// module: mt7915.ko
// function: net_ad_free_pkt @ 0x25c8c4
// size: 48 bytes
//

undefined4 net_ad_free_pkt(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 != 0) {
    RTMPFreeNdisPacket(iVar1,param_2);
    return 0;
  }
  return 0x606;
}

