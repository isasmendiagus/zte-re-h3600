// module: mt7915.ko
// function: bss_color_timer_init @ 0x206c8c
// size: 132 bytes
//

void bss_color_timer_init(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = *(int *)(param_1 + 0x14);
  uVar2 = *(undefined4 *)(param_1 + 8);
  if (iVar1 == 1) {
    RTMPInitTimer(uVar2,param_1 + 0xa48,rtmp_timer_trigger_timer_callback,param_1,0);
    iVar1 = *(int *)(param_1 + 0x14);
  }
  if (iVar1 != 2) {
    return;
  }
  RTMPInitTimer(uVar2,param_1 + 0xa48,rtmp_timer_notify_timer_callback,param_1,0);
  return;
}

