// module: mt7915.ko
// function: Set_AP_ASSOC_REQ_RSSI_THRESHOLD @ 0x29ac8
// size: 336 bytes
//

undefined4 Set_AP_ASSOC_REQ_RSSI_THRESHOLD(int *param_1,undefined4 param_2)

{
  int iVar1;
  char cVar2;
  uint uVar3;
  int *piVar4;
  
  uVar3 = *(uint *)(*param_1 + 0x3c);
  cVar2 = os_str_tol(param_2,0,10);
  if (cVar2 == '\0') {
    if (DebugLevel < 3) {
      *(undefined1 *)(param_1 + (uVar3 & 0xff) * 0x160d + 0xaefa1) = 0;
      goto LAB_00029b1c;
    }
    printk("Disable AP_ASSOC_REQ_RSSI_THRESHOLD\n");
  }
  else if (100 < (byte)(cVar2 + 100U)) {
    if (DebugLevel < 3) {
      return 0;
    }
    printk("Set_AP_ASSOC_REQ_RSSI_THRESHOLD Value Error.\n");
    return 0;
  }
  iVar1 = DebugLevel;
  uVar3 = uVar3 & 0xff;
  *(char *)(param_1 + uVar3 * 0x160d + 0xaefa1) = cVar2;
  if (2 < iVar1) {
    printk("I/F(ra%d) Set_AP_ASSOC_REQ_RSSI_THRESHOLD=%d\n",uVar3,(int)cVar2);
  }
LAB_00029b1c:
  if (*(char *)((int)param_1 + 0x2b7242) != '\0') {
    uVar3 = 0;
    piVar4 = param_1 + 0xaefa1;
    do {
      if (2 < DebugLevel) {
        printk("%d. ==> %d\n",uVar3,(int)(char)*piVar4);
      }
      uVar3 = uVar3 + 1;
      piVar4 = piVar4 + 0x160d;
    } while (uVar3 < *(byte *)((int)param_1 + 0x2b7242));
  }
  return 1;
}

