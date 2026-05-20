// module: mt7915.ko
// function: rtmp_eeprom_info_extract @ 0x126a14
// size: 60 bytes
//

void rtmp_eeprom_info_extract(int param_1)

{
  int iVar1;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x27c) == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00126a4c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x27c))(param_1,*(undefined4 *)("Set_IRR_TTGOnOff" + param_1 + 4));
  return;
}

