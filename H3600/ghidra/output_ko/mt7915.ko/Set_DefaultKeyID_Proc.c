// module: mt7915.ko
// function: Set_DefaultKeyID_Proc @ 0x57a30
// size: 144 bytes
//

undefined4
Set_DefaultKeyID_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)(*param_1 + 0x3c);
  iVar2 = os_str_tol(param_2,0,10,*param_1,param_4);
  iVar1 = DebugLevel;
  if (3 < iVar2 - 1U) {
    return 0;
  }
  *(char *)(param_1 + iVar3 * 0x84dec + 0xdb734) = (char)(iVar2 - 1U);
  if (iVar1 < 3) {
    return 1;
  }
  printk("%s:: DefaultKeyId=%d\n","Set_DefaultKeyID_Proc");
  return 1;
}

