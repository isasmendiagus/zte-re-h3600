// module: mt7915.ko
// function: tmr_handler @ 0xc6270
// size: 28 bytes
//

undefined4 tmr_handler(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  TmrReportParser(param_1,param_3,0,0,param_4);
  return 1;
}

