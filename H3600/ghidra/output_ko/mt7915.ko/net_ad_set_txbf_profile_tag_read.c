// module: mt7915.ko
// function: net_ad_set_txbf_profile_tag_read @ 0x25d4a8
// size: 36 bytes
//

void net_ad_set_txbf_profile_tag_read
               (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  uVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  TxBfProfileTagRead(uVar1,param_2,param_3,param_4);
  return;
}

