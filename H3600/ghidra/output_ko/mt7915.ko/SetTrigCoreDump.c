// module: mt7915.ko
// function: SetTrigCoreDump @ 0x2fb68
// size: 100 bytes
//

undefined4 SetTrigCoreDump(int param_1)

{
  if (0 < DebugLevel) {
    printk("Manual trigger Fw Core dump\n");
  }
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x89010108,0x40000);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x89010118,0x40000);
  return 1;
}

