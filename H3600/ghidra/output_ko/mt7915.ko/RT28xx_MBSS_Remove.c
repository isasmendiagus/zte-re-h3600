// module: mt7915.ko
// function: RT28xx_MBSS_Remove @ 0x5294c
// size: 40 bytes
//

void RT28xx_MBSS_Remove(undefined4 param_1)

{
  RTMP_AP_IoctlHandle(param_1,0,0x18,0,0,0);
  return;
}

