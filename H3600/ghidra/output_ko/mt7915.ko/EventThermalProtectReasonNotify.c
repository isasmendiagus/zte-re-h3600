// module: mt7915.ko
// function: EventThermalProtectReasonNotify @ 0x1a7c7c
// size: 124 bytes
//

void EventThermalProtectReasonNotify(undefined4 param_1,int param_2)

{
  char cVar1;
  
  cVar1 = *(char *)(param_2 + 3);
  if (0 < DebugLevel) {
    printk("%s: HLType: %d, CurrentTemp: %d, Reason: %d\n","EventThermalProtectReasonNotify",
           *(undefined1 *)(param_2 + 1),(int)*(char *)(param_2 + 2),cVar1);
  }
  if (cVar1 == '\x02') {
    RTMP_SET_THERMAL_RADIO_OFF(param_1);
    if (0 < DebugLevel) {
      printk("Radio Off due to too high temperature.\n");
      return;
    }
  }
  return;
}

