// module: mt7915.ko
// function: Set_WmmCapable_Proc @ 0x57894
// size: 168 bytes
//

undefined4
Set_WmmCapable_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  char cVar2;
  int iVar3;
  
  iVar3 = *(int *)(*param_1 + 0x3c);
  cVar2 = os_str_tol(param_2,0,10,*param_1,param_4);
  iVar1 = DebugLevel;
  if ((cVar2 != '\x01') && (cVar2 != '\0')) {
    return 0;
  }
  *(char *)(param_1 + iVar3 * 0x84dec + 0xdb90b) = cVar2;
  if (iVar1 < 3) {
    return 1;
  }
  printk("Set_WmmCapable_Proc::(bWmmCapable=%d)\n",(char)param_1[iVar3 * 0x84dec + 0xdb90b]);
  return 1;
}

