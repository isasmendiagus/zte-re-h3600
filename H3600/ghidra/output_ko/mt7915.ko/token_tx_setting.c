// module: mt7915.ko
// function: token_tx_setting @ 0x1d3e44
// size: 272 bytes
//

undefined4 token_tx_setting(int param_1,int param_2,int param_3,uint param_4,int param_5)

{
  int iVar1;
  byte bVar2;
  
  iVar1 = hc_get_ct_cb(*(undefined4 *)(param_1 + 0xa797a0));
  if (param_3 == 1) {
    if (0xb < (int)param_4) {
      return 1;
    }
    *(undefined2 *)(iVar1 + (param_2 * 0x15 + param_4) * 8 + 0x4c) = (undefined2)param_5;
    return 0;
  }
  if (param_3 == 2) {
    if (param_5 == 0) {
      bVar2 = *(byte *)(iVar1 + 0x164) & ~(byte)(1 << (param_4 & 0xff));
    }
    else {
      bVar2 = *(byte *)(iVar1 + 0x164) | (byte)(1 << (param_4 & 0xff));
    }
    *(byte *)(iVar1 + 0x164) = bVar2;
    return 0;
  }
  if (param_3 == 0) {
    if (param_4 == 0) {
      *(int *)(iVar1 + param_2 * 0xa8 + 0x2c) = param_5;
      return 0;
    }
    if (param_4 == 1) {
      *(int *)(iVar1 + param_2 * 0xa8 + 0x30) = param_5;
      return 0;
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s: unknown token option %d\n","token_tx_setting",param_3);
    return 1;
  }
  return 1;
}

