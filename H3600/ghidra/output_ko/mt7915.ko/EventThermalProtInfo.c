// module: mt7915.ko
// function: EventThermalProtInfo @ 0x1a7adc
// size: 272 bytes
//

void EventThermalProtInfo(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined2 *puVar1;
  int iVar2;
  int iVar3;
  
  if (param_2 != 0) {
    if (0 < DebugLevel) {
      printk("band_idx: %d\n",*(undefined1 *)(param_2 + 1),param_3,DebugLevel,param_4);
    }
    puVar1 = (undefined2 *)(param_2 + 0x24);
    iVar2 = 1;
    iVar3 = param_2;
    while( true ) {
      if ((((0 < DebugLevel) &&
           (printk("prot_type: %d, trig_type: %d\n",*(undefined1 *)(param_2 + 4),
                   *(undefined1 *)(param_2 + 8),DebugLevel,param_4), 0 < DebugLevel)) &&
          (printk("state: %d, enable: %d\n",*(undefined1 *)(param_2 + 0x2c),
                  *(undefined1 *)(param_2 + 0x30),DebugLevel,param_4), 0 < DebugLevel)) &&
         ((printk("trigger_temp: %d, restore_temp: %d\n",*(undefined4 *)(iVar3 + 0xc),
                  *(undefined4 *)(iVar3 + 0x18),DebugLevel,param_4), 0 < DebugLevel &&
          (printk("recheck_time: %d\n",*puVar1), 0 < DebugLevel)))) {
        printk("--------------------------\n");
      }
      puVar1 = puVar1 + 1;
      param_2 = param_2 + 1;
      iVar3 = iVar3 + 4;
      if (iVar2 == 3) break;
      iVar2 = iVar2 + 1;
    }
    return;
  }
  return;
}

