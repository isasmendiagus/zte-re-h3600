// module: mt7915.ko
// function: ba_ori_session_setup @ 0xa5cec
// size: 536 bytes
//

void ba_ori_session_setup(int param_1,uint param_2,uint param_3,undefined4 param_4)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  
  if (2 < DebugLevel) {
    printk("%s: wcid = %d, tid = %d\n","ba_ori_session_setup",param_2,param_3);
  }
  if ((((*(char *)(param_1 + 0x286285) != '\0') || ("hif_set_WPDMA"[param_1 + 0xc] != '\x01')) &&
      ((*(uint *)(param_1 + 0xa3ac14) & 1) == 0)) &&
     ((*(int *)(param_1 + 0xa77bb4) != 1 ||
      ((*(uint *)(*(int *)(param_1 + 0xa77bb8) + 0x4e0) & 1) == 0)))) {
    if (param_3 < 8) {
      uVar2 = HcGetMaxStaNum(param_1);
      if (param_2 < uVar2) {
        iVar6 = param_1 + param_2 * 0x14c0 + 0xa1d20;
        if (((iVar6 != 0) &&
            (iVar5 = param_1 + param_2 * 0x14c0, puVar7 = (undefined4 *)(iVar5 + 0xa1d28),
            *(int *)(iVar5 + 0xa1d28) != 0)) &&
           (cVar1 = RTMPStaFixedTxMode(param_1,iVar6), 1 < (byte)(cVar1 - 1U))) {
          uVar3 = wlan_config_get_ba_tx_wsize(*puVar7);
          uVar4 = FUN_000a4a20(iVar6,uVar3,0);
          iVar6 = wlan_config_get_ppdu_caps(*puVar7);
          iVar5 = wlan_config_get_amsdu_en(*puVar7);
          uVar3 = 0;
          if ((iVar5 != 0) && (uVar3 = 0, *(char *)(iVar6 + 0x10) != '\0')) {
            uVar3 = 1;
          }
          iVar6 = ba_resrc_ori_prep(param_1,param_2,param_3,uVar4,uVar3,param_4);
          if (iVar6 != 0) {
            uVar3 = 3000;
            iVar6 = (uint)*(ushort *)(param_1 + (param_2 * 0xa60 + param_3 + 0x51500) * 2 + 4) *
                    0x48;
            if (((int)(uint)*(ushort *)(param_2 * 0x14c0 + param_1 + 0xa29e6) >> (param_3 & 0xff) &
                1U) == 0) {
              uVar3 = 10;
            }
            if (param_1 + 0x1c0 + iVar6 + 0x1b000 != 0) {
              RTMPSetTimer(param_1 + 0x1c0 + iVar6 + 0x1b010,uVar3);
              return;
            }
          }
        }
      }
    }
    else if (2 < DebugLevel) {
      printk("Wrong TID %d!\n",param_3);
      return;
    }
  }
  return;
}

