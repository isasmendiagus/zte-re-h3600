// module: mt7915.ko
// function: MtAsicSetReptFuncEnableByFw @ 0x199b9c
// size: 76 bytes
//

undefined4 MtAsicSetReptFuncEnableByFw(undefined4 param_1,int param_2,undefined1 param_3)

{
  bool local_1d [12];
  undefined1 local_11;
  
  __memzero(local_1d,0xd);
  local_1d[0] = param_2 == 1;
  local_11 = param_3;
  MtCmdMuarConfigSet(param_1,local_1d);
  return 1;
}

