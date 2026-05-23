// module: mt7915.ko
// function: SetSKUInfo @ 0xc0448
// size: 24 bytes
//

undefined4 SetSKUInfo(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  MtShowPwrLimitTable(param_1,0,1,param_4,param_4);
  return 1;
}

