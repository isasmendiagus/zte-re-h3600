// module: mt7915.ko
// function: sae_clear_data @ 0x2091d0
// size: 204 bytes
//

void sae_clear_data(int *param_1)

{
  int iVar1;
  undefined1 uStack_9;
  
  if (4 < DebugLevel) {
    printk("==> %s()\n","sae_clear_data");
  }
  if (param_1[0x26] != 0) {
    (**(code **)(param_1[0x26] + 4))(param_1);
  }
  if (param_1[0x1f] != 0) {
    os_free_mem();
    param_1[0x1f] = 0;
  }
  Bignum_Free(param_1 + 0x18);
  Bignum_Free(param_1 + 10);
  Bignum_Free(param_1 + 0x14);
  iVar1 = param_1[0x60];
  if ((iVar1 != 0) && (*param_1 - 1U < 2)) {
    *(int *)(iVar1 + 0x1b904) = *(int *)(iVar1 + 0x1b904) + -1;
  }
  *param_1 = 0;
  __memzero(param_1,0x128);
  RTMPCancelTimer(param_1 + 0x4b,&uStack_9);
  return;
}

