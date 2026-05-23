// module: mt7915.ko
// function: TxBfCfgBfPhy @ 0x889c8
// size: 220 bytes
//

undefined4 TxBfCfgBfPhy(int param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined1 uStack_30;
  undefined1 local_2f;
  byte local_2e;
  char local_2d;
  
  iVar3 = *(int *)(param_1 + 0xa797a0);
  if (*(char *)(iVar3 + 0x32d8) != '\0') {
    uVar2 = 0;
    do {
      iVar1 = uVar2 * 0x354 + iVar3 + 0x1000;
      if (*(char *)(iVar1 + 0x6a6) != '\0') {
        local_2e = *(byte *)(iVar1 + 0x69c);
        local_2f = 0;
        local_2d = *(char *)(param_1 + (uint)local_2e + 0x7959a7);
        *(char *)(iVar1 + 0x6a7) = local_2d;
        if (local_2d != '\0') {
          AsicTxBfCfgBfPhy(param_1,&uStack_30);
        }
      }
      if (0 < DebugLevel) {
        printk("ucAction = %d, ucBandIdx = %d, ucSmthIntlBypass = %d\n",local_2f,local_2e,local_2d);
      }
      uVar2 = uVar2 + 1 & 0xff;
    } while (uVar2 < *(byte *)(iVar3 + 0x32d8));
  }
  return 1;
}

