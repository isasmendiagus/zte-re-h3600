// module: mt7915.ko
// function: AsicGetCCACnt @ 0x131c00
// size: 180 bytes
//

int AsicGetCCACnt(int param_1,int param_2)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint local_14 [2];
  
  local_14[0] = 0;
  if (param_2 == 0) {
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x83081010,local_14);
    uVar2 = *(undefined4 *)(param_1 + 0xa797a0);
    uVar3 = 0x83081014;
  }
  else {
    if (param_2 != 1) {
      return 0;
    }
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x83091010,local_14);
    uVar2 = *(undefined4 *)(param_1 + 0xa797a0);
    uVar3 = 0x83091014;
  }
  uVar1 = local_14[0];
  mac_io_read32(uVar2,uVar3,local_14);
  return (((uVar1 >> 0x10) + (uVar1 & 0xffff)) - (local_14[0] >> 0x10)) - (local_14[0] & 0xffff);
}

