// module: mt7915.ko
// function: chip_show_protect_info @ 0x18a000
// size: 212 bytes
//

undefined4 chip_show_protect_info(int param_1)

{
  int iVar1;
  undefined4 local_14;
  
  iVar1 = *(int *)(param_1 + 0x4328);
  if (0 < DebugLevel) {
    printk(" -Proetction\n");
  }
  mac_io_read32(*(undefined4 *)(iVar1 + 0xa797a0),0x820f2058,&local_14);
  if (0 < DebugLevel) {
    printk("  > AGG_PCR 0x%08x\n",local_14);
    if (0 < DebugLevel) {
      printk(" -RTS Threshold\n");
    }
  }
  mac_io_read32(*(undefined4 *)(iVar1 + 0xa797a0),0x820f205c,&local_14);
  if (0 < DebugLevel) {
    printk("  > AGG_PCR1 0x%08x\n",local_14);
  }
  return 1;
}

