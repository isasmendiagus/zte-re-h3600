// module: mt7915.ko
// function: net_ad_write_mac_bbp_reg @ 0x25d644
// size: 68 bytes
//

undefined4 net_ad_write_mac_bbp_reg(int param_1,undefined4 *param_2)

{
  int iVar1;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 != 0) {
    mac_io_write32(*(undefined4 *)(iVar1 + 0xa797a0),*param_2,*(undefined4 *)param_2[2]);
    return 0;
  }
  return 0x606;
}

