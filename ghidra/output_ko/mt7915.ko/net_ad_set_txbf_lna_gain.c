// module: mt7915.ko
// function: net_ad_set_txbf_lna_gain @ 0x25d448
// size: 28 bytes
//

void net_ad_set_txbf_lna_gain(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  CmdTxBfLnaGain(uVar1,param_2);
  return;
}

