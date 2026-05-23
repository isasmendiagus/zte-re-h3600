// module: mt7915.ko
// function: halWtblReadRaw @ 0x190a6c
// size: 280 bytes
//

undefined4
halWtblReadRaw(int param_1,uint param_2,int param_3,uint param_4,ushort param_5,undefined4 *param_6)

{
  undefined4 *puVar1;
  uint uVar2;
  uint uVar3;
  undefined4 local_24 [2];
  
  uVar2 = (uint)param_5;
  if (param_6 == (undefined4 *)0x0) {
    return 0xff;
  }
  if (param_3 == 0) {
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820d4000,(param_2 << 0x16) >> 0x1d);
    uVar3 = (param_4 & 0x3f) << 2 | 0x820d8000 | (param_2 & 0x7f) << 8;
  }
  else {
    if (param_3 == 1) {
      uVar3 = (param_2 << 0x15) >> 0x1c;
    }
    else {
      if (param_3 != 2) {
        uVar3 = 0;
        goto LAB_00190ab0;
      }
      uVar3 = (param_2 << 0x15) >> 0x1c | 0x80000000;
    }
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820c4000,uVar3);
    uVar3 = (param_4 & 0xf) << 2 | 0x820c6000 | (param_2 & 0x7f) << 6;
  }
LAB_00190ab0:
  if (uVar2 != 0) {
    puVar1 = param_6;
    do {
      local_24[0] = 0;
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),(int)puVar1 + (uVar3 - (int)param_6),
                    local_24);
      uVar2 = uVar2 - 1;
      *puVar1 = local_24[0];
      puVar1 = puVar1 + 1;
    } while (uVar2 != 0);
  }
  return 0;
}

