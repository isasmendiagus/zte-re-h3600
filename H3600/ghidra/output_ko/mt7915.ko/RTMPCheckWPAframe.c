// module: mt7915.ko
// function: RTMPCheckWPAframe @ 0x119aac
// size: 548 bytes
//

undefined1
RTMPCheckWPAframe(undefined4 param_1,int param_2,void *param_3,uint param_4,byte param_5,
                 char param_6)

{
  undefined1 uVar1;
  int iVar2;
  undefined1 uStack_11;
  
  if (0x68 < param_5) {
    printk(&_LC35,0x5a5);
    dump_stack();
    return 0;
  }
  if (param_5 == 0x68) {
    return 0;
  }
  if (param_6 == '\0') {
    if (param_4 < 0xc) {
      return 0;
    }
  }
  else {
    if (param_4 < 0x12) {
      return 0;
    }
    if (param_6 == '\x01') {
      param_3 = (void *)((int)param_3 + 0xe);
      goto LAB_00119b0c;
    }
  }
  iVar2 = memcmp(&SNAP_802_1H,param_3,6);
  if ((iVar2 == 0) || (iVar2 = memcmp(&SNAP_BRIDGE_TUNNEL,param_3,6), iVar2 == 0)) {
    param_3 = (void *)((int)param_3 + 6);
  }
LAB_00119b0c:
  iVar2 = memcmp(&EAPOL,param_3,2);
  if (iVar2 == 0) {
    uVar1 = *(undefined1 *)((int)param_3 + 3);
    switch(uVar1) {
    case 0:
      if (DebugLevel < 3) {
        return 1;
      }
      printk("Receive EAP-Packet frame, TYPE = 0, Length = %ld\n",
             CONCAT11(*(undefined1 *)((int)param_3 + 4),*(undefined1 *)((int)param_3 + 5)));
      return 1;
    case 1:
      if (DebugLevel < 3) {
        if (*(char *)(param_2 + 0x17b) == '\0') {
          return 1;
        }
      }
      else {
        printk("Receive EAPOL-Start frame, TYPE = 1\n");
        if (*(char *)(param_2 + 0x17b) == '\0') {
          return 1;
        }
        if (2 < DebugLevel) {
          printk("Cancel the EnqueueEapolStartTimerRunning\n");
        }
      }
      RTMPCancelTimer(param_2 + 0x404,&uStack_11);
      *(undefined1 *)(param_2 + 0x17b) = 0;
      return uVar1;
    case 2:
      if (DebugLevel < 3) {
        return 1;
      }
      printk("Receive EAPOLLogoff frame, TYPE = 2\n");
      return 1;
    case 3:
      if (DebugLevel < 3) {
        return 1;
      }
      printk("Receive EAPOL-Key frame, TYPE = 3, Length = %ld\n",
             CONCAT11(*(undefined1 *)((int)param_3 + 4),*(undefined1 *)((int)param_3 + 5)));
      return 1;
    case 4:
      if (DebugLevel < 3) {
        return 1;
      }
      printk("Receive EAPOLASFAlert frame, TYPE = 4\n");
      return 1;
    }
  }
  return 0;
}

