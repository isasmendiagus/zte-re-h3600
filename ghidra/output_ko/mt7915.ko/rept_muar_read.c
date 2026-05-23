// module: mt7915.ko
// function: rept_muar_read @ 0x75154
// size: 384 bytes
//

void rept_muar_read(int param_1,byte param_2)

{
  uint local_18;
  undefined4 local_14;
  
  __memzero(&local_18,4);
  __memzero(&local_14,4);
  local_14 = CONCAT13(local_14._3_1_ & 0xc0 | (param_2 & 0x1f) << 1,(int3)local_14) | 0x10000;
  hw_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820f5260,local_14);
  do {
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f5260,&local_14);
  } while ((local_14 & 0x10000) != 0);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f525c,&local_18);
  printk("%02x:%02x:%02x:%02x:%02x:%02x  ",local_18 & 0xff,(local_18 << 0x10) >> 0x18,
         (local_18 << 8) >> 0x18,local_18 >> 0x18,local_14 & 0xff,local_14 >> 8 & 0xff);
  __memzero(&local_18,4);
  __memzero(&local_14,4);
  local_14 = CONCAT13(local_14._3_1_ & 0xc0 | param_2 * '\x02' + 1 & 0x3f,(int3)local_14) | 0x10000;
  hw_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820f5260,local_14);
  do {
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f5260,&local_14);
  } while ((local_14 & 0x10000) != 0);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f525c,&local_18);
  printk("%02x:%02x:%02x:%02x:%02x:%02x\n",local_18 & 0xff,(local_18 << 0x10) >> 0x18,
         (local_18 << 8) >> 0x18,local_18 >> 0x18,local_14 & 0xff,local_14 >> 8 & 0xff);
  return;
}

