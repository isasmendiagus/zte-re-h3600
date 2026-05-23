// module: mt7915.ko
// function: hex_dump_with_lvl @ 0x243ab8
// size: 240 bytes
//

void hex_dump_with_lvl(undefined4 param_1,int param_2,uint param_3,int param_4)

{
  int iVar1;
  uint uVar2;
  
  if (DebugLevel < param_4) {
    return;
  }
  printk("%s: %p, len = %d\n",param_1,param_2,param_3);
  iVar1 = DebugLevel;
  if (param_3 != 0) {
    uVar2 = 0;
    do {
      if ((uVar2 & 0xf) == 0) {
        if (param_4 <= iVar1) {
          printk("0x%04x : ",uVar2);
          iVar1 = DebugLevel;
          goto LAB_00243b3c;
        }
      }
      else {
LAB_00243b3c:
        if (((param_4 <= iVar1) &&
            (printk("%02x ",*(undefined1 *)(param_2 + uVar2)), iVar1 = DebugLevel,
            (int)uVar2 % 0x10 == 0xf)) && (param_4 <= DebugLevel)) {
          printk(&_LC13);
          iVar1 = DebugLevel;
        }
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 != param_3);
  }
  if (param_4 <= iVar1) {
    printk(&_LC13);
    return;
  }
  return;
}

