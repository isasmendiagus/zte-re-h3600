// module: mt7915.ko
// function: net_ad_rx_done_handle @ 0x25cb48
// size: 188 bytes
//

undefined4 net_ad_rx_done_handle(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  uint local_18;
  uint local_14 [2];
  
  local_18 = 0;
  local_14[0] = 0;
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    uVar2 = 0x606;
  }
  else {
    if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + iVar1 + 0xc) & 0xffff) != 0x7915) {
      mac_io_read32(*(undefined4 *)(iVar1 + 0xa797a0),0x820f5030,&local_18);
      mac_io_read32(*(undefined4 *)(iVar1 + 0xa797a0),0x820f5130,local_14);
      uVar3 = (uint)*(ushort *)(param_2 + 0x80);
      if ((uVar3 != local_18) && (uVar3 != local_14[0])) {
        printk("%s: wrong chfreq!!\n\tRXD.ch_freq=%u, chfreq0=%u, chfreq1=%u\n",
               "net_ad_rx_done_handle",uVar3,local_18,local_14[0]);
        return 0x60a;
      }
    }
    uVar2 = 0;
  }
  return uVar2;
}

