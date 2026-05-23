// module: mt7915.ko
// function: mt7915_iBFPhaseCalE2PInit @ 0x893dc
// size: 116 bytes
//

void mt7915_iBFPhaseCalE2PInit(int param_1)

{
  chip_eeprom_read_with_range
            (param_1,au2MT7915IBfCalEEPROMOffset._0_2_,0x28,*(undefined4 *)(param_1 + 0xa78684));
  chip_eeprom_read_with_range
            (param_1,au2MT7915IBfCalEEPROMOffset._2_2_,0x118,*(undefined4 *)(param_1 + 0xa78688));
  chip_eeprom_read_with_range
            (param_1,au2MT7915IBfCalEEPROMOffset._16_2_,0x28,*(int *)(param_1 + 0xa78688) + 0x118);
  *(undefined1 *)(param_1 + 0xa7868c) = 0;
  __memzero(param_1 + 0xa7868d,9);
  return;
}

