// module: mt7915.ko
// function: hex_dump_with_cat_and_lvl @ 0x243bb0
// size: 288 bytes
//

void hex_dump_with_cat_and_lvl
               (undefined4 param_1,int param_2,uint param_3,int param_4,uint param_5,int param_6)

{
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  undefined4 extraout_r1_01;
  undefined4 extraout_r1_02;
  uint uVar1;
  int iVar2;
  
  if ((param_5 & *(uint *)(DebugSubCategory + (param_4 + param_6 * 0x20) * 4)) == 0) {
    return;
  }
  if (DebugLevel < param_6) {
    if (param_3 == 0) {
      return;
    }
  }
  else {
    printk("%s: %p, len = %d\n",param_1,param_2,param_3);
    param_1 = extraout_r1_01;
    iVar2 = DebugLevel;
    if (param_3 == 0) goto LAB_00243c9c;
  }
  uVar1 = 0;
  iVar2 = DebugLevel;
  do {
    if ((uVar1 & 0xf) == 0) {
      if (param_6 <= iVar2) {
        printk("0x%04x : ",uVar1);
        param_1 = extraout_r1_02;
        iVar2 = DebugLevel;
        goto LAB_00243c28;
      }
    }
    else {
LAB_00243c28:
      if (param_6 <= iVar2) {
        printk("%02x ",*(undefined1 *)(param_2 + uVar1));
        param_1 = extraout_r1;
        iVar2 = DebugLevel;
        if (((int)uVar1 % 0x10 == 0xf) && (param_6 <= DebugLevel)) {
          printk(&_LC13);
          param_1 = extraout_r1_00;
          iVar2 = DebugLevel;
        }
      }
    }
    uVar1 = uVar1 + 1;
  } while (uVar1 < param_3);
LAB_00243c9c:
  if (iVar2 < param_6) {
    return;
  }
  printk(&_LC13,param_1);
  return;
}

