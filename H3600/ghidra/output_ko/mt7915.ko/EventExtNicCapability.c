// module: mt7915.ko
// function: EventExtNicCapability @ 0x1c1d68
// size: 180 bytes
//

void EventExtNicCapability
               (undefined4 param_1,undefined1 *param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 extraout_r2;
  undefined4 extraout_r2_00;
  int iVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  
  if (0 < DebugLevel) {
    printk("The data code of firmware:");
    param_3 = extraout_r2_00;
  }
  puVar2 = param_2 + 0x10;
  iVar1 = DebugLevel;
  puVar3 = param_2;
  do {
    if (0 < iVar1) {
      printk(&_LC1,*puVar3,param_3,iVar1,param_4);
      iVar1 = DebugLevel;
      param_3 = extraout_r2;
    }
    puVar3 = puVar3 + 1;
  } while (puVar3 != puVar2);
  if (0 < iVar1) {
    printk("\nThe version code of firmware:");
    iVar1 = DebugLevel;
  }
  do {
    if (0 < iVar1) {
      printk(&_LC1,*puVar2);
    }
    puVar2 = puVar2 + 1;
    iVar1 = DebugLevel;
  } while (puVar2 != param_2 + 0x1c);
  return;
}

