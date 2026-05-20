// module: mt7915.ko
// function: sta_assoc_init @ 0x8031c
// size: 508 bytes
//

void sta_assoc_init(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = *(undefined4 *)(param_1 + 8);
  iVar1 = GetStaCfgByWdev(uVar2,param_1);
  if (iVar1 != 0) {
    *(undefined1 **)(param_1 + 0xc98) = sta_assoc_api;
    *(undefined4 *)(param_1 + 0xbdc) = 0;
    sta_assoc_api._0_4_ = sta_mlme_assoc_req_action;
    sta_assoc_api._4_4_ = sta_peer_assoc_rsp_action;
    sta_assoc_api._8_4_ = sta_mlme_assoc_req_timeout_action;
    sta_assoc_api._12_4_ = sta_mlme_reassoc_req_action;
    sta_assoc_api._16_4_ = sta_peer_reassoc_rsp_action;
    sta_assoc_api._20_4_ = sta_mlme_reassoc_req_timeout_action;
    sta_assoc_api._32_4_ = sta_mlme_disassoc_req_action;
    sta_assoc_api._36_4_ = sta_peer_disassoc_action;
    sta_assoc_api._40_4_ = sta_mlme_disassoc_req_timeout_action;
    if (*(char *)(iVar1 + 0x211ed0) == '\0') {
      *(undefined4 *)(iVar1 + 0x211f74) = uVar2;
      *(int *)(iVar1 + 0x211f78) = param_1;
      RTMPInitTimer(uVar2,iVar1 + 0x211eb4,rtmp_timer_sta_assoc_timeout,iVar1 + 0x211f74,0);
    }
    if (*(char *)(iVar1 + 0x211f04) == '\0') {
      *(undefined4 *)(bn_mul_normal + iVar1) = uVar2;
      *(int *)(iVar1 + 0x211f84) = param_1;
      RTMPInitTimer(uVar2,iVar1 + 0x211ee8,rtmp_timer_sta_reassoc_timeout,bn_mul_normal + iVar1,0);
    }
    if (*(char *)(iVar1 + 0x211f38) == '\0') {
      *(undefined4 *)(iVar1 + 0x211f8c) = uVar2;
      *(int *)(iVar1 + 0x211f90) = param_1;
      RTMPInitTimer(uVar2,BN_mod_sqr + iVar1,rtmp_timer_sta_disassoc_timeout,iVar1 + 0x211f8c,0);
    }
    if (*(char *)(iVar1 + 0x21248c) == '\0') {
      RTMPInitTimer(uVar2,iVar1 + 0x212470,rtmp_timer_sta_link_down_exec,param_1,0);
    }
    if (*(char *)(iVar1 + 0x2123bc) == '\0') {
      RTMPInitTimer(uVar2,iVar1 + 0x2123a0,rtmp_timer_WpaDisassocApAndBlockAssoc,param_1,0);
    }
    return;
  }
  printk(&_LC1,0xa3f);
  dump_stack();
  return;
}

