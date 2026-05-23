// module: mt7915.ko
// function: EventThermalCompTableShowInfo @ 0x1a85e4
// size: 292 bytes
//

void EventThermalCompTableShowInfo(undefined4 param_1,int param_2)

{
  undefined *puVar1;
  int iVar2;
  undefined1 *puVar3;
  char *pcVar4;
  undefined1 auStack_144 [300];
  undefined1 auStack_18 [4];
  
  memcpy(auStack_144,"-7_Step_Number  ",300);
  if (0 < DebugLevel) {
    printk("=========================================\n");
    if (0 < DebugLevel) {
      printk("       Thermal Compensation Table     \n");
      if (0 < DebugLevel) {
        printk("=========================================\n");
        if (0 < DebugLevel) {
          puVar1 = &_LC127;
          if (*(char *)(param_2 + 1) == '\0') {
            puVar1 = &_LC128;
          }
          printk("  Band Index: %d,  Channel Band: %s\n",*(undefined1 *)(param_2 + 2),puVar1);
          if (0 < DebugLevel) {
            printk("-----------------------------------------\n");
          }
        }
      }
    }
  }
  pcVar4 = (char *)(param_2 + 4);
  puVar3 = auStack_144;
  iVar2 = DebugLevel;
  do {
    if (0 < iVar2) {
      printk("%s    = 0x%x\n",puVar3,(int)*pcVar4);
      iVar2 = DebugLevel;
    }
    puVar3 = puVar3 + 0x14;
    pcVar4 = pcVar4 + 1;
  } while (puVar3 != auStack_18);
  if (0 < iVar2) {
    printk("------------------------------------------\n");
  }
  return;
}

