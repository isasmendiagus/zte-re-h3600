// module: mt7915.ko
// function: get_dev_eeprom_size @ 0x14ef08
// size: 32 bytes
//

undefined4 get_dev_eeprom_size(int param_1)

{
  char *pcVar1;
  undefined4 uVar2;
  
  uVar2 = DAT_0033aa1c;
  pcVar1 = "Get_System_CapNode_Info" + param_1 + 4;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  return uVar2;
}

