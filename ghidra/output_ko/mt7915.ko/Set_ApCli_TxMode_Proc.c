// module: mt7915.ko
// function: Set_ApCli_TxMode_Proc @ 0x30548
// size: 136 bytes
//

undefined4 Set_ApCli_TxMode_Proc(int *param_1,undefined4 param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = *param_1;
  if (*(int *)(iVar2 + 0x38) != 0x400) {
    return 0;
  }
  iVar3 = *(int *)(iVar2 + 0x3c);
  bVar1 = RT_CfgSetFixedTxPhyMode(param_2);
  *(byte *)((int)param_1 + iVar3 * 0x2137b0 + 0x36e407) =
       *(byte *)((int)param_1 + iVar3 * 0x2137b0 + 0x36e407) & 199 | (bVar1 & 7) << 3;
  if (DebugLevel < 3) {
    return 1;
  }
  printk("I/F(apcli%d) Set_ApCli_TxMode_Proc = %d\n",*(undefined4 *)(iVar2 + 0x3c));
  return 1;
}

