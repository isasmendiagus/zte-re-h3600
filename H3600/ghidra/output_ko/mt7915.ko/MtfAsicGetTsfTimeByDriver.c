// module: mt7915.ko
// function: MtfAsicGetTsfTimeByDriver @ 0x1954d0
// size: 140 bytes
//

undefined4 MtfAsicGetTsfTimeByDriver(int param_1,undefined4 param_2,undefined4 param_3)

{
  uint local_1c [2];
  
  local_1c[0] = 0;
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820eb0a8,local_1c);
  local_1c[0] = local_1c[0] & 0xc | 3;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820eb0a8);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820eb080,param_3);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820eb084,param_2);
  return 1;
}

