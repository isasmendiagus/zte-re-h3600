// module: mt7915.ko
// function: Set_Map_Proc @ 0x341d4
// size: 124 bytes
//

undefined4 Set_Map_Proc(int *param_1,undefined4 param_2)

{
  int iVar1;
  bool bVar2;
  
  if ((*(int *)(*param_1 + 0x38) - 0x100U & 0xfffffeff) != 0) {
    return 0;
  }
  iVar1 = os_str_tol(param_2,0,10);
  bVar2 = DebugLevel < 0;
  *(bool *)((int)param_1 + 0xa7cbfa) = iVar1 != 0;
  if (bVar2) {
    return 1;
  }
  printk("%s() pAd->bMAPEnable = 0x%x\n","Set_Map_Proc");
  return 1;
}

