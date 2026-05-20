// module: mt7915.ko
// function: mt7915_rxv_raw_data_show @ 0x173d68
// size: 312 bytes
//

undefined4
mt7915_rxv_raw_data_show(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  
  puVar5 = *(uint **)(param_1 + 0xa7c214);
  if (puVar5 == (uint *)0x0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s(): null pointer for rxv raw dara.\n","mt7915_rxv_raw_data_show",param_3,DebugLevel,
           param_4);
    return 0;
  }
  uVar2 = *puVar5;
  if (0 < DebugLevel) {
    printk("%s: rxv_cnt: %d, rxv_byte_cnt: %d\n","mt7915_rxv_raw_data_show",(uVar2 << 0xb) >> 0x1b,
           uVar2 & 0xffff,param_4);
  }
  uVar4 = (uVar2 & 0xffff) >> 2;
  iVar1 = DebugLevel;
  if ((uVar2 & 3) == 0) {
    if (uVar4 == 0) goto LAB_00173dd4;
  }
  else {
    uVar4 = uVar4 + 1;
  }
  uVar2 = 0;
  uVar3 = 0;
  do {
    if (((0 < iVar1) &&
        (printk("[0x%04X]:%08X  ",uVar2,puVar5[uVar2]), iVar1 = DebugLevel, (uVar3 & 3) == 3)) &&
       (0 < DebugLevel)) {
      printk(&_LC43);
      iVar1 = DebugLevel;
    }
    uVar2 = uVar2 + 1;
    uVar3 = uVar2 & 0xffff;
  } while (uVar3 < uVar4);
LAB_00173dd4:
  if (iVar1 < 1) {
    return 1;
  }
  printk(&_LC43);
  return 1;
}

