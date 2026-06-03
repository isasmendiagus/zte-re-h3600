import paramiko,time,re
c=paramiko.SSHClient(); c.set_missing_host_key_policy(paramiko.AutoAddPolicy())
c.connect('192.168.1.1',username='admin',password='UkuGPeyRDU',timeout=12,allow_agent=False,look_for_keys=False)
ch=c.invoke_shell(width=240,height=8000); time.sleep(1.0)
def run(cmd,t=1.1):
    ch.send(cmd+'\n'); o='';e=time.time()+t
    while time.time()<e:
        if ch.recv_ready(): o+=ch.recv(65536).decode(errors='replace');e=time.time()+t
        else: time.sleep(0.04)
    return o
CMD=0xe3005; DATA=0xe3007
def rd(ram,addr):
    cmdval=addr|(ram<<22)|(1<<27)
    run('rm -f /tmp/r.bin; (cat /dev/logger_main > /tmp/r.bin 2>&1 &); sleep 0.5',1.1)
    run('fpga -r 0x73000 1 >/dev/null 2>&1',0.5)
    run('fpga -w 0x%x 0x%x >/dev/null 2>&1'%(CMD,cmdval),0.4)
    run('fpga -r 0x%x 17 >/dev/null 2>&1'%DATA,0.7)
    time.sleep(0.25); run('killall cat 2>/dev/null',0.5)
    out=run('grep -aE "fpga read:" /tmp/r.bin',1.2)
    w={}
    for m in re.finditer(r'reg=0x([0-9a-f]+),\s*value=0x([0-9a-f]+)',out): w[int(m.group(1),16)]=m.group(2)
    return [w.get(DATA+i,'????????') for i in range(17)]
def decode(d):
    try:
        ws=[int(x,16) for x in d[:5]]
        w1,w3,w4=ws[1],ws[3],ws[4]
        b13=(w3>>8)&0xff; b14=(w3>>16)&0xff
        inport=((b14&0x3f)<<6)|(b13>>2)
        cpu_qid=(w1>>16)&0xff   # byte6 = word1 byte2
        valid=w4&0xff           # byte0x10 = word4 byte0
        return 'inport=%d cpu_qid=0x%02x valid/dir=0x%02x'%(inport,cpu_qid,valid)
    except: return '(decode-fail)'
P2=[0x21,0x93,0x121,0x193,0x221,0x293,0x321,0x393]
P3=[0x79,0xcb,0x179,0x1cb,0x279,0x2cb,0x379,0x3cb]
print('### regport2 (logical port1, FAILS) — ram2')
for a in P2:
    d=rd(2,a); print('ram2 a0x%03x: %s   | %s'%(a,' '.join(d),decode(d)),flush=True)
print('### regport3 (logical port2, WORKS) — ram2')
for a in P3:
    d=rd(2,a); print('ram2 a0x%03x: %s   | %s'%(a,' '.join(d),decode(d)),flush=True)
ch.close(); c.close()
print('DONE')
