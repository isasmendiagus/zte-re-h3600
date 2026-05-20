// module: mt7915.ko
// function: sta_auth_init @ 0x76e28
// size: 252 bytes
//

void sta_auth_init(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = *(undefined4 *)(param_1 + 8);
  iVar1 = GetStaCfgByWdev(uVar2,param_1);
  if (iVar1 != 0) {
    *(undefined1 **)(param_1 + 0xedc) = sta_auth_api;
    *(undefined4 *)(param_1 + 0xe30) = 0;
    sta_auth_api._24_4_ = sta_mlme_deauth_req_action;
    sta_auth_api._0_4_ = sta_mlme_auth_req_action;
    sta_auth_api._4_4_ = sta_auth_timeout_action;
    sta_auth_api._28_4_ = sta_peer_deauth_action;
    sta_auth_api._8_4_ = sta_peer_auth_rsp_at_seq2_action;
    sta_auth_api._12_4_ = sta_peer_auth_rsp_at_seq4_action;
    sta_auth_api._32_4_ = sta_sae_auth_req_action;
    sta_auth_api._36_4_ = sta_sae_auth_rsp_action;
    if (BN_mod_lshift[iVar1 + 4] == (code)0x0) {
      *(undefined4 *)(iVar1 + 0x211f68) = uVar2;
      *(int *)(iVar1 + 0x211f6c) = param_1;
      RTMPInitTimer(uVar2,iVar1 + 0x211e80,rtmp_timer_sta_auth_timeout,iVar1 + 0x211f68,0);
    }
    return;
  }
  printk(&_LC3,0x35a);
  dump_stack();
  return;
}

