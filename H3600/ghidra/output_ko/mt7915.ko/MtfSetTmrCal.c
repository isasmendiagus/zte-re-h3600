// module: mt7915.ko
// function: MtfSetTmrCal @ 0x196f1c
// size: 96 bytes
//

void MtfSetTmrCal(int param_1)

{
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f40c0);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820f40c0);
  return;
}

