// module: mt7915.ko
// function: chip_get_ple_txcmd_stat @ 0x189268
// size: 28 bytes
//

void chip_get_ple_txcmd_stat(int param_1,undefined4 param_2)

{
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c022c,param_2);
  return;
}

