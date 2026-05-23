// module: mt7915.ko
// function: chip_dump_wtbl_base_info @ 0x189cfc
// size: 32 bytes
//

void chip_dump_wtbl_base_info(void)

{
  if (DebugLevel < 1) {
    return;
  }
  printk("WTBL Basic Info:\n");
  return;
}

