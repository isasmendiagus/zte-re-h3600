// module: mt7915.ko
// function: chip_get_dis_sta_map @ 0x1891a0
// size: 200 bytes
//

void chip_get_dis_sta_map(int param_1,int param_2)

{
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c0440,param_2);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c0444,param_2 + 4);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c0448,param_2 + 8);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c044c,param_2 + 0xc);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c0450,param_2 + 0x10);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c0454,param_2 + 0x14);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c0458,param_2 + 0x18);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c045c,param_2 + 0x1c);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c045c,param_2 + 0x20);
  return;
}

