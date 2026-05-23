// module: mt7915.ko
// function: D_ShowTableInfo @ 0x9b57c
// size: 240 bytes
//

void D_ShowTableInfo(undefined4 *param_1)

{
  undefined1 local_50 [64];
  
  if (DebugLevel < 1) goto LAB_0009b59c;
  printk("Drv bnstrg info\n");
  if (0 < DebugLevel) {
    printk("bEnabled=%d\n",*(undefined1 *)((int)param_1 + 5));
    if (DebugLevel < 1) goto LAB_0009b59c;
    printk("bInitialized=%d\n",*(undefined1 *)(param_1 + 1));
    if (DebugLevel < 1) goto LAB_0009b59c;
    printk("b2GInfReady=%d\n",*(undefined1 *)(param_1 + 0x408));
    if (DebugLevel < 1) goto LAB_0009b59c;
    printk("b5GInfReady=%d\n",*(undefined1 *)((int)param_1 + 0x1021));
  }
  if (0 < DebugLevel) {
    printk("=======================");
  }
LAB_0009b59c:
  local_50[0] = 9;
  RtmpOSWrielessEventSend(*param_1,1,0x950,0,local_50,0x40);
  return;
}

