// module: mt7915.ko
// function: Set_NoForwarding_Proc @ 0x298f8
// size: 160 bytes
//

undefined4
Set_NoForwarding_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *param_1;
  iVar1 = os_str_tol(param_2,0,10,param_4,param_4);
  if ((iVar1 != 1) && (iVar1 != 0)) {
    return 0;
  }
  param_1[*(int *)(iVar2 + 0x3c) * 0x160d + 0xaed9b] = iVar1;
  if (DebugLevel < 3) {
    return 1;
  }
  iVar1 = *(int *)(iVar2 + 0x3c);
  printk("IF(ra%d) Set_NoForwarding_Proc::(NoForwarding=%ld)\n",iVar1,
         param_1[iVar1 * 0x160d + 0xaed9b]);
  return 1;
}

