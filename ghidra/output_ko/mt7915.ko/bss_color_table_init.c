// module: mt7915.ko
// function: bss_color_table_init @ 0x16af80
// size: 44 bytes
//

void bss_color_table_init(int param_1)

{
  os_zero_mem(param_1 + 0x30d8,0x200);
  *(undefined4 *)(param_1 + 0x31d4) = 0;
  *(undefined4 *)(param_1 + 0x32d4) = 0;
  return;
}

