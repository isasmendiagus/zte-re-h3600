// module: mt7915.ko
// function: EventThermalProtDutyInfo @ 0x1a7bec
// size: 140 bytes
//

void EventThermalProtDutyInfo(undefined4 param_1,int param_2)

{
  if ((((0 < DebugLevel) && (printk(&_LC95,"EventThermalProtDutyInfo"), param_2 != 0)) &&
      (0 < DebugLevel)) && (printk("band_idx: %d\n",*(undefined1 *)(param_2 + 1)), 0 < DebugLevel))
  {
    printk("duty0: %d, duty1: %d, duty2: %d, duty3: %d\n",*(undefined1 *)(param_2 + 2),
           *(undefined1 *)(param_2 + 3),*(undefined1 *)(param_2 + 4),*(undefined1 *)(param_2 + 5));
  }
  return;
}

