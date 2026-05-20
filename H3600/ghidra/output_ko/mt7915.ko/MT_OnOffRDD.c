// module: mt7915.ko
// function: MT_OnOffRDD @ 0x280354
// size: 164 bytes
//

undefined4 MT_OnOffRDD(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  undefined4 uVar1;
  bool bVar2;
  
  bVar2 = param_4 != 0;
  MtATESetMacTxRx(param_1,2,bVar2,0);
  if (*(char *)(param_1 + 0x79504d) != '\0') {
    MtATESetMacTxRx(param_1,2,bVar2,1);
  }
  uVar1 = MtCmdSetRDDTestExt(param_1,param_2,param_3,param_4);
  if (2 < DebugLevel) {
    printk("%s ARB Rx On:%x\n","MT_OnOffRDD",bVar2);
  }
  return uVar1;
}

