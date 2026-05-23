// module: mt7915.ko
// function: Set_APSDCapable_Proc @ 0x5793c
// size: 156 bytes
//

undefined4
Set_APSDCapable_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  
  iVar2 = *(int *)(*param_1 + 0x3c);
  cVar1 = os_str_tol(param_2,0,10,*param_1,param_4);
  if (cVar1 == '\0') {
    *(undefined1 *)(param_1 + iVar2 * 0x84dec + 0xdb90c) = 0;
  }
  else {
    *(undefined1 *)(param_1 + iVar2 * 0x84dec + 0xdb90c) = 1;
  }
  if (2 < DebugLevel) {
    printk("APSDCapable=%d\n",(char)param_1[iVar2 * 0x84dec + 0xdb90c]);
  }
  return 1;
}

