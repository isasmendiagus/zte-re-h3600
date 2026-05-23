// module: mt7915.ko
// function: SetATELOGDump @ 0x260d70
// size: 148 bytes
//

undefined4 SetATELOGDump(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = simple_strtol(param_2,0,10,param_4,param_4);
  if (2 < iVar1 - 1U) {
    return 0;
  }
  MT_ATEDumpLog(param_1,param_1 + (iVar1 - 1U) * 0x18 + 0xa3b854,iVar1);
  if (DebugLevel < 1) {
    return 1;
  }
  printk("%s: log_type:%08x, driver:%08x\n","SetATELOGDump",iVar1,
         *(undefined4 *)(param_1 + 0xa39ffc));
  return 1;
}

