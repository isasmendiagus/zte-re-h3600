// module: mt7915.ko
// function: ap_assoc_init @ 0x51734
// size: 68 bytes
//

void ap_assoc_init(int param_1)

{
  *(undefined1 **)(param_1 + 0xc98) = ap_assoc_api;
  ap_assoc_api._24_4_ = ap_peer_assoc_req_action;
  ap_assoc_api._28_4_ = ap_peer_reassoc_req_action;
  ap_assoc_api._32_4_ = ap_mlme_disassoc_req_action;
  ap_assoc_api._36_4_ = ap_peer_disassoc_action;
  return;
}

