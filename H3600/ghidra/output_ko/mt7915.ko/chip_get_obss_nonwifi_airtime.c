// module: mt7915.ko
// function: chip_get_obss_nonwifi_airtime @ 0x189074
// size: 100 bytes
//

void chip_get_obss_nonwifi_airtime(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820e53b4,param_2);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f53b4,param_2 + 4);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820e53b8,param_2 + 8);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f53b8,param_2 + 0xc,param_4);
  return;
}

