// module: mt7915.ko
// function: StaRecUpdateRaUpdate @ 0x1c33ac
// size: 132 bytes
//

undefined4 StaRecUpdateRaUpdate(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  iVar2 = *(int *)(param_3 + 0x9c);
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  if (iVar2 == 0) {
    uVar1 = 0xffffffff;
  }
  else {
    os_zero_mem(&local_34,0x1c);
    StaRecAutoRateUpdate(iVar2 + 0x13c0,iVar2 + 0x1404,*(undefined4 *)(param_3 + 0xa0),&local_34);
    AndesAppendCmdMsg(param_2,&local_34,0x1c);
    uVar1 = 0;
  }
  return uVar1;
}

