// module: mt7915.ko
// function: tx_interference_restore @ 0x15db34
// size: 164 bytes
//

void tx_interference_restore(int param_1)

{
  int iVar1;
  
  if (*(char *)(param_1 + 0xa7c545) != '\0') {
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820f2070,
                   *(undefined4 *)(param_1 + 0xa7c538));
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820f2098,
                   *(undefined4 *)(param_1 + 0xa7c53c));
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820f3340,
                   *(undefined4 *)(param_1 + 0xa7c540));
    iVar1 = DebugLevel;
    *(undefined1 *)(param_1 + 0xa7c545) = 0;
    if (2 < iVar1) {
      printk("%s:: ---Enter---(value=0x%x, 0x%x, 0x%x)\n","tx_interference_restore",
             *(undefined4 *)(param_1 + 0xa7c538),*(undefined4 *)(param_1 + 0xa7c53c),
             *(undefined4 *)(param_1 + 0xa7c540));
    }
  }
  return;
}

