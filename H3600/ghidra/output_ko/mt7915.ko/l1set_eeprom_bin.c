// module: mt7915.ko
// function: l1set_eeprom_bin @ 0x14edac
// size: 204 bytes
//

undefined4 l1set_eeprom_bin(int param_1,undefined4 param_2,char *param_3)

{
  char *pcVar1;
  size_t sVar2;
  int iVar3;
  
  pcVar1 = "Get_System_CapNode_Info" + param_1 + 4;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  sVar2 = strlen(param_3);
  iVar3 = strcmp(&DAT_0033aa20,param_3);
  if (iVar3 == 0 || 0x1d < (sVar2 & 0xff)) {
    if (2 < DebugLevel) {
      printk("eeprom binary remain %s\n",&DAT_0033aa20);
    }
    return 0;
  }
  if (2 < DebugLevel) {
    printk("eeprom binary update from %s to %s\n",&DAT_0033aa20,param_3);
  }
  strcpy(&DAT_0033aa20,param_3);
  (&DAT_0033aa20)[sVar2 & 0xff] = 0;
  return 0;
}

