// module: mt7915.ko
// function: RTMP_OS_Mod_Timer @ 0x24539c
// size: 52 bytes
//

void RTMP_OS_Mod_Timer(undefined4 param_1,int param_2)

{
  mod_timer(param_1,jiffies + (uint)(param_2 * 100) / 1000,param_2 * 0x6666666c);
  return;
}

