// module: mt7915.ko
// function: BackgroundScanStartAction @ 0x22e26c
// size: 252 bytes
//

void BackgroundScanStartAction(int param_1,int param_2)

{
  byte bVar1;
  char cVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  char *pcVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  
  bVar1 = *(byte *)(param_2 + 0x924);
  if (2 < DebugLevel) {
    printk("%s ===> ScanType=%d\n","BackgroundScanStartAction",bVar1 & 0xf);
  }
  uVar8 = *(byte *)(param_1 + 0xa78ad1) - 1;
  if (0 < (int)uVar8) {
    if (*(char *)(param_1 + 0xa78ad9) == '\x01') {
      uVar6 = 0;
      pcVar5 = (char *)(param_1 + 0xa78af1);
      do {
        uVar6 = uVar6 + 1;
        if (uVar6 == uVar8) goto LAB_0022e2ec;
        cVar2 = *pcVar5;
        pcVar5 = pcVar5 + 0x18;
      } while (cVar2 == '\x01');
      uVar8 = uVar6 & 0xff;
    }
    else {
      uVar6 = 0;
      uVar8 = uVar6;
    }
    iVar7 = param_1 + uVar6 * 0x18;
    uVar3 = *(undefined1 *)(iVar7 + 0xa78ad5);
    *(undefined1 *)(param_1 + 0xa7905c) = uVar3;
    uVar4 = *(undefined1 *)(iVar7 + 0xa78ad6);
    *(undefined1 *)(param_1 + 0xa7922e) = uVar3;
    *(char *)(param_1 + 0xa7922f) = (char)uVar8;
    *(undefined1 *)(param_1 + 0xa7905d) = uVar4;
  }
LAB_0022e2ec:
  *(byte *)(param_1 + 0xa79754) = bVar1;
  greenap_suspend(param_1,1);
  BackgroundScanNextChannel(param_1,bVar1);
  return;
}

