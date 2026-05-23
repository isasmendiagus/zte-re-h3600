// module: mt7915.ko
// function: WscPushPBCAction @ 0x1e7128
// size: 352 bytes
//

void WscPushPBCAction(undefined4 param_1,int param_2)

{
  undefined1 uStack_21;
  
  if (2 < DebugLevel) {
    printk("-----> WscPushPBCAction\n");
  }
  if (*(char *)(param_2 + 0x1c5b) != '\0') {
    *(undefined1 *)(param_2 + 0x1c5b) = 0;
    RTMPCancelTimer(param_2 + 0x1c5c,&uStack_21);
  }
  if (*(char *)(param_2 + 0x283c) != '\0') {
    *(undefined1 *)(param_2 + 0x283c) = 0;
    RTMPCancelTimer(param_2 + 0x2840,&uStack_21);
  }
  if (*(char *)(param_2 + 0x2804) != '\0') {
    *(undefined1 *)(param_2 + 0x2804) = 0;
    RTMPCancelTimer(param_2 + 0x2808,&uStack_21);
  }
  *(undefined4 *)(param_2 + 0xc) = 0x23;
  *(undefined4 *)(param_2 + 0x10) = 2;
  WscInitRegistrarPair(param_1,param_2,0);
  WscGetRegDataPIN(param_1,*(undefined4 *)(param_2 + 0x14),param_2);
  RTMPSetTimer(param_2 + 0x1c5c,120000);
  *(undefined1 *)(param_2 + 0x1c5b) = 1;
  *(undefined1 *)(param_2 + 0x29e4) = 1;
  WscScanExec(param_1,param_2);
  if ((*(int *)(param_2 + 0x28e4) == 0) && (*(char *)(param_2 + 0x2c4d) != '\x01')) {
    RTMPSetTimer(param_2 + 0x2808,10000);
    *(undefined1 *)(param_2 + 0x2804) = 1;
  }
  if (2 < DebugLevel) {
    printk("<----- WscPushPBCAction\n");
  }
  return;
}

