// module: mt7915.ko
// function: ge_enq_dataq_pkt @ 0xd25e4
// size: 368 bytes
//

undefined4 ge_enq_dataq_pkt(int param_1,undefined4 param_2,undefined4 *param_3,int param_4)

{
  ushort uVar1;
  int iVar2;
  byte bVar3;
  int iVar4;
  
  iVar4 = *(int *)("Get_RBIST_Raw_Data_Proc" + param_1 + 0x14);
  uVar1 = *(ushort *)((int)param_3 + 0x42);
  iVar2 = wlan_operate_get_state(param_2);
  if (iVar2 != 1) {
    RTMPFreeNdisPacket(param_1,param_3);
    return 1;
  }
  bVar3 = *(byte *)((int)param_3 + 0x4e) & 8;
  if ((*(byte *)((int)param_3 + 0x4e) & 8) == 0) {
    if ((*(uint *)(param_1 + 0x286338) <= *(uint *)(param_1 + (param_4 + 0x2862d) * 0x10)) ||
       (iVar2 = ge_enq_req(param_1,param_3,param_4,param_1 + (uint)uVar1 * 0x620 + 0x2f6a0,bVar3),
       iVar2 != 1)) {
      RTMPFreeNdisPacket(param_1,param_3);
      (**(code **)(iVar4 + 0x3c))(param_1,bVar3);
      return 1;
    }
  }
  else {
    iVar2 = param_1 + 0x285b98;
    _raw_spin_lock_bh(iVar2);
    if (0x1ff < *(uint *)(param_1 + 0x285ba4)) {
      RTMPFreeNdisPacket(param_1,param_3);
      _raw_spin_unlock_bh(iVar2);
      return 1;
    }
    *param_3 = 0;
    if (*(undefined4 **)(param_1 + 0x285ba0) == (undefined4 *)0x0) {
      *(undefined4 **)(param_1 + 0x285b9c) = param_3;
    }
    else {
      **(undefined4 **)(param_1 + 0x285ba0) = param_3;
    }
    *(undefined4 **)(param_1 + 0x285ba0) = param_3;
    *(int *)(param_1 + 0x285ba4) = *(int *)(param_1 + 0x285ba4) + 1;
    _raw_spin_unlock_bh(iVar2);
  }
  (**(code **)(iVar4 + 0x3c))(param_1,0);
  return 0;
}

