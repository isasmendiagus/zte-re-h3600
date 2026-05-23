// module: mt7915.ko
// function: rtmp_hexdump @ 0x37808
// size: 156 bytes
//

void rtmp_hexdump(int param_1,undefined4 param_2,int param_3,uint param_4)

{
  uint uVar1;
  int iVar2;
  
  if (param_1 < DebugLevel) {
    return;
  }
  if (DebugLevel < 3) {
    if (param_4 == 0) {
      return;
    }
  }
  else {
    printk("%s - hexdump(len=%lu):",param_2,param_4);
    iVar2 = DebugLevel;
    if (param_4 == 0) goto LAB_00037850;
  }
  uVar1 = 0;
  iVar2 = DebugLevel;
  do {
    if (2 < iVar2) {
      printk(" %02x",*(undefined1 *)(param_3 + uVar1));
      iVar2 = DebugLevel;
    }
    uVar1 = uVar1 + 1;
  } while (uVar1 < param_4);
LAB_00037850:
  if (2 < iVar2) {
    printk(&_LC220);
    return;
  }
  return;
}

