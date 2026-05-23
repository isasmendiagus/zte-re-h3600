// module: mt7915.ko
// function: net_ad_set_sta_rec_bf_read @ 0x25d514
// size: 28 bytes
//

void net_ad_set_sta_rec_bf_read(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  Set_StaRecBfRead(uVar1,param_2);
  return;
}

