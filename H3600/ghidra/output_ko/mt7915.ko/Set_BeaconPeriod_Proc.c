// module: mt7915.ko
// function: Set_BeaconPeriod_Proc @ 0x342d8
// size: 136 bytes
//

bool Set_BeaconPeriod_Proc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  ushort uVar1;
  bool bVar2;
  
  uVar1 = os_str_tol(param_2,0,10,param_4,param_4);
  bVar2 = uVar1 - 0x14 < 0x3ec;
  if (bVar2) {
    *(ushort *)(&DAT_00794c50 + param_1) = uVar1;
    QBSS_LoadAlarmReset(param_1);
  }
  if (2 < DebugLevel) {
    printk("Set_BeaconPeriod_Proc::(BeaconPeriod=%d)\n",*(undefined2 *)(&DAT_00794c50 + param_1));
  }
  return bVar2;
}

