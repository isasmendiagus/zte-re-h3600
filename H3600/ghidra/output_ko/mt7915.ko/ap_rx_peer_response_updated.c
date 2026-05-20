// module: mt7915.ko
// function: ap_rx_peer_response_updated @ 0x4b048
// size: 676 bytes
//

undefined4 ap_rx_peer_response_updated(int param_1,undefined4 param_2,int param_3,int param_4)

{
  undefined1 uVar1;
  ushort uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  int *piVar8;
  int iVar9;
  byte local_5e [2];
  undefined4 *local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined1 auStack_4c [4];
  undefined1 local_48;
  undefined1 local_47;
  undefined1 local_46;
  undefined1 local_45;
  
  uVar1 = *(undefined1 *)(param_4 + 0x91f);
  local_58 = 0;
  local_54 = 0;
  local_50 = 0;
  local_5c = (undefined4 *)0x0;
  local_5e[0] = 0;
  local_5e[1] = 0;
  iVar3 = get_scan_tab_by_wdev();
  uVar2 = *(ushort *)(param_4 + 0x920);
  uVar4 = HcGetMaxStaNum(param_1);
  if ((uVar2 < uVar4) && (iVar5 = MacTableLookup(param_1,param_3), iVar5 != 0)) {
    uVar1 = *(undefined1 *)(*(int *)(iVar5 + 8) + 0x1a);
  }
  local_46 = *(undefined1 *)(param_4 + 0x91a);
  local_48 = *(undefined1 *)(param_4 + 0x918);
  local_47 = *(undefined1 *)(param_4 + 0x919);
  local_45 = *(undefined1 *)(param_4 + 0x91b);
  iVar5 = rtmp_avg_rssi(param_1,auStack_4c);
  if ((*(char *)(param_1 + 0x795651) < iVar5) && ((*(byte *)(param_3 + 0xdd) & 0x40) != 0)) {
    Handle_BSS_Width_Trigger_Events(param_1,uVar1);
  }
  local_5c = &local_58;
  SupportRate(param_3 + 0xac,&local_5c,local_5e,local_5e + 1);
  if ((((*(byte *)(param_3 + 0x36) & 1) != 0) || (local_5e[0] < 5)) &&
     (*(int *)(param_1 + 0x795078) == 0)) {
    *(undefined4 *)(&DAT_0036b8a4 + param_1) = *(undefined4 *)(param_1 + 0x7960e8);
  }
  if ((*(uint *)(param_3 + 0xa8) & 1) == 0) {
    *(undefined4 *)(&DAT_0036b8a8 + param_1) = *(undefined4 *)(param_1 + 0x7960e8);
  }
  if (*(char *)(param_1 + 0x795651) < iVar5) {
    bss_coex_insert_effected_ch_list(param_1,uVar1,param_3,param_2);
  }
  iVar9 = param_3 + 6;
  iVar6 = BssTableSearch(iVar3,iVar9,*(undefined1 *)(param_3 + 0x30));
  if (iVar6 != -1) {
    iVar3 = iVar6 * 0xaf4 + iVar3;
    *(undefined1 *)(iVar3 + 0x6ca) = 0;
    if (*(char *)(param_3 + 0x95) != '\0') {
      if (*(char *)(param_3 + 0x96) != '\0') {
        *(undefined1 *)(iVar3 + 0x6ca) = 1;
      }
      if (*(char *)(param_3 + 0x30) != (&DAT_0036b860)[param_1]) {
        return 1;
      }
      goto LAB_0004b1fc;
    }
  }
  if (*(char *)(param_3 + 0x30) != (&DAT_0036b860)[param_1]) {
    return 1;
  }
LAB_0004b1fc:
  uVar7 = HcGetBandByWdev(param_2);
  piVar8 = (int *)HcGetAutoChCtrlbyBandIdx(param_1,uVar7);
  if ((*piVar8 != 0) &&
     (iVar3 = AutoChBssSearchWithSSID
                        (param_1,iVar9,param_3 + 0xc,*(undefined1 *)(param_3 + 0x2c),
                         *(undefined1 *)(param_3 + 0x30),param_2), iVar3 == -1)) {
    iVar3 = *piVar8 + (uint)(byte)(&DAT_0036b861)[param_1] * 4;
    *(int *)(iVar3 + 0xf0) = *(int *)(iVar3 + 0xf0) + 1;
  }
  AutoChBssInsertEntry
            (param_1,iVar9,param_3 + 0xc,*(undefined1 *)(param_3 + 0x2c),
             *(undefined1 *)(param_3 + 0x30),*(undefined1 *)(param_3 + 0xa3),iVar5,param_2);
  return 1;
}

