// module: mt7915.ko
// function: wifi_sys_dump @ 0x104534
// size: 896 bytes
//

void wifi_sys_dump(int param_1)

{
  int *piVar1;
  int iVar2;
  
  if (((DebugLevel < 1) || (printk("===============================\n"), DebugLevel < 1)) ||
     (printk("Current DevInfo Num: %d\n",*(undefined4 *)(param_1 + 0xa7bed4)), DebugLevel < 1)) {
    piVar1 = *(int **)(param_1 + 0xa7bed8);
    if ((int *)(param_1 + 0xa7bed8) == piVar1) goto LAB_001045a8;
LAB_0010457c:
    iVar2 = DebugLevel;
    do {
      if ((((0 < iVar2) &&
           (printk("#####WdevIdx (%d)#####\n",*(undefined1 *)(piVar1[-1] + 0xc)), iVar2 = DebugLevel
           , 0 < DebugLevel)) &&
          ((printk("Active: %d\n",(char)piVar1[-3]), iVar2 = DebugLevel, 0 < DebugLevel &&
           ((printk("BandIdx: %d\n",*(undefined1 *)((int)piVar1 + -0xd)), iVar2 = DebugLevel,
            0 < DebugLevel &&
            (printk("EnableFeature: %d\n",piVar1[-2]), iVar2 = DebugLevel, 0 < DebugLevel)))))) &&
         (printk("OwnMacIdx: %d\n",(char)piVar1[-5]), iVar2 = DebugLevel, 0 < DebugLevel)) {
        printk("OwnMacAddr: %02x:%02x:%02x:%02x:%02x:%02x\n",*(undefined1 *)((int)piVar1 + -0x13),
               *(undefined1 *)((int)piVar1 + -0x12),*(undefined1 *)((int)piVar1 + -0x11),
               (char)piVar1[-4],*(undefined1 *)((int)piVar1 + -0xf),
               *(undefined1 *)((int)piVar1 + -0xe));
        iVar2 = DebugLevel;
      }
      piVar1 = (int *)*piVar1;
    } while ((int *)(param_1 + 0xa7bed8) != piVar1);
  }
  else {
    printk("===============================\n");
    piVar1 = *(int **)(param_1 + 0xa7bed8);
    iVar2 = DebugLevel;
    if ((int *)(param_1 + 0xa7bed8) != piVar1) goto LAB_0010457c;
  }
  if (((0 < iVar2) && (printk("===============================\n"), 0 < DebugLevel)) &&
     (printk("Current BssInfo Num: %d\n",*(undefined4 *)(param_1 + 0xa7bee0)), 0 < DebugLevel)) {
    printk("===============================\n");
  }
LAB_001045a8:
  FUN_00103e28(param_1 + 0xa7bee0);
  if (((0 < DebugLevel) && (printk("===============================\n"), 0 < DebugLevel)) &&
     (printk("Current StaRec Num: %d\n",*(undefined4 *)(param_1 + 0xa7beec)), 0 < DebugLevel)) {
    printk("===============================\n");
  }
  for (piVar1 = *(int **)(param_1 + 0xa7bef0); (int *)(param_1 + 0xa7bef0) != piVar1;
      piVar1 = (int *)*piVar1) {
    iVar2 = piVar1[-1];
    if (((0 < DebugLevel) &&
        (printk("#####MacEntry (%d)#####\n",*(undefined2 *)(iVar2 + 8)), 0 < DebugLevel)) &&
       ((printk("PeerAddr: %02x:%02x:%02x:%02x:%02x:%02x\n",*(undefined1 *)(iVar2 + 0xb),
                *(undefined1 *)(iVar2 + 0xc),*(undefined1 *)(iVar2 + 0xd),
                *(undefined1 *)(iVar2 + 0xe),*(undefined1 *)(iVar2 + 0xf),
                *(undefined1 *)(iVar2 + 0x10)), 0 < DebugLevel &&
        ((((printk("WlanIdx: %d\n",*(undefined2 *)((int)piVar1 + -0xce)), 0 < DebugLevel &&
           (printk("BssIndex: %d\n",*(undefined1 *)(piVar1 + -0x34)), 0 < DebugLevel)) &&
          (printk("ConnectionState: %d\n",*(undefined1 *)(piVar1 + -0x32)), 0 < DebugLevel)) &&
         (printk("ConnectionType: %d\n",piVar1[-0x33]), 0 < DebugLevel)))))) {
      printk("EnableFeature: %x\n",piVar1[-0x31]);
    }
  }
  return;
}

