// module: mt7915.ko
// function: tmr_raw_dump @ 0x1d7b30
// size: 260 bytes
//

void tmr_raw_dump(undefined4 param_1,int param_2,uint param_3)

{
  uint uVar1;
  int iVar2;
  
  if (DebugLevel < 0) {
    if (param_3 == 0) {
      return;
    }
  }
  else {
    printk("%s: %p, len = %d\n",param_1,param_2,param_3);
    iVar2 = DebugLevel;
    if (param_3 == 0) goto LAB_001d7c00;
  }
  uVar1 = 0;
  iVar2 = DebugLevel;
  do {
    if ((uVar1 & 0xf) == 0) {
      if (-1 < iVar2) {
        printk("TMR 0x%04x : ",uVar1);
        iVar2 = DebugLevel;
        goto LAB_001d7b84;
      }
    }
    else {
LAB_001d7b84:
      if (-1 < iVar2) {
        printk("%02x ",*(undefined1 *)(param_2 + uVar1));
        iVar2 = DebugLevel;
        if (((int)uVar1 % 0x10 == 0xf) && (-1 < DebugLevel)) {
          printk(&_LC3);
          iVar2 = DebugLevel;
        }
      }
    }
    uVar1 = uVar1 + 1;
  } while (uVar1 < param_3);
LAB_001d7c00:
  if (iVar2 < 0) {
    return;
  }
  printk(&_LC3);
  return;
}

