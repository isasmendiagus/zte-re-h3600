// module: mt7915.ko
// function: ap_send_mlme_pkt @ 0x1e2d4
// size: 392 bytes
//

undefined4 ap_send_mlme_pkt(int param_1,int param_2,int param_3,undefined4 param_4,char param_5)

{
  undefined2 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar7 = *(int *)(param_2 + 0xcc);
  iVar4 = *(int *)("Get_RBIST_Raw_Data_Proc" + param_1 + 0x14);
  uVar5 = (uint)*(byte *)(iVar2 + 2);
  *(undefined1 *)(param_2 + 0x2d) = *(undefined1 *)(param_3 + 0xc);
  *(byte *)(param_2 + 0x3a) = *(byte *)(param_2 + 0x3a) | 8;
  if (iVar7 != 0) {
    iVar2 = iVar7 + uVar5;
    iVar6 = iVar2 + 4;
    uVar1 = ap_mlme_search_wcid(param_1,iVar6,iVar2 + 10,param_2,param_3);
    *(undefined2 *)(param_2 + 0x42) = uVar1;
    iVar2 = in_altx_filter_list(iVar2);
    if (((iVar2 != 0) && ((*(byte *)(iVar7 + uVar5) & 0xc) == 0)) &&
       (*(char *)(param_2 + 0x36) != '\b')) {
      *(undefined1 *)(param_2 + 0x4f) = 3;
    }
    if (param_5 != '\0') {
      if ((*(byte *)(iVar7 + uVar5) & 0xf0) == 0xc0) {
        *(undefined1 *)(param_2 + 0x32) = 0xff;
        iVar2 = MacTableLookup(param_1,iVar6);
        if (iVar2 != 0) {
          *(undefined2 *)(param_2 + 0x42) = *(undefined2 *)(iVar2 + 0xe0);
        }
      }
      else {
        *(undefined1 *)(param_2 + 0x32) = 0;
      }
      *(byte *)(param_2 + 0x3e) = *(byte *)(param_2 + 0x3e) | 1;
    }
    iVar2 = MacTableLookup(param_1,iVar6);
    if ((iVar2 != 0) || (*(char *)(param_2 + 0x4f) == '\x03')) {
                    /* WARNING: Could not recover jumptable at 0x0001e3b8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      uVar3 = (**(code **)(iVar4 + 0x20))(param_1,param_3,param_2);
      return uVar3;
    }
    if (-1 < DebugLevel) {
      printk("%s pkt from non-connected sta, type=%d, sub_type=%d to ACQ, drop\n","ap_send_mlme_pkt"
             ,((uint)*(byte *)(iVar7 + uVar5) << 0x1c) >> 0x1e,*(byte *)(iVar7 + uVar5) >> 4);
    }
  }
  RTMPFreeNdisPacket(param_1,param_2);
  return 1;
}

