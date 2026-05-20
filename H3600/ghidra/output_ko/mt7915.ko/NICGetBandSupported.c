// module: mt7915.ko
// function: NICGetBandSupported @ 0x147b90
// size: 152 bytes
//

undefined4 NICGetBandSupported(int param_1)

{
  undefined4 uVar1;
  uint uVar2;
  
  uVar2 = (uint)(byte)"rtmp_read_dot11v_mbssid_cfg_from_file"[param_1 + 0x1e];
  if ((uVar2 - 0x1e & 0xfb) != 0) {
    if ((uVar2 - 2 & 0xfd) == 0 ||
        (uVar2 - 0x1f < 2 ||
        (uVar2 - 0x1c < 2 ||
        (uVar2 - 0x18 < 3 ||
        (uVar2 - 0x13 < 2 ||
        (uVar2 - 0xd < 5 || (uVar2 - 9 < 2 || (uVar2 == 0x23 || uVar2 == 0xff)))))))) {
      uVar1 = 3;
    }
    else {
      uVar1 = 1;
    }
    return uVar1;
  }
  return 2;
}

