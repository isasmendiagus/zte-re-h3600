// module: mt7915.ko
// function: ge_enq_mgmtq_pkt @ 0xd1b48
// size: 228 bytes
//

undefined4 ge_enq_mgmtq_pkt(int param_1,undefined4 param_2,undefined4 *param_3)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)("Get_RBIST_Raw_Data_Proc" + param_1 + 0x14);
  iVar1 = wlan_operate_get_state(param_2);
  if (iVar1 != 1) {
    *(int *)(param_1 + 0x9db74) = *(int *)(param_1 + 0x9db74) + 1;
    RTMPFreeNdisPacket(param_1,param_3);
    return 1;
  }
  if (0x1ff < *(uint *)(param_1 + 0x285b54)) {
    *(int *)(param_1 + 0x9db78) = *(int *)(param_1 + 0x9db78) + 1;
    RTMPFreeNdisPacket(param_1,param_3);
    return 1;
  }
  _raw_spin_lock_bh(param_1 + 0x285b3c);
  *param_3 = 0;
  if (*(undefined4 **)(param_1 + 0x285b50) == (undefined4 *)0x0) {
    *(undefined4 **)(param_1 + 0x285b4c) = param_3;
  }
  else {
    **(undefined4 **)(param_1 + 0x285b50) = param_3;
  }
  *(undefined4 **)(param_1 + 0x285b50) = param_3;
  *(int *)(param_1 + 0x285b54) = *(int *)(param_1 + 0x285b54) + 1;
  _raw_spin_unlock_bh(param_1 + 0x285b3c);
  (**(code **)(iVar2 + 0x3c))(param_1,0);
  return 0;
}

