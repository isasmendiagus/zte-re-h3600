// module: mt7915.ko
// function: chip_get_sta_pause @ 0x1890d8
// size: 200 bytes
//

void chip_get_sta_pause(int param_1,int param_2)

{
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c0400,param_2);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c0404,param_2 + 4);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c0408,param_2 + 8);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c040c,param_2 + 0xc);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c0410,param_2 + 0x10);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c0414,param_2 + 0x14);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c0418,param_2 + 0x18);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c041c,param_2 + 0x1c);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c041c,param_2 + 0x20);
  return;
}

