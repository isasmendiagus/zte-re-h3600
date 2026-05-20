// module: mt7915.ko
// function: net_ad_set_low_power @ 0x25d5c4
// size: 64 bytes
//

undefined4 net_ad_set_low_power(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    return 0x606;
  }
  if (param_2 == 0) {
    MlmeLpExit();
    return 0;
  }
  MlmeLpEnter();
  return 0;
}

