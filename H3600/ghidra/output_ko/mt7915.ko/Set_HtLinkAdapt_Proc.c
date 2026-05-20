// module: mt7915.ko
// function: Set_HtLinkAdapt_Proc @ 0xde364
// size: 116 bytes
//

undefined4 Set_HtLinkAdapt_Proc(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = os_str_tol(param_2,0,10);
  if ((iVar1 != 0) && (iVar1 != 1)) {
    return 0;
  }
  *(char *)(param_1 + 0xa39fb4) = (char)iVar1;
  if (DebugLevel < 3) {
    return 1;
  }
  printk("Set_HtLinkAdapt_Proc::(HtLinkAdapt=%d)\n",*(undefined1 *)(param_1 + 0xa39fb4));
  return 1;
}

