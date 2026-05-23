// module: mt7915.ko
// function: Set_PowerSaveLifeTime_Proc @ 0x2b578
// size: 92 bytes
//

undefined4 Set_PowerSaveLifeTime_Proc(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined2 uVar2;
  
  uVar2 = os_str_tol(param_2,0,10);
  iVar1 = DebugLevel;
  *(undefined2 *)(param_1 + 0x28594a) = uVar2;
  if (2 < iVar1) {
    printk("Set new life time = %d\n",uVar2);
  }
  return 1;
}

