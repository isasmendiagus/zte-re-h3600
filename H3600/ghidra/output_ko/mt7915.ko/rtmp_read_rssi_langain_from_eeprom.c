// module: mt7915.ko
// function: rtmp_read_rssi_langain_from_eeprom @ 0x126788
// size: 380 bytes
//

undefined4 rtmp_read_rssi_langain_from_eeprom(int param_1)

{
  char *pcVar1;
  char *pcVar2;
  ushort local_12 [3];
  
  chip_eeprom_read16(param_1,0x46,local_12);
  "auth_fsm_reset"[param_1 + 7] = (char)local_12[0];
  "auth_fsm_reset"[param_1 + 8] = (char)(local_12[0] >> 8);
  chip_eeprom_read16(param_1,0x48,local_12);
  "auth_fsm_reset"[param_1 + 9] = (char)local_12[0];
  "BssEntrySet"[param_1 + 1] = (char)(local_12[0] >> 8);
  chip_eeprom_read16(param_1,0x44,local_12);
  "auth_fsm_reset"[param_1 + 0xf] = (char)local_12[0];
  "BssEntrySet"[param_1] = (char)(local_12[0] >> 8);
  chip_eeprom_read16(param_1,0x4a,local_12);
  "auth_fsm_reset"[param_1 + 0xb] = (char)local_12[0];
  "auth_fsm_reset"[param_1 + 0xc] = (char)(local_12[0] >> 8);
  chip_eeprom_read16(param_1,0x4c,local_12);
  if ((byte)("BssEntrySet"[param_1 + 1] + 1U) < 2) {
    "BssEntrySet"[param_1 + 1] = "BssEntrySet"[param_1];
  }
  "auth_fsm_reset"[param_1 + 0xd] = (char)local_12[0];
  "BssEntrySet"[param_1 + 2] = (char)(local_12[0] >> 8);
  if (((local_12[0] >> 8) + 1 & 0xff) < 2) {
    "BssEntrySet"[param_1 + 2] = "BssEntrySet"[param_1];
  }
  if (2 < DebugLevel) {
    printk("ALNAGain0 = %d, ALNAGain1 = %d, ALNAGain2 = %d\n",(int)"BssEntrySet"[param_1],
           (int)"BssEntrySet"[param_1 + 1],(int)"BssEntrySet"[param_1 + 2]);
  }
  pcVar2 = "auth_fsm_reset" + param_1 + 6;
  pcVar1 = "auth_fsm_reset" + param_1 + 10;
  do {
    pcVar2 = pcVar2 + 1;
    if (0x14 < (byte)(*pcVar2 + 10U)) {
      *pcVar2 = '\0';
    }
    pcVar1 = pcVar1 + 1;
    if (0x14 < (byte)(*pcVar1 + 10U)) {
      *pcVar1 = '\0';
    }
  } while (pcVar2 != "auth_fsm_reset" + param_1 + 9);
  return 1;
}

