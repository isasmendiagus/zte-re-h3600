// module: mt7915.ko
// function: ap_mlme_disassoc_req_action @ 0x5195c
// size: 16 bytes
//

void ap_mlme_disassoc_req_action(undefined4 param_1,int param_2)

{
  APMlmeKickOutSta(param_1,param_2,*(undefined2 *)(param_2 + 0x920),*(undefined2 *)(param_2 + 6));
  return;
}

