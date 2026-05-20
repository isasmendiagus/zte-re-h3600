// module: mt7915.ko
// function: Set_AP_PMKCachePeriod_Proc @ 0x29a5c
// size: 108 bytes
//

undefined4
Set_AP_PMKCachePeriod_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = *(uint *)(*param_1 + 0x3c);
  iVar2 = os_str_tol(param_2,0,10,*param_1,param_4);
  iVar1 = DebugLevel;
  param_1[(uVar3 & 0xff) * 0x160d + 0xaed81] = iVar2 * 6000;
  if (2 < iVar1) {
    printk("I/F(ra%d) Set_AP_PMKCachePeriod_Proc=%ld\n");
  }
  return 1;
}

