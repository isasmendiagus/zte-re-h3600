// module: mt7915.ko
// function: greenap_suspend @ 0x844c4
// size: 244 bytes
//

void greenap_suspend(int param_1,uint param_2)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  
  uVar3 = HcGetAmountOfBand();
  if (param_1 == -0x36da94) {
    return;
  }
  cVar1 = (&DAT_0036da94)[param_1];
  if (2 < DebugLevel) {
    uVar5 = param_2;
    if (cVar1 == '\0') {
      uVar5 = 0;
    }
    printk("%s, reason(0x%x)\n","greenap_suspend",uVar5);
  }
  if (cVar1 == '\0') {
    return;
  }
  OS_SPIN_LOCK(&DAT_0036da9c + param_1);
  iVar2 = DebugLevel;
  *(uint *)(&DAT_0036da98 + param_1) = param_2 | *(uint *)(&DAT_0036da98 + param_1);
  if (2 < iVar2) {
    printk("%s, greenap->suspend(0x%x)\n","greenap_suspend");
  }
  if (uVar3 != 0) {
    uVar6 = 0;
    uVar5 = uVar6;
    do {
      uVar4 = IsHcGreenAPActiveByBand(param_1,uVar5);
      uVar6 = uVar6 + 1;
      FUN_00083c04(param_1,uVar4,0,uVar5);
      uVar5 = uVar6 & 0xff;
    } while ((uVar6 & 0xff) < uVar3);
  }
  OS_SPIN_UNLOCK(&DAT_0036da9c + param_1);
  return;
}

