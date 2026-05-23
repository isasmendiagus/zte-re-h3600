// module: mt7915.ko
// function: ChannelInfoDestroy @ 0x1fc5c
// size: 88 bytes
//

void ChannelInfoDestroy(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int *piVar1;
  undefined4 extraout_r2;
  undefined4 extraout_r2_00;
  undefined4 uVar2;
  undefined4 extraout_r3;
  undefined4 uVar3;
  
  piVar1 = (int *)HcGetAutoChCtrlbyBandIdx(param_1,0,param_3,param_4,param_4);
  uVar3 = extraout_r3;
  uVar2 = extraout_r2;
  if (*piVar1 != 0) {
    os_free_mem();
    uVar3 = 0;
    *piVar1 = 0;
    uVar2 = extraout_r2_00;
  }
  piVar1 = (int *)HcGetAutoChCtrlbyBandIdx(param_1,1,uVar2,uVar3,param_4);
  if (*piVar1 == 0) {
    return;
  }
  os_free_mem();
  *piVar1 = 0;
  return;
}

