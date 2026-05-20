// module: mt7915.ko
// function: SetPowerDropCtrl @ 0xbf468
// size: 496 bytes
//

undefined4 SetPowerDropCtrl(int *param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  char cVar3;
  uint uVar4;
  uint uVar5;
  
  if (*(char *)((int)param_1 + 0x286285) == '\x01') {
    if ((uint)*(byte *)((int)param_1 + 0x2b7242) <= (uint)*(byte *)(*param_1 + 0x3c)) {
      return 0;
    }
    uVar4 = HcGetBandByWdev(param_1 + (uint)*(byte *)(*param_1 + 0x3c) * 0x160d + 0xadc92);
    if (*(char *)((int)param_1 + 0x286285) == '\0') goto LAB_000bf5bc;
  }
  else {
    if (*(char *)((int)param_1 + 0x286285) != '\0') {
      uVar4 = 0;
      goto LAB_000bf494;
    }
LAB_000bf5bc:
    uVar4 = HcGetBandByWdev(param_1 + 0xdb6d6);
  }
  if (1 < uVar4) {
    return 0;
  }
LAB_000bf494:
  if (param_2 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: No parameters!!\n","SetPowerDropCtrl");
    }
    return 0;
  }
  iVar1 = rstrtok(param_2,&_LC156);
  if (iVar1 == 0) {
    uVar5 = 0;
  }
  else {
    uVar5 = 0;
    cVar3 = '\0';
    do {
      if (cVar3 == '\0') {
        uVar5 = simple_strtol(iVar1,0,10);
        uVar5 = uVar5 & 0xff;
        iVar1 = rstrtok(0,&_LC156);
        cVar3 = '\x01';
        if (iVar1 == 0) break;
      }
      if (-1 < DebugLevel) {
        printk("%s: set wrong parameters\n","SetPowerDropCtrl");
      }
      cVar3 = cVar3 + '\x01';
      iVar1 = rstrtok(0,&_LC156);
    } while (iVar1 != 0);
  }
  if (0 < DebugLevel) {
    printk("%s: ucPowerDrop = %d\n","SetPowerDropCtrl",uVar5);
  }
  *(char *)((int)param_1 + uVar4 + 0x794cd8) = (char)uVar5;
  if (uVar4 == 0) {
    param_1[0x28eea4] = uVar5;
  }
  else {
    param_1[0x28eaee] = uVar5;
  }
  uVar2 = TxPowerDropCtrl(param_1,uVar5,uVar4);
  return uVar2;
}

