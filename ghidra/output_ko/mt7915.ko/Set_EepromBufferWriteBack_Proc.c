// module: mt7915.ko
// function: Set_EepromBufferWriteBack_Proc @ 0x1283bc
// size: 308 bytes
//

undefined4 Set_EepromBufferWriteBack_Proc(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  
  uVar1 = os_str_tol(param_2,0,10);
  if (uVar1 < 5) {
    switch(uVar1) {
    case 1:
      if (0 < DebugLevel) {
        printk("Write EEPROM buffer back to eFuse\n");
      }
      rtmp_ee_write_to_efuse(param_1);
      return 1;
    case 2:
      if (0 < DebugLevel) {
        printk("Write EEPROM buffer back to Flash\n");
      }
      rtmp_ee_flash_write_all(param_1);
      return 1;
    case 3:
      if (0 < DebugLevel) {
        printk("Write EEPROM buffer back to EEPROM\n");
      }
      rtmp_ee_write_to_prom(param_1);
      return 1;
    case 4:
      if (0 < DebugLevel) {
        printk("Write EEPROM buffer back to BIN\n");
      }
      rtmp_ee_write_to_bin(param_1);
      return 1;
    }
    if (-1 < DebugLevel) {
      printk("%s::do not support this EEPROM access mode\n","Set_EepromBufferWriteBack_Proc");
      return 0;
    }
  }
  return 0;
}

