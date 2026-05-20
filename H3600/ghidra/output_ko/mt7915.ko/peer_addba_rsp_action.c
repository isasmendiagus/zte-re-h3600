// module: mt7915.ko
// function: peer_addba_rsp_action @ 0xa7218
// size: 504 bytes
//

void peer_addba_rsp_action(int param_1,int param_2)

{
  ushort uVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  ushort *puVar7;
  int iVar8;
  
  puVar7 = (ushort *)(param_2 + 0x920);
  if (2 < DebugLevel) {
    printk("%s ==> Wcid(%d)\n","peer_addba_rsp_action",*puVar7);
  }
  uVar1 = *puVar7;
  uVar2 = HcGetMaxStaNum(param_1);
  if (uVar1 < uVar2) {
    uVar1 = *puVar7;
    iVar5 = (uint)uVar1 * 0x14c0;
    iVar6 = param_1 + iVar5 + 0xa1d20;
    if (((iVar6 != 0) && (*(int *)(param_1 + iVar5 + 0xa1d28) != 0)) &&
       (iVar5 = PeerAddBARspActionSanity(param_1,param_2,*(undefined4 *)(param_2 + 0x908)),
       iVar5 != 0)) {
      if (2 < DebugLevel) {
        printk("\t\t StatusCode = %d\n",*(undefined2 *)(param_2 + 0x1b));
      }
      if (*(short *)(param_2 + 0x1b) != 0) {
        if (*(short *)(param_2 + 0x1b) == 0x25) {
          iVar5 = (uint)*puVar7 * 0x14c0 + param_1;
          *(ushort *)(iVar5 + 0xa29e6) =
               *(ushort *)(iVar5 + 0xa29e6) |
               (ushort)(1 << (((uint)*(byte *)(param_2 + 0x1d) << 0x1a) >> 0x1c));
        }
        ba_ori_session_tear_down
                  (param_1,*puVar7,((uint)*(byte *)(param_2 + 0x1d) << 0x1a) >> 0x1c,1);
        return;
      }
      iVar8 = (uint)uVar1 * 0x14c0 + param_1;
      uVar3 = wlan_config_get_ba_tx_wsize(*(undefined4 *)(iVar8 + 0xa1d28));
      uVar3 = FUN_000a4a20(iVar6,uVar3,
                           (uint)*(byte *)(param_2 + 0x1e) << 2 |
                           (uint)(*(byte *)(param_2 + 0x1d) >> 6));
      iVar5 = wlan_config_get_ppdu_caps(*(undefined4 *)(iVar8 + 0xa1d28));
      iVar8 = wlan_config_get_amsdu_en(*(undefined4 *)(iVar8 + 0xa1d28));
      if (iVar8 == 0) {
        uVar4 = (uint)*(byte *)(param_2 + 0x1d);
        uVar2 = 0;
      }
      else {
        uVar4 = (uint)*(byte *)(param_2 + 0x1d);
        uVar2 = 0;
        if (*(char *)(iVar5 + 0x10) != '\0') {
          uVar2 = uVar4 & 1;
        }
      }
      iVar5 = ba_resrc_ori_add(param_1,*puVar7,(uVar4 << 0x1a) >> 0x1c,uVar3,uVar2,
                               *(undefined2 *)(param_2 + 0x1f));
      if (iVar5 != 0) {
        SendRefreshBAR(param_1,iVar6);
        return;
      }
      if (-1 < DebugLevel) {
        printk("%s(): add ori resrc fail\n","peer_addba_rsp_action");
        return;
      }
    }
  }
  return;
}

