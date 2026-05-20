#!/usr/bin/env python3
"""
H3600 config.bin helper — decrypt / edit / re-pack.

Wraps ../tools/ztetool.py (orca.pet) for the H3600 (no P) variant which uses
HARDCODED AES-256-CBC keys (no serial/MAC/passphrase needed):
    key = buggy_sha256("H3600V9Key02660008")
    iv  = buggy_sha256("H3600V9Iv02660008")[:16]

Usage:
    ./cfg_tool.py decode  config.bin  config.xml
    ./cfg_tool.py encode  config.xml  config_new.bin     # ENCRYPTED upload
    ./cfg_tool.py plain   config.xml  config_new.bin     # PLAIN upload (works too)
    ./cfg_tool.py ssh-on     config.bin config_new.bin   # SSHCfg.SSH_Enable = 1
    ./cfg_tool.py telnet-on  config.bin config_new.bin   # TelnetCfg.TS_Enable + Lan_Enable = 1
    ./cfg_tool.py lan-ssh-on config.bin config_new.bin   # FWSC: unblock SSH from LAN (real fix)

The router accepts BOTH encrypted (flag=4) and plain-zlib (flag=0) uploads,
so for an edit-and-upload roundtrip you don't need to re-encrypt.
"""
import os, re, struct, subprocess, sys, tempfile, zlib

ZTETOOL = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                      "..", "tools", "ztetool.py")

def run_ztetool(args):
    r = subprocess.run([sys.executable, ZTETOOL] + args,
                       capture_output=True, text=True)
    if r.returncode != 0:
        sys.stderr.write(r.stderr)
        sys.exit(r.returncode)
    return r

def decode(in_bin, out_xml):
    run_ztetool(["--router", "h3600", "--decode", in_bin, out_xml])
    print(f"[+] decoded {in_bin} -> {out_xml} ({os.path.getsize(out_xml)} B)")

def encode_encrypted(in_xml, out_bin):
    run_ztetool(["--router", "h3600", "--encode", in_xml, out_bin])
    print(f"[+] encoded (AES) {in_xml} -> {out_bin}")

def encode_plain(in_xml, out_bin):
    """Build flag=0 (plain zlib) container — router accepts it for upload.

    Outer header (60 B):
        u32 BE  magic        = 0x01020304
        u32 BE  fmt          = 0
        u32 BE  total_size   = uncompressed XML length
        u32 BE  ?            = 0 (matches stock plain dumps)
        u32 BE  ?            = total_size (mirror)
        u32 BE  crc32        = zlib.crc32(uncompressed XML)
        u32 BE  header_crc   = zlib.crc32(header[0:24])
        bytes   pad          = 0x00 * (60 - 28)

    Then chunked body, same 12 B chunk header (plain_len, comp_len, more_flag).
    We emit the whole XML as one zlib chunk for simplicity.
    """
    xml = open(in_xml, "rb").read()
    comp = zlib.compress(xml)
    body_crc = zlib.crc32(xml)

    hdr = bytearray(60)
    struct.pack_into(">IIIIIII", hdr, 0,
                     0x01020304, 0, len(xml), 0, len(xml), body_crc, 0)
    header_crc = zlib.crc32(bytes(hdr[:24]))
    struct.pack_into(">I", hdr, 24, header_crc)

    chunk_hdr = struct.pack(">III", len(xml), len(comp), 0)

    with open(out_bin, "wb") as f:
        f.write(hdr)
        f.write(chunk_hdr)
        f.write(comp)
    print(f"[+] plain (flag=0) {in_xml} -> {out_bin} ({os.path.getsize(out_bin)} B)")

def edit_xml_inplace(xml_path, mutator):
    """mutator: f(xml_text)->xml_text"""
    with open(xml_path, "rb") as f:
        text = f.read().decode("utf-8")
    new = mutator(text)
    if new == text:
        print("[!] no changes made")
    with open(xml_path, "wb") as f:
        f.write(new.encode("utf-8"))

def _set_dm_in_table(text, table_name, dm_name, value):
    """Find <Tbl name="X"> ... </Tbl> block and set <DM name="dm_name" val="..."/>"""
    pat = re.compile(
        r'(<Tbl name="' + re.escape(table_name) + r'"[^>]*>.*?)'
        r'(<DM name="' + re.escape(dm_name) + r'" val=")[^"]*("/>.*?</Tbl>)',
        re.DOTALL,
    )
    return pat.sub(lambda m: m.group(1) + m.group(2) + value + m.group(3), text)

def ssh_on(in_bin, out_bin):
    with tempfile.TemporaryDirectory() as td:
        xml = os.path.join(td, "c.xml")
        decode(in_bin, xml)
        edit_xml_inplace(xml, lambda t: _set_dm_in_table(t, "SSHCfg", "SSH_Enable", "1"))
        encode_plain(xml, out_bin)

def telnet_on(in_bin, out_bin):
    with tempfile.TemporaryDirectory() as td:
        xml = os.path.join(td, "c.xml")
        decode(in_bin, xml)
        def mut(t):
            t = _set_dm_in_table(t, "TelnetCfg", "TS_Enable", "1")
            t = _set_dm_in_table(t, "TelnetCfg", "Lan_Enable", "1")
            return t
        edit_xml_inplace(xml, mut)
        encode_plain(xml, out_bin)

def lan_ssh_on(in_bin, out_bin):
    """Flip FWSC rows named 'lan_ssh' / 'lan_sshv6' from DROP (0) to ALLOW (1).

    Stock ships a FWSC rule that explicitly drops SSH from the LAN bridge.
    Without flipping this, SSH_Enable=1 is meaningless from the LAN side.
    """
    with tempfile.TemporaryDirectory() as td:
        xml = os.path.join(td, "c.xml")
        decode(in_bin, xml)
        def mut(t):
            # Match a Row block that contains Name="lan_ssh" or "lan_sshv6"
            # and replace its FilterTarget value with 1.
            row_pat = re.compile(
                r'(<Row No="\d+">(?:(?!</Row>).)*?'
                r'<DM name="Name" val="lan_ssh(?:v6)?"/>'
                r'(?:(?!</Row>).)*?'
                r'<DM name="FilterTarget" val=")0("/>'
                r'(?:(?!</Row>).)*?</Row>)',
                re.DOTALL,
            )
            return row_pat.sub(lambda m: m.group(1).replace(
                '<DM name="FilterTarget" val="0"/>',
                '<DM name="FilterTarget" val="1"/>'), t)
        edit_xml_inplace(xml, mut)
        encode_plain(xml, out_bin)

def main():
    if len(sys.argv) != 4:
        print(__doc__)
        sys.exit(1)
    cmd, src, dst = sys.argv[1], sys.argv[2], sys.argv[3]
    {"decode":     decode,
     "encode":     encode_encrypted,
     "plain":      encode_plain,
     "ssh-on":     ssh_on,
     "telnet-on":  telnet_on,
     "lan-ssh-on": lan_ssh_on}[cmd](src, dst)

if __name__ == "__main__":
    main()
