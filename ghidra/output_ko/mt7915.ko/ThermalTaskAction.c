// module: mt7915.ko
// function: ThermalTaskAction @ 0xd7e78
// size: 80 bytes
//

undefined4
ThermalTaskAction(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (DebugLevel < 1) {
    return 1;
  }
  printk("%s(): u4PhyIdx: %d, u4ThermalTaskProp: %d, u1ThermalAdc: %d\n","ThermalTaskAction",param_2
         ,param_3,param_4);
  return 1;
}

