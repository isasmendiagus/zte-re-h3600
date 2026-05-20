// module: mt7915.ko
// function: mtf_asic_set_rts_signal_ta @ 0x197224
// size: 260 bytes
//

undefined4 mtf_asic_set_rts_signal_ta(int param_1,int param_2,int param_3)

{
  uint local_20;
  uint local_1c [2];
  
  local_20 = 0;
  local_1c[0] = 0;
  if (param_2 == 0) {
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820e4000,&local_20);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820e4240,local_1c);
  }
  else {
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f4000,&local_20);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f4240,local_1c);
  }
  if (param_3 == 0) {
    local_20 = local_20 & 0xffffbfff;
    local_1c[0] = local_1c[0] & 0x7fffffff;
  }
  else {
    local_20 = local_20 | 0x4000;
    local_1c[0] = local_1c[0] | 0x80000000;
  }
  if (param_2 != 0) {
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820f4000);
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820f4240,local_1c[0]);
    return 1;
  }
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820e4000);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820e4240,local_1c[0]);
  return 1;
}

