// module: mt7915.ko
// function: EventThermalProtDutyNotify @ 0x1a7980
// size: 176 bytes
//

void EventThermalProtDutyNotify(undefined4 param_1,int param_2)

{
  if (param_2 == 0) {
    return;
  }
  if ((0 < DebugLevel) && (printk("(Thermal Protect) Duty Notify.\n"), 0 < DebugLevel)) {
    printk("band_idx: %d, level_idx: %d, duty_percent: %d\n",*(undefined1 *)(param_2 + 1),
           *(undefined1 *)(param_2 + 2),*(undefined1 *)(param_2 + 3));
  }
  if (*(int *)(param_2 + 4) == 0) {
    if (*(int *)(param_2 + 8) == 0) {
      return;
    }
  }
  else if (*(int *)(param_2 + 8) == 0) {
    if (DebugLevel < 1) {
      return;
    }
    printk("Trigger Temp = %d\n");
    return;
  }
  if (DebugLevel < 1) {
    return;
  }
  printk("Restore Temp = %d\n");
  return;
}

