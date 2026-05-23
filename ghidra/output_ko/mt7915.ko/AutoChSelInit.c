// module: mt7915.ko
// function: AutoChSelInit @ 0x26690
// size: 80 bytes
//

void AutoChSelInit(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = HcGetAutoChCtrlbyBandIdx(param_1,0);
  AutoChSelStateMachineInit(param_1,0,iVar1 + 0x4c,iVar1 + 100);
  iVar1 = HcGetAutoChCtrlbyBandIdx(param_1,1);
  AutoChSelStateMachineInit(param_1,1,iVar1 + 0x4c,iVar1 + 100);
  return;
}

