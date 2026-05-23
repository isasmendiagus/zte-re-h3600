// module: mt7915.ko
// function: MtfAsicSetRxFilter @ 0x1953a0
// size: 296 bytes
//

undefined4 MtfAsicSetRxFilter(int param_1,uint param_2,undefined4 param_3)

{
  uint uVar1;
  uint uVar2;
  undefined1 local_c;
  undefined1 local_b;
  undefined1 local_a;
  
  local_c = (char)param_3;
  if (local_c == '\0') {
    local_b = (char)((uint)param_3 >> 8);
    if (local_b == '\0') {
      uVar2 = 0;
    }
    else {
      uVar2 = 0x1000;
    }
    if ((param_2 & 1) != 0) {
      uVar2 = uVar2 | 1;
    }
    if ((param_2 & 2) != 0) {
      uVar2 = uVar2 | 2;
    }
    if ((param_2 & 4) != 0) {
      uVar2 = uVar2 | 8;
    }
    if ((param_2 & 8) != 0) {
      uVar2 = uVar2 | 0x10;
    }
    if ((param_2 & 0x10) != 0) {
      uVar2 = uVar2 | 0x20;
    }
    if ((param_2 & 0x20) != 0) {
      uVar2 = uVar2 | 0x40;
    }
    if ((param_2 & 0x40) != 0) {
      uVar2 = uVar2 | 0x80;
    }
    if ((param_2 & 0x80) != 0) {
      uVar2 = uVar2 | 0x100;
    }
    if ((param_2 & 0x100) != 0) {
      uVar2 = uVar2 | 0x200;
    }
    if ((param_2 & 0x200) != 0) {
      uVar2 = uVar2 | 0x400;
    }
    if ((param_2 & 0x400) != 0) {
      uVar2 = uVar2 | 0x800;
    }
    if ((param_2 & 0x800) != 0) {
      uVar2 = uVar2 | 0x2000;
    }
    if ((param_2 & 0x1000) != 0) {
      uVar2 = uVar2 | 0x4000;
    }
    if ((param_2 & 0x2000) != 0) {
      uVar2 = uVar2 | 0x8000;
    }
    if ((param_2 & 0x4000) != 0) {
      uVar2 = uVar2 | 0x10000;
    }
    if ((param_2 & 0x8000) != 0) {
      uVar2 = uVar2 | 0x20000;
    }
    if ((param_2 & 0x10000) != 0) {
      uVar2 = uVar2 | 0x40000;
    }
    if ((param_2 & 0x20000) != 0) {
      uVar2 = uVar2 | 0x80000;
    }
    if ((param_2 & 0x40000) != 0) {
      uVar2 = uVar2 | 0x100000;
    }
  }
  else {
    uVar2 = 4;
  }
  local_a = (char)((uint)param_3 >> 0x10);
  if (local_a == '\0') {
    uVar1 = 0x5000;
  }
  else {
    uVar1 = 0x5100;
  }
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),uVar1 | 0x820f0000,uVar2);
  return 1;
}

