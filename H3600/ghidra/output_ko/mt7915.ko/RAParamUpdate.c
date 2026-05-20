// module: mt7915.ko
// function: RAParamUpdate @ 0x1d930c
// size: 100 bytes
//

void RAParamUpdate(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (*(char *)(param_2 + 0x13c0) != '\x01') {
    return;
  }
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  raWrapperEntrySet(param_1,param_2,param_2 + 0x13c0);
  if (*(char *)(iVar1 + 0x150) != '\x01') {
    return;
  }
  WifiSysUpdateRa(param_1,param_2,param_3,param_4);
  return;
}

