// module: mt7915.ko
// function: APStartRekeyTimer @ 0x18990
// size: 44 bytes
//

void APStartRekeyTimer(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 extraout_r2;
  
  iVar1 = HcIsRadioAcq(param_2);
  if (iVar1 == 0) {
    return;
  }
  WPAGroupRekeyByWdev(param_1,param_2,extraout_r2,param_4);
  return;
}

