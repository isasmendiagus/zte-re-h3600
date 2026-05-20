// module: mt7915.ko
// function: _802_11_CounterMeasureHdlr @ 0xc4680
// size: 48 bytes
//

undefined4 _802_11_CounterMeasureHdlr(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  if (*(char *)(param_1 + 0x286285) != '\x01') {
    return 0;
  }
  HandleCounterMeasure(param_1,*(undefined4 *)(param_2 + 4),param_3,1,param_4);
  return 0;
}

