// module: mt7915.ko
// function: ap_auth_init @ 0x4e0f4
// size: 68 bytes
//

void ap_auth_init(int param_1)

{
  *(undefined1 **)(param_1 + 0xedc) = ap_auth_api;
  ap_auth_api._24_4_ = ap_mlme_deauth_req_action;
  ap_auth_api._28_4_ = ap_peer_deauth_action;
  ap_auth_api._16_4_ = ap_peer_auth_req_at_idle_action;
  ap_auth_api._20_4_ = ap_peer_auth_confirm_action;
  return;
}

