// module: mt7915.ko
// function: chip_get_ple_acq_stat @ 0x189284
// size: 740 bytes
//

void chip_get_ple_acq_stat(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c00b0,param_2);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c0500,param_2 + 4);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c0504,param_2 + 8);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c0508,param_2 + 0xc);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c050c,param_2 + 0x10);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c0510,param_2 + 0x14);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c0514,param_2 + 0x18);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c0518,param_2 + 0x1c);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c0520,param_2 + 0x24);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c0540,param_2 + 0x28);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c0544,param_2 + 0x2c);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c0548,param_2 + 0x30);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c054c,param_2 + 0x34);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c0550,param_2 + 0x38);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c0554,param_2 + 0x3c);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c0558,param_2 + 0x40);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c055c,param_2 + 0x44);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c0560,param_2 + 0x48);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c0580,param_2 + 0x4c);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c0584,param_2 + 0x50);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c0588,param_2 + 0x54);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c058c,param_2 + 0x58);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c0590,param_2 + 0x5c);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c0594,param_2 + 0x60);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c0598,param_2 + 100);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c059c,param_2 + 0x68);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c05a0,param_2 + 0x6c);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c05c0,param_2 + 0x70);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c05c4,param_2 + 0x74);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c05c8,param_2 + 0x78);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c05cc,param_2 + 0x7c);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c05d0,param_2 + 0x80);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c05d4,param_2 + 0x84);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c05d8,param_2 + 0x88);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c05dc,param_2 + 0x8c);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c05e0,param_2 + 0x90,param_4);
  return;
}

