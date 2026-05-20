// module: mt7915.ko
// function: StaRecUpdateRa @ 0x1c3430
// size: 144 bytes
//

undefined4 StaRecUpdateRa(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  iVar2 = *(int *)(param_3 + 0x9c);
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  if (iVar2 == 0) {
    uVar1 = 0xffffffff;
  }
  else {
    os_zero_mem(&local_48,0x38);
    StaRecAutoRateParamSet(iVar2 + 0x13c0,&local_48);
    AndesAppendCmdMsg(param_2,&local_48,0x38);
    uVar1 = 0;
  }
  return uVar1;
}

