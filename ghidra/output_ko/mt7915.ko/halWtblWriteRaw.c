// module: mt7915.ko
// function: halWtblWriteRaw @ 0x1909ac
// size: 192 bytes
//

undefined4 halWtblWriteRaw(int param_1,uint param_2,int param_3,uint param_4,undefined4 param_5)

{
  uint uVar1;
  
  if (param_3 == 0) {
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820d4000,(param_2 << 0x16) >> 0x1d);
    uVar1 = (param_4 & 0x3f) << 2 | 0x820d8000 | (param_2 & 0x7f) << 8;
  }
  else {
    if (param_3 == 1) {
      uVar1 = (param_2 << 0x15) >> 0x1c;
    }
    else {
      if (param_3 != 2) {
        uVar1 = 0;
        goto LAB_001909e8;
      }
      uVar1 = (param_2 << 0x15) >> 0x1c | 0x80000000;
    }
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820c4000,uVar1);
    uVar1 = (param_4 & 0xf) << 2 | 0x820c6000 | (param_2 & 0x7f) << 6;
  }
LAB_001909e8:
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),uVar1,param_5);
  return 0;
}

