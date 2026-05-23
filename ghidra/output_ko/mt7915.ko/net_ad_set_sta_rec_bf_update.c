// module: mt7915.ko
// function: net_ad_set_sta_rec_bf_update @ 0x25d4f8
// size: 28 bytes
//

void net_ad_set_sta_rec_bf_update(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  Set_StaRecBfUpdate(uVar1,param_2);
  return;
}

