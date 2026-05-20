// module: mt7915.ko
// function: dumpEDCAParm @ 0x34d7c
// size: 292 bytes
//

void dumpEDCAParm(int param_1,int param_2,int param_3)

{
  int iVar1;
  
  if (param_2 == 0) {
    if (DebugLevel < param_3) {
      return;
    }
    printk("\nAC_BE:");
  }
  else if (param_2 == 1) {
    if (DebugLevel < param_3) {
      return;
    }
    printk("\nAC_BK:");
  }
  else if (param_2 == 2) {
    if (DebugLevel < param_3) {
      return;
    }
    printk("\nAC_VI:");
  }
  else if (param_2 == 3) {
    if (DebugLevel < param_3) {
      return;
    }
    printk("\nAC_VO:");
  }
  if (param_3 <= DebugLevel) {
    iVar1 = param_1 + param_2;
    printk("Aifsn=%d Cwmin=%d Cwmax=%d Txop=%d\n",*(undefined1 *)(iVar1 + 7),
           *(undefined1 *)(iVar1 + 0xb),*(undefined1 *)(iVar1 + 0xf),
           *(undefined2 *)(param_1 + param_2 * 2 + 0x14));
  }
  return;
}

