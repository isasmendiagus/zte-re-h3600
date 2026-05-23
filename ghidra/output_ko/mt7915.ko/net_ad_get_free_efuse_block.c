// module: mt7915.ko
// function: net_ad_get_free_efuse_block @ 0x25db20
// size: 48 bytes
//

undefined4 net_ad_get_free_efuse_block(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 != 0) {
    eFuseGetFreeBlockCount(iVar1,param_2 + 0xc);
    return 0;
  }
  return 0x606;
}

