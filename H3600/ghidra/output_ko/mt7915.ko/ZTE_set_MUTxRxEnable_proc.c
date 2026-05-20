// module: mt7915.ko
// function: ZTE_set_MUTxRxEnable_proc @ 0xe9330
// size: 88 bytes
//

undefined4 ZTE_set_MUTxRxEnable_proc(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = simple_strtol(param_2,0,10);
  iVar1 = DebugLevel;
  *(undefined4 *)(param_1 + 0x7959a0) = uVar2;
  if (0 < iVar1) {
    printk("%s: MUTxRxEnable:%lu\n","ZTE_set_MUTxRxEnable_proc",uVar2);
  }
  return 1;
}

