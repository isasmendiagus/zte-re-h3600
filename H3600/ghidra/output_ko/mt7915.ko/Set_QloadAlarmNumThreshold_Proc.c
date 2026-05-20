// module: mt7915.ko
// function: Set_QloadAlarmNumThreshold_Proc @ 0x27804
// size: 44 bytes
//

undefined4 Set_QloadAlarmNumThreshold_Proc(undefined4 param_1,undefined4 param_2)

{
  undefined1 uVar1;
  int iVar2;
  
  iVar2 = HcGetQloadCtrl();
  uVar1 = os_str_tol(param_2,0,10);
  *(undefined1 *)(iVar2 + 0xc2) = uVar1;
  return 1;
}

