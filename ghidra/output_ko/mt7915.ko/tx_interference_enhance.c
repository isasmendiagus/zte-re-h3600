// module: mt7915.ko
// function: tx_interference_enhance @ 0x15d9e4
// size: 148 bytes
//

void tx_interference_enhance(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (*(char *)(param_1 + 0xa7c545) == '\x01') {
    return;
  }
  if (2 < DebugLevel) {
    printk("%s:: ---Enter---\n","tx_interference_enhance",param_3,DebugLevel,param_4);
  }
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820f2070,1);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820f2098,0x4001fc0);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820f3340,0);
  *(undefined1 *)(param_1 + 0xa7c545) = 1;
  return;
}

