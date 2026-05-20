// module: mt7915.ko
// function: chip_set_fw_cp_util_en @ 0x18fb90
// size: 156 bytes
//

undefined4 chip_set_fw_cp_util_en(int param_1,int param_2)

{
  undefined4 uVar1;
  
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f04c);
  hw_io_write32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f04c);
  if (param_2 == 0) {
    uVar1 = 0x2005;
  }
  else {
    uVar1 = 0x2004;
  }
  hw_io_write32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f010,uVar1);
  hw_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x89010080,0x20);
  hw_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x890100c0,0x20);
  return 0;
}

