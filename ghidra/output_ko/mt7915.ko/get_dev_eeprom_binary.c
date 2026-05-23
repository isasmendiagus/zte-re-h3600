// module: mt7915.ko
// function: get_dev_eeprom_binary @ 0x14eecc
// size: 24 bytes
//

undefined * get_dev_eeprom_binary(int param_1)

{
  char *pcVar1;
  
  pcVar1 = "Get_System_CapNode_Info" + param_1 + 4;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  return &DAT_0033aa20;
}

