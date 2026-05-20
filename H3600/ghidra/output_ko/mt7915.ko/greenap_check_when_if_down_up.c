// module: mt7915.ko
// function: greenap_check_when_if_down_up @ 0x846d8
// size: 328 bytes
//

undefined4 greenap_check_when_if_down_up(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  char cVar4;
  uint uVar5;
  uint uVar6;
  
  if (2 < DebugLevel) {
    if (param_1 == -0x36da94) {
      cVar4 = '\0';
    }
    else {
      cVar4 = (&DAT_0036da94)[param_1];
    }
    printk("%s, greenap_cap=%d\n","greenap_check_when_if_down_up",cVar4 != '\0');
  }
  uVar1 = HcGetAmountOfBand();
  if (param_1 == -0x36da94) {
    return 0;
  }
  if ((&DAT_0036da94)[param_1] != '\0') {
    OS_SPIN_LOCK(&DAT_0036da9c + param_1);
    if (*(int *)(&DAT_0036da98 + param_1) == 0) {
      if (2 < DebugLevel) {
        printk(&_LC6,"greenap_check_for_all_bands");
      }
      if (uVar1 != 0) {
        uVar6 = 0;
        uVar5 = uVar6;
        do {
          uVar2 = IsHcGreenAPActiveByBand(param_1,uVar5);
          uVar6 = uVar6 + 1;
          uVar3 = FUN_00083b10(param_1);
          FUN_00083c8c(param_1,uVar5,uVar2,uVar3);
          uVar5 = uVar6 & 0xff;
        } while ((uVar6 & 0xff) < uVar1);
      }
    }
    OS_SPIN_UNLOCK(&DAT_0036da9c + param_1);
    return 1;
  }
  return 1;
}

