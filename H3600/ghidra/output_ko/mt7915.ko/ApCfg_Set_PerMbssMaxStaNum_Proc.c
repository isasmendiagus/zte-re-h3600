// module: mt7915.ko
// function: ApCfg_Set_PerMbssMaxStaNum_Proc @ 0x3ef14
// size: 112 bytes
//

undefined4
ApCfg_Set_PerMbssMaxStaNum_Proc(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  char cVar2;
  
  cVar2 = os_str_tol(param_3,0,10,param_4,param_4);
  iVar1 = DebugLevel;
  "pStaCfg->WpaPassPhrase"[param_2 * 0x5834 + param_1 + 10] = cVar2;
  if (2 < iVar1) {
    printk("IF(ra%d) %s::(MaxStaNum=%d)\n",param_2,"ApCfg_Set_PerMbssMaxStaNum_Proc",cVar2);
  }
  return 1;
}

