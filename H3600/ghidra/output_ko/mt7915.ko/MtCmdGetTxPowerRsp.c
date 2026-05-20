// module: mt7915.ko
// function: MtCmdGetTxPowerRsp @ 0x1ab750
// size: 56 bytes
//

void MtCmdGetTxPowerRsp(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0xc);
  *(undefined1 *)(iVar1 + 1) = *(undefined1 *)(param_2 + 1);
  *(undefined1 *)(iVar1 + 2) = *(undefined1 *)(param_2 + 2);
  if (DebugLevel < 3) {
    return;
  }
  printk("%s, Power: 0x%x Band: %d\n","MtCmdGetTxPowerRsp");
  return;
}

