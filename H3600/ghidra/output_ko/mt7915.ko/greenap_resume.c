// module: mt7915.ko
// function: greenap_resume @ 0x845bc
// size: 280 bytes
//

void greenap_resume(int param_1,uint param_2)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  uint uVar6;
  uint uVar7;
  
  uVar3 = HcGetAmountOfBand();
  if (param_1 != -0x36da94) {
    cVar1 = (&DAT_0036da94)[param_1];
    if (2 < DebugLevel) {
      uVar6 = param_2;
      if (cVar1 == '\0') {
        uVar6 = 0;
      }
      printk("%s, reason(0x%x)\n","greenap_resume",uVar6);
    }
    if (cVar1 != '\0') {
      OS_SPIN_LOCK(&DAT_0036da9c + param_1);
      if (uVar3 != 0) {
        uVar7 = 0;
        uVar6 = uVar7;
        do {
          uVar4 = IsHcGreenAPActiveByBand(param_1,uVar6);
          uVar7 = uVar7 + 1;
          uVar5 = FUN_00083b10(param_1);
          FUN_00083c8c(param_1,uVar6,uVar4,uVar5);
          uVar6 = uVar7 & 0xff;
        } while ((uVar7 & 0xff) < uVar3);
      }
      iVar2 = DebugLevel;
      *(uint *)(&DAT_0036da98 + param_1) = *(uint *)(&DAT_0036da98 + param_1) & ~param_2;
      if (2 < iVar2) {
        printk("%s, greenap->suspend(0x%x)\n","greenap_resume");
      }
      OS_SPIN_UNLOCK(&DAT_0036da9c + param_1);
      return;
    }
  }
  return;
}

