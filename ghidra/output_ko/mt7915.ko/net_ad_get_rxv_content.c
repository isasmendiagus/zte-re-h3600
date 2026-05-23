// module: mt7915.ko
// function: net_ad_get_rxv_content @ 0x25e3d4
// size: 56 bytes
//

undefined4 net_ad_get_rxv_content(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 != 0) {
    chip_get_rxv_content(iVar1,param_2,param_3);
    return 0;
  }
  return 0x606;
}

