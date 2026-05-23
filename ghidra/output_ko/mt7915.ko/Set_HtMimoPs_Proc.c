// module: mt7915.ko
// function: Set_HtMimoPs_Proc @ 0xdf4d0
// size: 116 bytes
//

undefined4 Set_HtMimoPs_Proc(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = os_str_tol(param_2,0,10);
  if ((iVar1 != 0) && (iVar1 != 1)) {
    return 0;
  }
  *(char *)(param_1 + 0x795945) = (char)iVar1;
  if (DebugLevel < 3) {
    return 1;
  }
  printk("Set_HtMimoPs_Proc::(HtMimoPs=%d)\n",*(undefined1 *)(param_1 + 0x795945));
  return 1;
}

