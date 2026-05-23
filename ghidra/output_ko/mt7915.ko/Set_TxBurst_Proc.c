// module: mt7915.ko
// function: Set_TxBurst_Proc @ 0xd9ea8
// size: 116 bytes
//

undefined4 Set_TxBurst_Proc(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = os_str_tol(param_2,0,10);
  iVar1 = DebugLevel;
  if ((iVar2 != 1) && (iVar2 != 0)) {
    return 0;
  }
  *(char *)(param_1 + 0x795071) = (char)iVar2;
  if (iVar1 < 3) {
    return 1;
  }
  printk("Set_TxBurst_Proc::(TxBurst=%d)\n",*(undefined1 *)(param_1 + 0x795071));
  return 1;
}

