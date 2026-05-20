// module: mt7915.ko
// function: Set_AutoRoaming_Proc @ 0x57cb0
// size: 172 bytes
//

undefined4
Set_AutoRoaming_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(*param_1 + 0x3c);
  iVar1 = os_str_tol(param_2,0,10,*param_1,param_4);
  if (iVar1 == 0) {
    *(undefined1 *)((int)param_1 + iVar2 * 0x2137b0 + 0x580cce) = 0;
  }
  else {
    *(undefined1 *)((int)param_1 + iVar2 * 0x2137b0 + 0x580cce) = 1;
  }
  if (2 < DebugLevel) {
    printk("IF Set_AutoRoaming_Proc::(bAutoRoaming=%d)\n",
           *(undefined1 *)((int)param_1 + iVar2 * 0x2137b0 + 0x580cce));
  }
  return 1;
}

