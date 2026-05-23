// module: mt7915.ko
// function: MT_ATELowPower @ 0x27e430
// size: 36 bytes
//

undefined4 MT_ATELowPower(undefined4 param_1,int param_2)

{
  if (param_2 == 0) {
    MlmeLpExit();
    return 0;
  }
  MlmeLpEnter();
  return 0;
}

