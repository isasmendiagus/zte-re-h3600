// module: mt7915.ko
// function: SetBFBackoffInfo @ 0xc0460
// size: 24 bytes
//

undefined4
SetBFBackoffInfo(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  MtShowPwrLimitTable(param_1,1,1,param_4,param_4);
  return 1;
}

