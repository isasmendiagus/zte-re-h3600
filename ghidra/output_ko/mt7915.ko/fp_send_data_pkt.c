// module: mt7915.ko
// function: fp_send_data_pkt @ 0xcd90c
// size: 336 bytes
//

undefined4 fp_send_data_pkt(int param_1,int param_2,int param_3)

{
  undefined1 uVar1;
  ushort uVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int local_40;
  int local_3c;
  undefined4 local_38;
  undefined1 auStack_34 [4];
  undefined1 auStack_30 [20];
  
  uVar2 = *(ushort *)(param_3 + 0x42);
  iVar5 = *(int *)("Get_RBIST_Raw_Data_Proc" + param_1 + 0x14);
  local_40 = 0;
  local_3c = 0;
  RTMP_QueryPacketInfo(param_3,auStack_30,&local_38,auStack_34);
  uVar1 = *(undefined1 *)(param_3 + 0x2a);
  if ((uVar2 == 0) || (*(int *)(param_1 + (uint)uVar2 * 0x620 + 0x2f6a0) != 0x400))
  goto LAB_000cd978;
  if (*(char *)(param_2 + 0x890) != '\0') {
    iVar3 = IgmpPktInfoQuery(param_1,local_38,param_3,param_2,&local_40,&local_3c);
    if (iVar3 != 0) {
      return 1;
    }
    if (local_40 == 2) {
      if (local_3c == 0) goto LAB_000cd9a8;
      iVar3 = IgmpMemberCnt(local_3c + 0x18);
      if (iVar3 != 0) goto LAB_000cd9f4;
    }
    if (local_40 == 3) {
LAB_000cd9f4:
      uVar4 = IgmpPktClone(param_1,param_2,param_3,local_40,local_3c,1,uVar1,
                           *(undefined4 *)(param_3 + 0x18));
      RTMPFreeNdisPacket(param_1,param_3);
      return uVar4;
    }
  }
LAB_000cd9a8:
  *(undefined1 *)(param_3 + 0x36) = 1;
LAB_000cd978:
  (**(code **)(iVar5 + 0x24))(param_1,param_2,param_3,*(undefined1 *)(param_3 + 0x4d));
  return 0;
}

