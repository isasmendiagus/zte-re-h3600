// module: mt7915.ko
// function: greenap_proc @ 0x84868
// size: 248 bytes
//

void greenap_proc(int param_1,int param_2)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  undefined *puVar6;
  
  uVar1 = HcGetAmountOfBand();
  if (param_1 == -0x36da94) {
    return;
  }
  puVar6 = &DAT_0036da9c + param_1;
  OS_SPIN_LOCK(puVar6);
  if (*(int *)(&DAT_0036da98 + param_1) == 0) {
    if (param_2 == 0) {
      (&DAT_0036da94)[param_1] = 0;
      if (uVar1 != 0) {
        uVar4 = 0;
        uVar5 = 0;
        do {
          uVar2 = IsHcGreenAPActiveByBand(param_1,uVar5);
          uVar4 = uVar4 + 1;
          FUN_00083c04(param_1,uVar2,0,uVar5);
          uVar5 = uVar4 & 0xff;
        } while ((uVar4 & 0xff) < uVar1);
        OS_SPIN_UNLOCK(puVar6);
        return;
      }
    }
    else {
      (&DAT_0036da94)[param_1] = 1;
      if (uVar1 != 0) {
        uVar4 = 0;
        uVar5 = 0;
        do {
          uVar2 = IsHcGreenAPActiveByBand(param_1,uVar5);
          uVar4 = uVar4 + 1;
          uVar3 = FUN_00083b10(param_1);
          FUN_00083c8c(param_1,uVar5,uVar2,uVar3);
          uVar5 = uVar4 & 0xff;
        } while ((uVar4 & 0xff) < uVar1);
      }
    }
  }
  OS_SPIN_UNLOCK(puVar6);
  return;
}

