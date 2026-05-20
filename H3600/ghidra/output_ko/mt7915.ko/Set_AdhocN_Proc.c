// module: mt7915.ko
// function: Set_AdhocN_Proc @ 0x57f30
// size: 168 bytes
//

undefined4 Set_AdhocN_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(*param_1 + 0x3c);
  iVar1 = os_str_tol(param_2,0,10,*param_1,param_4);
  if (iVar1 == 0) {
    *(undefined1 *)(param_1 + iVar2 * 0x84dec + 0xdc701) = 0;
  }
  else {
    *(undefined1 *)(param_1 + iVar2 * 0x84dec + 0xdc701) = 1;
  }
  if (2 < DebugLevel) {
    printk("IF Set_AdhocN_Proc::(bAdhocN=%d)\n",(char)param_1[iVar2 * 0x84dec + 0xdc701]);
  }
  return 1;
}

