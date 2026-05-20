// module: mt7915.ko
// function: chip_show_pwr_info @ 0x136d8c
// size: 52 bytes
//

undefined4 chip_show_pwr_info(int param_1)

{
  int iVar1;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0xcc) != (code *)0x0) {
    (**(code **)(iVar1 + 0xcc))(param_1);
  }
  return 0;
}

