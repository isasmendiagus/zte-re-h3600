// module: mt7915.ko
// function: Set_WscConfStatus_Proc @ 0x5a07c
// size: 224 bytes
//

undefined4
Set_WscConfStatus_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  byte bVar2;
  int iVar3;
  
  iVar3 = *(int *)(*param_1 + 0x3c);
  bVar2 = os_str_tol(param_2,0,10,*param_1,param_4);
  iVar1 = DebugLevel;
  if (1 < bVar2 - 1) {
    if ((2 < DebugLevel) &&
       (printk("Set_WscConfStatus_Proc:: Set failed!!(WscConfStatus=%s), WscConfStatus is 1 or 2\n",
               param_2), 2 < DebugLevel)) {
      printk("Set_WscConfStatus_Proc:: WscConfStatus is not changed (%d)\n",
             (char)param_1[iVar3 * 0x84dec + 0xdbb91]);
    }
    return 0;
  }
  *(byte *)(param_1 + iVar3 * 0x84dec + 0xdbb91) = bVar2;
  if (2 < iVar1) {
    printk("Set_WscConfStatus_Proc::(WscConfStatus=%d)\n",(uint)bVar2);
  }
  return 1;
}

