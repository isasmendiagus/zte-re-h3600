// module: mt7915.ko
// function: Set_QloadAlarmTimeThreshold_Proc @ 0x277b8
// size: 76 bytes
//

undefined4 Set_QloadAlarmTimeThreshold_Proc(int param_1,undefined4 param_2)

{
  undefined1 uVar1;
  int iVar2;
  
  iVar2 = HcGetQloadCtrl();
  uVar1 = os_str_tol(param_2,0,10);
  *(undefined1 *)(iVar2 + 0xc1) = uVar1;
  QBSS_LoadAlarmReset(param_1);
  *(uint *)(iVar2 + 0xd0) = (uint)*(ushort *)(&DAT_00794c50 + param_1);
  return 1;
}

