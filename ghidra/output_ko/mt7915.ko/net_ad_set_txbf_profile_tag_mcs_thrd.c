// module: mt7915.ko
// function: net_ad_set_txbf_profile_tag_mcs_thrd @ 0x25d4cc
// size: 44 bytes
//

undefined4 net_ad_set_txbf_profile_tag_mcs_thrd(int param_1,undefined4 param_2,undefined4 param_3)

{
  RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  TxBfProfileTag_McsThd(0,param_2,param_3);
  return 0;
}

