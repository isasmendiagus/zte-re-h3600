// module: mt7915.ko
// function: HwCtrlWakeUp @ 0xaef48
// size: 28 bytes
//

undefined4 HwCtrlWakeUp(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  AsicWakeup(param_1,1,**(undefined4 **)(param_2 + 8),*(undefined4 **)(param_2 + 8),param_4);
  return 0;
}

