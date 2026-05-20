// module: mt7915.ko
// function: RT28xxPciStaAsicSleepAutoWakeup @ 0x1c9004
// size: 20 bytes
//

void RT28xxPciStaAsicSleepAutoWakeup(undefined4 param_1,int param_2)

{
  if (param_2 == 0) {
    return;
  }
  RTMPOffloadPm(param_1,param_2,4,1);
  return;
}

