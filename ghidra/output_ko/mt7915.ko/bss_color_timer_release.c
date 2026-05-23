// module: mt7915.ko
// function: bss_color_timer_release @ 0x206d10
// size: 88 bytes
//

void bss_color_timer_release(int param_1)

{
  int iVar1;
  undefined1 uStack_9;
  
  iVar1 = *(int *)(param_1 + 0x14);
  if (iVar1 == 1) {
    RTMPReleaseTimer(param_1 + 0xa48,&uStack_9);
    iVar1 = *(int *)(param_1 + 0x14);
  }
  if (iVar1 != 2) {
    return;
  }
  RTMPReleaseTimer(param_1 + 0xa48,&uStack_9);
  return;
}

