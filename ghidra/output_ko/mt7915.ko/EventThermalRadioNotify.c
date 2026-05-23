// module: mt7915.ko
// function: EventThermalRadioNotify @ 0x1a7a30
// size: 172 bytes
//

void EventThermalRadioNotify(undefined4 param_1,int param_2)

{
  if (param_2 == 0) {
    return;
  }
  if (0 < DebugLevel) {
    printk("(Thermal Protect) Radio Notify.\n");
    if (0 < DebugLevel) {
      printk("band_idx: %d, level_idx: %d\n",*(undefined1 *)(param_2 + 1),
             *(undefined1 *)(param_2 + 2));
    }
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

