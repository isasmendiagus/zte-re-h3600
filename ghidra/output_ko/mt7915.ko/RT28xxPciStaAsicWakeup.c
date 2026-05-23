// module: mt7915.ko
// function: RT28xxPciStaAsicWakeup @ 0x1c8ff0
// size: 20 bytes
//

void RT28xxPciStaAsicWakeup(undefined4 param_1,undefined4 param_2,int param_3)

{
  if (param_3 == 0) {
    return;
  }
  RTMPOffloadPm(param_1,param_3,4,2);
  return;
}

