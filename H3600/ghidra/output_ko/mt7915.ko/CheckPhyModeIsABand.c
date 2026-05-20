// module: mt7915.ko
// function: CheckPhyModeIsABand @ 0x1fd58
// size: 56 bytes
//

void CheckPhyModeIsABand(undefined4 param_1,undefined4 param_2)

{
  int *piVar1;
  uint uVar2;
  
  piVar1 = (int *)HcGetAutoChCtrlbyBandIdx();
  uVar2 = HcGetRadioPhyModeByBandIdx(param_1,param_2);
  *(bool *)(*piVar1 + 0x510) = (uVar2 & 0xb1) != 0;
  return;
}

