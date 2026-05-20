// module: mt7915.ko
// function: EventThermalSensorTaskResp @ 0x1a7e54
// size: 128 bytes
//

void EventThermalSensorTaskResp(undefined4 param_1,int param_2)

{
  if (0 < DebugLevel) {
    printk("%s(): result fp: #%x\n","EventThermalSensorTaskResp",*(undefined4 *)(param_2 + 0xc));
    if (0 < DebugLevel) {
      printk("%s(): origin fp: #%p\n","EventThermalSensorTaskResp",ThermalTaskAction);
    }
  }
  if (*(int *)(param_2 + 0xc) == 0) {
    return;
  }
  ThermalTaskAction(param_1,*(undefined1 *)(param_2 + 4),*(undefined4 *)(param_2 + 8),
                    *(undefined1 *)(param_2 + 1));
  return;
}

