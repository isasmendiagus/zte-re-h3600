// module: mt7915.ko
// function: ap_send_data_pkt @ 0x1a210
// size: 804 bytes
//

undefined4 ap_send_data_pkt(int param_1,int param_2,int param_3)

{
  undefined1 uVar1;
  undefined1 uVar2;
  ushort uVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  code *pcVar12;
  int local_30;
  int local_2c [2];
  
  uVar3 = *(ushort *)(param_3 + 0x42);
  uVar1 = *(undefined1 *)(param_3 + 0x2a);
  iVar8 = param_1 + 0x1c0;
  iVar11 = *(int *)("Get_RBIST_Raw_Data_Proc" + param_1 + 0x14);
  local_30 = 0;
  iVar4 = (uint)uVar3 * 0x620;
  local_2c[0] = 0;
  uVar2 = *(undefined1 *)(param_3 + 0x4d);
  iVar7 = iVar8 + iVar4 + 0x2f4e0;
  if (*(int *)(param_1 + iVar4 + 0x2f6a0) == 0x400) {
    if (*(char *)(param_2 + 0x890) != '\0') {
      iVar4 = IgmpPktInfoQuery(param_1,*(undefined4 *)(param_3 + 0xcc),param_3,param_2,&local_30,
                               local_2c);
      if (iVar4 != 0) {
        return 1;
      }
      if (((local_30 == 2) && (local_2c[0] != 0)) &&
         (iVar4 = IgmpMemberCnt(local_2c[0] + 0x18), iVar4 != 0)) {
        uVar5 = IgmpPktClone(param_1,param_2,param_3,local_30,local_2c[0],uVar2,uVar1,
                             *(undefined4 *)(param_3 + 0x18));
        *(int *)(param_1 + 0x9db8c) = *(int *)(param_1 + 0x9db8c) + 1;
        RTMPFreeNdisPacket(param_1,param_3);
        return uVar5;
      }
    }
    *(undefined1 *)(param_3 + 0x36) = 1;
  }
  else {
    (**(code **)(*(int *)(param_2 + 0x904) + 0x84))(param_1,param_2,uVar1,1);
  }
  *(undefined1 *)(param_3 + 0x2a) = uVar1;
  iVar4 = (uint)uVar3 * 0x620;
  iVar10 = iVar8 + iVar4 + 0x2f588;
  _raw_spin_lock_bh(iVar10);
  iVar6 = param_1 + iVar4;
  if (*(char *)(iVar6 + 0x2f72c) == '\0') {
    pcVar12 = *(code **)(iVar11 + 0x24);
LAB_0001a2ec:
    (*pcVar12)(param_1,param_2,param_3,uVar2);
  }
  else {
    iVar11 = *(int *)("Get_RBIST_Raw_Data_Proc" + param_1 + 0x14);
    uVar9 = *(int *)(iVar6 + 0x2f714) + (uint)*(ushort *)(iVar8 + iVar4 + 0x2faf8) & 0xffff;
    if (uVar9 < 0x20) {
      if (*(uint *)(iVar6 + 0x2f70c) == 0) {
LAB_0001a414:
        pcVar12 = *(code **)(iVar11 + 0x24);
        goto LAB_0001a2ec;
      }
      uVar9 = 0x20 - uVar9 & 0xffff;
      do {
        iVar4 = (**(code **)(iVar11 + 0x34))(param_1,iVar7);
        if (iVar4 == 0) {
          if (uVar9 != 0) goto LAB_0001a414;
          break;
        }
        uVar9 = uVar9 - 1 & 0xffff;
        *(int *)("Get_RBIST_Capture_Status" + param_1 + 0x10) =
             *(int *)("Get_RBIST_Capture_Status" + param_1 + 0x10) + -1;
        (**(code **)(iVar11 + 0x24))(param_1,param_2,iVar4,uVar2);
      } while (uVar9 != 0);
      pcVar12 = *(code **)(iVar11 + 0x38);
    }
    else {
      if ((0x1f < *(uint *)(iVar6 + 0x2f70c)) ||
         (0x3ff < *(uint *)("Get_RBIST_Capture_Status" + param_1 + 0x10))) {
        wlan_dbg_radio_statistics_inc(0,8);
        RTMPFreeNdisPacket(param_1,param_3);
        goto LAB_0001a300;
      }
      pcVar12 = *(code **)(iVar11 + 0x38);
      if (pcVar12 == (code *)0x0) {
        if (-1 < DebugLevel) {
          printk("%s no enq_psq_pkt handler\n","ap_ps_handle");
        }
        RTMPFreeNdisPacket(param_1,param_3);
        goto LAB_0001a300;
      }
    }
    (*pcVar12)(param_1,param_2,iVar7,param_3);
    *(int *)("Get_RBIST_Capture_Status" + param_1 + 0x10) =
         *(int *)("Get_RBIST_Capture_Status" + param_1 + 0x10) + 1;
  }
LAB_0001a300:
  _raw_spin_unlock_bh(iVar10);
  ba_ori_session_start(param_1,iVar7,uVar1);
  return 0;
}

