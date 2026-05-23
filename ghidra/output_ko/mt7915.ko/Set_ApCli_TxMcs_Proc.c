// module: mt7915.ko
// function: Set_ApCli_TxMcs_Proc @ 0x3099c
// size: 216 bytes
//

undefined4 Set_ApCli_TxMcs_Proc(int *param_1,undefined4 param_2)

{
  int iVar1;
  byte bVar2;
  int iVar3;
  
  iVar3 = *param_1;
  if (*(int *)(iVar3 + 0x38) != 0x400) {
    return 0;
  }
  iVar1 = *(int *)(iVar3 + 0x3c) * 0x2137b0;
  bVar2 = RT_CfgSetTxMCSProc(param_2,(undefined *)((int)param_1 + (int)(&DAT_0036e408 + iVar1)));
  *(byte *)((int)param_1 + iVar1 + 0x36e406) =
       *(byte *)((int)param_1 + iVar1 + 0x36e406) & 0x80 | bVar2 & 0x7f;
  if ((*(byte *)((int)param_1 + iVar1 + 0x36e406) & 0x7f) == 0x21) {
    if (2 < DebugLevel) {
      printk("I/F(apcli%d) Set_ApCli_TxMcs_Proc = AUTO\n",*(undefined4 *)(iVar3 + 0x3c));
      return 1;
    }
  }
  else if (2 < DebugLevel) {
    printk("I/F(apcli%d) Set_ApCli_TxMcs_Proc = %d\n",*(undefined4 *)(iVar3 + 0x3c));
    return 1;
  }
  return 1;
}

