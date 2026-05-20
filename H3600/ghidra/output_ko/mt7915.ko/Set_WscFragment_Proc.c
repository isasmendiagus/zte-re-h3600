// module: mt7915.ko
// function: Set_WscFragment_Proc @ 0x2abfc
// size: 108 bytes
//

undefined4 Set_WscFragment_Proc(int *param_1,undefined4 param_2)

{
  undefined1 uVar1;
  int iVar2;
  
  iVar2 = *param_1;
  uVar1 = os_str_tol(param_2,0,0x10);
  if (2 < DebugLevel) {
    printk("Set_WscFragment_Proc::(bool_flag=%d)\n",uVar1);
  }
  *(undefined1 *)((int)param_1 + *(int *)(iVar2 + 0x3c) * 0x5834 + 0x2bb10d) = uVar1;
  return 1;
}

