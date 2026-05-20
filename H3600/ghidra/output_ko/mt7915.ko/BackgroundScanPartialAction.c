// module: mt7915.ko
// function: BackgroundScanPartialAction @ 0x22e5b8
// size: 288 bytes
//

void BackgroundScanPartialAction(int param_1,int param_2)

{
  undefined1 uVar1;
  char cVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  char *pcVar8;
  
  uVar1 = *(undefined1 *)(param_2 + 0x924);
  if (DebugLevel < 3) {
    if (*(char *)(param_1 + 0xa7905c) != '\0') goto LAB_0022e644;
  }
  else {
    printk("%s =====ScanType=%d===>\n","BackgroundScanPartialAction",uVar1);
    if (*(char *)(param_1 + 0xa7905c) != '\0') goto LAB_0022e644;
    if (2 < DebugLevel) {
      printk("%s First time===========>\n","BackgroundScanPartialAction");
    }
  }
  uVar7 = *(byte *)(param_1 + 0xa78ad1) - 1;
  if (0 < (int)uVar7) {
    if (*(char *)(param_1 + 0xa78ad9) == '\x01') {
      uVar5 = 0;
      pcVar8 = (char *)(param_1 + 0xa78af1);
      do {
        uVar5 = uVar5 + 1;
        if (uVar5 == uVar7) goto LAB_0022e638;
        cVar2 = *pcVar8;
        pcVar8 = pcVar8 + 0x18;
      } while (cVar2 == '\x01');
      uVar7 = uVar5 & 0xff;
    }
    else {
      uVar7 = 0;
      uVar5 = uVar7;
    }
    iVar6 = param_1 + uVar5 * 0x18;
    uVar3 = *(undefined1 *)(iVar6 + 0xa78ad5);
    *(undefined1 *)(param_1 + 0xa7905c) = uVar3;
    uVar4 = *(undefined1 *)(iVar6 + 0xa78ad6);
    *(undefined1 *)(param_1 + 0xa7922e) = uVar3;
    *(char *)(param_1 + 0xa7922f) = (char)uVar7;
    *(undefined1 *)(param_1 + 0xa7905d) = uVar4;
  }
LAB_0022e638:
  greenap_suspend(param_1,1);
LAB_0022e644:
  BackgroundScanNextChannel(param_1,uVar1);
  return;
}

