// module: mt7915.ko
// function: Set_WscMaxPinAttack_Proc @ 0x2ae2c
// size: 104 bytes
//

undefined4 Set_WscMaxPinAttack_Proc(int *param_1,undefined4 param_2)

{
  undefined1 uVar1;
  int iVar2;
  
  iVar2 = *param_1;
  uVar1 = os_str_tol(param_2,0,10);
  if (2 < DebugLevel) {
    printk("Set_WscMaxPinAttack_Proc::(MaxPinAttack=%d)\n",uVar1);
  }
  *(undefined1 *)((int)param_1 + *(int *)(iVar2 + 0x3c) * 0x5834 + 0x2bb107) = uVar1;
  return 1;
}

