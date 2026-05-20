// module: mt7915.ko
// function: rx_isr_th_backup @ 0x15dbdc
// size: 364 bytes
//

void rx_isr_th_backup(int param_1)

{
  int iVar1;
  undefined4 local_14;
  
  local_14 = 0;
  if (*(char *)(param_1 + 0xa7c544) != '\x01') {
    if (2 < DebugLevel) {
      printk("%s:: ---Enter---\n","rx_isr_th_backup");
    }
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x8309605c,&local_14);
    *(undefined4 *)(param_1 + 0xa7c51c) = local_14;
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x830960a8,&local_14);
    *(undefined4 *)(param_1 + 0xa7c520) = local_14;
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x830a740c,&local_14);
    *(undefined4 *)(param_1 + 0xa7c524) = local_14;
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x830a744c,&local_14);
    *(undefined4 *)(param_1 + 0xa7c528) = local_14;
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x83020280,&local_14);
    *(undefined4 *)(param_1 + 0xa7c52c) = local_14;
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x83030280,&local_14);
    *(undefined4 *)(param_1 + 0xa7c530) = local_14;
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x8309f05c,&local_14);
    iVar1 = DebugLevel;
    *(undefined4 *)(param_1 + 0xa7c534) = local_14;
    if (2 < iVar1) {
      printk("%s:: backup cr value([%x][%x][%x][%x][%x][%x][%x])\n","rx_isr_th_backup",
             *(undefined4 *)(param_1 + 0xa7c51c),*(undefined4 *)(param_1 + 0xa7c520),
             *(undefined4 *)(param_1 + 0xa7c524),*(undefined4 *)(param_1 + 0xa7c528),
             *(undefined4 *)(param_1 + 0xa7c52c),*(undefined4 *)(param_1 + 0xa7c530),local_14);
    }
  }
  return;
}

