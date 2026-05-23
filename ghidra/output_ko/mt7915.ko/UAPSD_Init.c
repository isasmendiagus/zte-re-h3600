// module: mt7915.ko
// function: UAPSD_Init @ 0x1ddb08
// size: 76 bytes
//

void UAPSD_Init(int param_1)

{
  char *pcVar1;
  int iVar2;
  
  iVar2 = DebugLevel;
  pcVar1 = "BssTableSortByRssi" + param_1 + 0x10;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  if (2 < iVar2) {
    printk("uapsd> allocate a spinlock!\n");
  }
  gUAPSD_SP_CloseAbnormalNum = 0;
  return;
}

