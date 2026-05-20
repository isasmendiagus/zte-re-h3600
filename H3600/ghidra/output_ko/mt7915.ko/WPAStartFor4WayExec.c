// module: mt7915.ko
// function: WPAStartFor4WayExec @ 0x121bd8
// size: 324 bytes
//

void WPAStartFor4WayExec(undefined4 param_1,int param_2)

{
  int iVar1;
  
  if (param_2 == 0) {
    return;
  }
  iVar1 = *(int *)(param_2 + 0xc);
  if (*(byte *)(param_2 + 0x514) < 8) {
    if (((*(uint *)(param_2 + 0x17c) & 0x2090) == 0) && (*(char *)(param_2 + 0x17b) != '\x01')) {
      if ((*(uint *)(param_2 + 0x17c) & 0x10048) != 0) {
        if (2 < DebugLevel) {
          printk("Enqueue EAPoL-Start-1X for sta(%02x:%02x:%02x:%02x:%02x:%02x)\n",
                 *(undefined1 *)(param_2 + 0xec),*(undefined1 *)(param_2 + 0xed),
                 *(undefined1 *)(param_2 + 0xee),*(undefined1 *)(param_2 + 0xef),
                 *(undefined1 *)(param_2 + 0xf0),*(undefined1 *)(param_2 + 0xf1));
        }
        DOT1X_EapTriggerAction(iVar1,param_2);
      }
    }
    else {
      if (2 < DebugLevel) {
        printk("Enqueue EAPoL-Start-PSK for sta(%02x:%02x:%02x:%02x:%02x:%02x)\n",
               *(undefined1 *)(param_2 + 0xec),*(undefined1 *)(param_2 + 0xed),
               *(undefined1 *)(param_2 + 0xee),*(undefined1 *)(param_2 + 0xef),
               *(undefined1 *)(param_2 + 0xf0),*(undefined1 *)(param_2 + 0xf1));
      }
      MlmeEnqueueWithWdev(iVar1,0x17,1,6,param_2 + 0xec,0,*(undefined4 *)(param_2 + 8));
      RtmpOsMlmeUp(iVar1 + 0x286298);
    }
    *(undefined1 *)(param_2 + 0x17b) = 0;
  }
  return;
}

