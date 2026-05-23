// module: mt7915.ko
// function: ZTE_wlan_edcca_setting @ 0x15ef70
// size: 136 bytes
//

void ZTE_wlan_edcca_setting(int param_1,int param_2)

{
  uint local_10;
  uint local_c;
  
  if (param_2 != 0) {
    return;
  }
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x83088554,&local_10);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x83088558,&local_c);
  local_10 = local_10 & 0xffffff00 | 0xce;
  local_c = local_c & 0xffffff00 | 0xd8;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x83088554);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x83088558,local_c);
  return;
}

