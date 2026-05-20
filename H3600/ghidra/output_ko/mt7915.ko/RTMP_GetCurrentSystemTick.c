// module: mt7915.ko
// function: RTMP_GetCurrentSystemTick @ 0x2432bc
// size: 20 bytes
//

void RTMP_GetCurrentSystemTick(undefined4 *param_1)

{
  *param_1 = jiffies;
  return;
}

