// module: mt7915.ko
// function: RTMP_GetCurrentSystemTime @ 0x2432a8
// size: 20 bytes
//

void RTMP_GetCurrentSystemTime(undefined4 *param_1)

{
  *param_1 = jiffies;
  return;
}

