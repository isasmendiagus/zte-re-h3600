// module: mt7915.ko
// function: sta_send_mlme_pkt @ 0x533b8
// size: 232 bytes
//

undefined4 sta_send_mlme_pkt(int param_1,int param_2,int param_3,undefined4 param_4,char param_5)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  ushort uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar5 = *(int *)(param_2 + 0xcc);
  iVar6 = *(int *)("Get_RBIST_Raw_Data_Proc" + param_1 + 0x14);
  bVar1 = *(byte *)(iVar2 + 2);
  *(undefined1 *)(param_2 + 0x2d) = *(undefined1 *)(param_3 + 0xc);
  *(byte *)(param_2 + 0x3a) = *(byte *)(param_2 + 0x3a) | 8;
  if (iVar5 == 0) {
    RTMPFreeNdisPacket(param_1,param_2);
    return 1;
  }
  iVar7 = iVar5 + (uint)bVar1;
  iVar2 = MacTableLookup(param_1,iVar7 + 4);
  if (iVar2 == 0) {
    uVar4 = 0;
  }
  else {
    uVar4 = (ushort)*(byte *)(iVar2 + 0xe0);
  }
  *(ushort *)(param_2 + 0x42) = uVar4;
  iVar2 = in_altx_filter_list(iVar7);
  if (((iVar2 != 0) && ((*(byte *)(iVar5 + (uint)bVar1) & 0xc) == 0)) &&
     (*(char *)(param_2 + 0x36) != '\b')) {
    *(undefined1 *)(param_2 + 0x4f) = 3;
  }
  if (param_5 != '\0') {
    *(byte *)(param_2 + 0x3e) = *(byte *)(param_2 + 0x3e) | 1;
  }
                    /* WARNING: Could not recover jumptable at 0x00053484. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar3 = (**(code **)(iVar6 + 0x20))(param_1,param_3,param_2);
  return uVar3;
}

