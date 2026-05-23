// module: mt7915.ko
// function: MtfDmacSetExtMbssEnableCR @ 0x1967f0
// size: 132 bytes
//

void MtfDmacSetExtMbssEnableCR(int param_1,uint param_2,int param_3)

{
  uint local_14 [2];
  
  if (param_3 == 0) {
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f5258,local_14);
    local_14[0] = local_14[0] & ~(1 << (param_2 & 0xff));
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820f5258);
    return;
  }
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f5258,local_14);
  local_14[0] = local_14[0] | 1 << (param_2 & 0xff);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820f5258);
  return;
}

