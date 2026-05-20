// module: mt7915.ko
// function: bss_color_table_deinit @ 0x16afac
// size: 48 bytes
//

void bss_color_table_deinit(int param_1)

{
  os_zero_mem(param_1 + 0x30d8,0x100);
  os_zero_mem(param_1 + 0x31d8,0x100);
  return;
}

