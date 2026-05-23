// module: mt7915.ko
// function: RTMP_OS_Del_Timer @ 0x2453d0
// size: 40 bytes
//

void RTMP_OS_Del_Timer(int *param_1,undefined1 *param_2)

{
  undefined1 uVar1;
  
  if (*param_1 != 0) {
    uVar1 = del_timer_sync();
    *param_2 = uVar1;
    return;
  }
  *param_2 = 1;
  return;
}

