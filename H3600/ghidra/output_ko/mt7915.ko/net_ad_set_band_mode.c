// module: mt7915.ko
// function: net_ad_set_band_mode @ 0x25cc08
// size: 120 bytes
//

undefined4 net_ad_set_band_mode(int param_1,int *param_2)

{
  int iVar1;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    return 0x606;
  }
  if (*param_2 != 1) {
    return 0;
  }
  if (param_2[1] == 2) {
    Set_WirelessMode_Proc(iVar1,&_LC48);
    return 0;
  }
  if (param_2[1] != 1) {
    return 0x60a;
  }
  Set_WirelessMode_Proc(iVar1,&_LC49);
  return 0;
}

