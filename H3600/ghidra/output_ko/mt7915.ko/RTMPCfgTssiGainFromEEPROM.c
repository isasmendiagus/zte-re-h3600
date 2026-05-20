// module: mt7915.ko
// function: RTMPCfgTssiGainFromEEPROM @ 0x26c70c
// size: 124 bytes
//

void RTMPCfgTssiGainFromEEPROM(int param_1)

{
  byte bVar1;
  ushort local_a;
  
  chip_eeprom_read16(param_1,0x76,&local_a);
  bVar1 = (byte)local_a;
  if ((byte)local_a == 0xff || (byte)local_a == 0) {
    *(undefined1 *)(param_1 + 0xa39fce) = 3;
  }
  else {
    *(byte *)(param_1 + 0xa39fce) = (byte)local_a & 0xf;
  }
  local_a = (ushort)(byte)local_a;
  if (2 < DebugLevel) {
    printk("%s: EEPROM_TSSI_GAIN_AND_ATTENUATION = 0x%X, pAd->TssiGain=0x%x\n",
           "RTMPCfgTssiGainFromEEPROM",bVar1,*(undefined1 *)(param_1 + 0xa39fce));
  }
  return;
}

