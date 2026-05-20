// module: mt7915.ko
// function: EventThermalSensorShowInfo @ 0x1a7ed8
// size: 276 bytes
//

void EventThermalSensorShowInfo(undefined4 param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  if (0 < DebugLevel) {
    printk("Thermal Task Num: %d\n\n",*(undefined1 *)(param_2 + 1));
    if (0 < DebugLevel) {
      printk("SensorTh: %d (Low), %d (High)\n\n",*(undefined1 *)(param_2 + 2),
             *(undefined1 *)(param_2 + 3));
      if (0 < DebugLevel) {
        printk(
              "==============================================================================================\n"
              );
        if (0 < DebugLevel) {
          printk(
                "  Item    Property    fgTrig    Threshold    FuncHandle    Data                            \n"
                );
          if (0 < DebugLevel) {
            printk(
                  "==============================================================================================\n"
                  );
          }
        }
      }
    }
  }
  uVar1 = (uint)*(byte *)(param_2 + 1);
  if (uVar1 != 0) {
    uVar3 = 0;
    do {
      if (0 < DebugLevel) {
        iVar2 = param_2 + uVar3 * 0x14;
        printk("  %d         %d         %d         %3d         #%x         #%x\n",uVar3,
               *(undefined4 *)(iVar2 + 4),*(undefined1 *)(iVar2 + 8),*(undefined1 *)(iVar2 + 9),
               *(undefined4 *)(iVar2 + 0xc),*(undefined4 *)(iVar2 + 0x14));
        uVar1 = (uint)*(byte *)(param_2 + 1);
      }
      uVar3 = uVar3 + 1 & 0xff;
    } while (uVar3 < uVar1);
  }
  return;
}

