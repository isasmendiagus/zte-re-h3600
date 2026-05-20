// module: mt7915.ko
// function: WscSendEapolStart @ 0x1e1bbc
// size: 484 bytes
//

void WscSendEapolStart(undefined4 param_1,undefined4 *param_2,undefined4 param_3,int param_4)

{
  int local_38;
  undefined1 local_32;
  undefined1 local_31;
  undefined2 local_30;
  undefined4 local_2e;
  undefined2 local_2a;
  undefined4 local_28;
  undefined2 local_24;
  undefined2 local_22;
  
  if (param_4 == 0) {
    printk(&_LC36,0x1544);
    dump_stack();
    if (-1 < DebugLevel) {
      printk("%s: wdev_obj is null.\n","WscSendEapolStart");
    }
  }
  else {
    (**(code **)(*(int *)(param_4 + 0x904) + 0xb8))(param_1,param_2,param_4,&local_38);
    if (local_38 == 0) {
      if (2 < DebugLevel) {
        printk("%s: cannot find this entry(%02x:%02x:%02x:%02x:%02x:%02x)\n","WscSendEapolStart",
               *(undefined1 *)param_2,*(undefined1 *)((int)param_2 + 1),
               *(undefined1 *)((int)param_2 + 2),*(undefined1 *)((int)param_2 + 3),
               *(undefined1 *)(param_2 + 1),*(undefined1 *)((int)param_2 + 5));
      }
    }
    else if (*(int *)(param_4 + 0x12f4) < 0x11) {
      if (2 < DebugLevel) {
        printk("-----> WscSendEapolStart\n");
      }
      __memzero(&local_2e,0xe);
      local_28 = *(undefined4 *)(param_4 + 0x1b);
      local_2a = *(undefined2 *)(param_2 + 1);
      local_24 = *(undefined2 *)(param_4 + 0x1f);
      local_2e = *param_2;
      local_22 = EAPOL;
      __memzero(&local_32,4);
      local_32 = 1;
      local_31 = 1;
      local_30 = 0;
      if (local_38 != 0) {
        RTMPToWirelessSta(param_1,local_38,&local_2e,0xe,&local_32,4,1);
      }
      *(undefined4 *)(param_4 + 0x12f4) = 9;
      *(undefined4 *)(param_4 + 0x12f0) = 0x24;
      if (*(char *)(param_4 + 0x3aac) == '\0') {
        *(undefined1 *)(param_4 + 0x3aac) = 1;
        RTMPSetTimer(param_4 + 0x3ab0,2000);
      }
      if (2 < DebugLevel) {
        printk("<----- WscSendEapolStart\n");
      }
    }
  }
  return;
}

