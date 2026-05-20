// module: mt7915.ko
// function: EventThermalProtectInfo @ 0x1a7cfc
// size: 264 bytes
//

void EventThermalProtectInfo(undefined4 param_1,int param_2)

{
  int iVar1;
  ushort *puVar2;
  undefined4 local_1c [2];
  
  local_1c[0] = 0x3e80040;
  if ((((0 < DebugLevel) &&
       (printk(
              "\n==================================================================================\n"
              ), 0 < DebugLevel)) &&
      (printk("                 Thermal Protect Information     \n"), 0 < DebugLevel)) &&
     (printk("                 Admit Duty Period = %d (us)     \n",
             (uint)*(ushort *)((int)local_1c + (uint)*(byte *)(param_2 + 2) * 2) *
             (uint)*(byte *)(param_2 + 1)), 0 < DebugLevel)) {
    printk("==================================================================================\n");
  }
  puVar2 = (ushort *)(param_2 + 0xc);
  iVar1 = 0;
  do {
    if (0 < DebugLevel) {
      printk("DutyLevel %3d       THERMAL PROTECT ADMIT TIME = %5d (us)                 \n",iVar1,
             (int)((uint)*(ushort *)((int)local_1c + (uint)*(byte *)(param_2 + 2) * 2) *
                  (uint)*puVar2) / 2);
    }
    iVar1 = iVar1 + 1;
    puVar2 = puVar2 + 1;
  } while (iVar1 != 4);
  return;
}

