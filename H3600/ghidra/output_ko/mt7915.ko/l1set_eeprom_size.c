// module: mt7915.ko
// function: l1set_eeprom_size @ 0x14e9b8
// size: 132 bytes
//

undefined4 l1set_eeprom_size(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char *pcVar1;
  int iVar2;
  
  pcVar1 = "Get_System_CapNode_Info" + param_1 + 4;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  iVar2 = os_str_tol(param_3,0,0,&UNK_00296000 + param_1,param_4);
  if (DAT_0033aa1c == iVar2) {
    iVar2 = DAT_0033aa1c;
    if (2 < DebugLevel) {
      printk("eeprom size remain 0x%x\n");
      iVar2 = DAT_0033aa1c;
    }
  }
  else if (2 < DebugLevel) {
    printk("eeprom size update from 0x%x to 0x%x\n",DAT_0033aa1c,iVar2);
  }
  DAT_0033aa1c = iVar2;
  return 0;
}

