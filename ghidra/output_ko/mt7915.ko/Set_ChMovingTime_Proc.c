// module: mt7915.ko
// function: Set_ChMovingTime_Proc @ 0x101418
// size: 144 bytes
//

undefined4 Set_ChMovingTime_Proc(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined2 uVar2;
  
  uVar2 = os_str_tol(param_2,0,10);
  iVar1 = DebugLevel;
  *(undefined2 *)(param_1 + 0xa3772c) = uVar2;
  if (2 < iVar1) {
    printk("[%s]: band index: %d, cac_time: %d\n","Set_ChMovingTime_Proc",0,uVar2);
  }
  iVar1 = DebugLevel;
  *(undefined2 *)(param_1 + 0xa3774c) = uVar2;
  if (2 < iVar1) {
    printk("[%s]: band index: %d, cac_time: %d\n","Set_ChMovingTime_Proc",1,uVar2);
  }
  return 1;
}

