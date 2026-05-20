// module: mt7915.ko
// function: mtRddControl @ 0x234a94
// size: 88 bytes
//

void mtRddControl(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (3 < DebugLevel) {
    printk("[mtRddControl]RddCtrl=%d, RddIdx=%d, RddRxSel=%d\n");
  }
  MtCmdRddCtrl(param_1,param_2,param_3,param_4);
  return;
}

