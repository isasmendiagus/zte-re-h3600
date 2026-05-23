// module: mt7915.ko
// function: rtmp_read_txpwr_from_eeprom @ 0x1269d0
// size: 68 bytes
//

undefined4 rtmp_read_txpwr_from_eeprom(int param_1)

{
  int iVar1;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x204) != (code *)0x0) {
    (**(code **)(iVar1 + 0x204))(param_1);
  }
  RTMPReadTxPwrPerRate(param_1);
  InitSkuRateDiffTable(param_1);
  return 1;
}

