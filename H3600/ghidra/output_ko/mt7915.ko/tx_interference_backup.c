// module: mt7915.ko
// function: tx_interference_backup @ 0x15da7c
// size: 180 bytes
//

void tx_interference_backup(int param_1)

{
  int iVar1;
  undefined4 local_14 [2];
  
  local_14[0] = 0;
  if (*(char *)(param_1 + 0xa7c545) != '\x01') {
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f2070,local_14);
    *(undefined4 *)(param_1 + 0xa7c538) = local_14[0];
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f2098,local_14);
    *(undefined4 *)(param_1 + 0xa7c53c) = local_14[0];
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f3340,local_14);
    iVar1 = DebugLevel;
    *(undefined4 *)(param_1 + 0xa7c540) = local_14[0];
    if (2 < iVar1) {
      printk("%s:: backup cr value([%x][%x])\n","tx_interference_backup",
             *(undefined4 *)(param_1 + 0xa7c538),*(undefined4 *)(param_1 + 0xa7c53c));
    }
  }
  return;
}

