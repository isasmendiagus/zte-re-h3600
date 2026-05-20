// module: mt7915.ko
// function: ZTE_Report_Event @ 0x15f990
// size: 84 bytes
//

undefined4 ZTE_Report_Event(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = simple_strtol(param_2,0,10);
  iVar1 = DebugLevel;
  *(undefined4 *)(param_1 + 0xa7d168) = uVar2;
  if (2 < iVar1) {
    printk("5G_ReportEvent %d\n",uVar2);
  }
  return 1;
}

