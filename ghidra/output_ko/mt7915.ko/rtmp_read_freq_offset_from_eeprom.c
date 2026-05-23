// module: mt7915.ko
// function: rtmp_read_freq_offset_from_eeprom @ 0x12695c
// size: 116 bytes
//

undefined4 rtmp_read_freq_offset_from_eeprom(int param_1)

{
  ushort local_a;
  
  chip_eeprom_read16(param_1,0x3a,&local_a);
  if ((local_a & 0xff) == 0xff) {
    "rtmp_read_dot11v_mbssid_cfg_from_file"[param_1 + 0x1f] = '\0';
  }
  else {
    "rtmp_read_dot11v_mbssid_cfg_from_file"[param_1 + 0x1f] = (char)local_a;
  }
  if (2 < DebugLevel) {
    printk("E2PROM: RF FreqOffset=0x%x\n","rtmp_read_dot11v_mbssid_cfg_from_file"[param_1 + 0x1f]);
  }
  return 1;
}

