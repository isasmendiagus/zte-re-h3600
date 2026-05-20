// module: mt7915.ko
// function: EventThermalStateShowInfo @ 0x1a83f4
// size: 264 bytes
//

void EventThermalStateShowInfo(undefined4 param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  undefined1 auStack_2fa [738];
  
  memcpy(auStack_2fa,"DPD_CAL          ",0x2e2);
  if (0 < DebugLevel) {
    printk("Total Thermo Item Num: %d\n\n",*(undefined1 *)(param_2 + 1));
    if (0 < DebugLevel) {
      printk("==================================================================================\n")
      ;
      if (0 < DebugLevel) {
        printk(
              "        Item            Type       LowEn       HighEn      LowerBnd       UpperBnd\n"
              );
        if (0 < DebugLevel) {
          printk(
                "==================================================================================\n"
                );
        }
      }
    }
  }
  uVar1 = (uint)*(byte *)(param_2 + 1);
  if (uVar1 != 0) {
    uVar2 = 0;
    do {
      if (0 < DebugLevel) {
        iVar3 = param_2 + uVar2 * 6;
        printk("%s     %3d        %3d         %3d          %3d            %3d\n",
               auStack_2fa + (uint)*(byte *)(iVar3 + 4) * 0x12,*(undefined1 *)(iVar3 + 5),
               *(undefined1 *)(iVar3 + 6),*(undefined1 *)(iVar3 + 7),(int)*(char *)(iVar3 + 8),
               (int)*(char *)(iVar3 + 9));
        uVar1 = (uint)*(byte *)(param_2 + 1);
      }
      uVar2 = uVar2 + 1 & 0xff;
    } while (uVar2 < uVar1);
  }
  return;
}

