// module: mt7915.ko
// function: Set_WscVersion_Proc @ 0x2ab90
// size: 108 bytes
//

undefined4 Set_WscVersion_Proc(int *param_1,undefined4 param_2)

{
  undefined1 uVar1;
  int iVar2;
  
  iVar2 = *param_1;
  uVar1 = os_str_tol(param_2,0,0x10);
  if (2 < DebugLevel) {
    printk("Set_WscVersion_Proc::(version=%x)\n",uVar1);
  }
  *(undefined1 *)(param_1 + *(int *)(iVar2 + 0x3c) * 0x160d + 0xae167) = uVar1;
  return 1;
}

