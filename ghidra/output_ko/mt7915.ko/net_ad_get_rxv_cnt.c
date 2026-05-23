// module: mt7915.ko
// function: net_ad_get_rxv_cnt @ 0x25e39c
// size: 56 bytes
//

undefined4 net_ad_get_rxv_cnt(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 != 0) {
    chip_get_rxv_cnt(iVar1,param_2,param_3);
    return 0;
  }
  return 0x606;
}

