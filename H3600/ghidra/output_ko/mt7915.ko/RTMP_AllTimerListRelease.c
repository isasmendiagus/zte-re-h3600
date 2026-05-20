// module: mt7915.ko
// function: RTMP_AllTimerListRelease @ 0x13c87c
// size: 152 bytes
//

void RTMP_AllTimerListRelease(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  undefined1 auStack_19 [5];
  
  piVar1 = (int *)*(int *)(param_1 + 0xa78490);
  while (piVar1 != (int *)0x0) {
    iVar2 = piVar1[1];
    iVar3 = *piVar1;
    if (2 < DebugLevel) {
      printk("%s: Timer is allocated by %pS,Valid:%d,Lock:%lx,State:%d\n","RTMP_AllTimerListRelease"
             ,*(undefined4 *)(iVar2 + 0x30),*(undefined1 *)(iVar2 + 0x1c),
             *(undefined4 *)(iVar2 + 0x2c),*(undefined1 *)(iVar2 + 0x1d));
      iVar2 = piVar1[1];
    }
    RTMPReleaseTimer(iVar2,auStack_19);
    piVar1 = (int *)iVar3;
  }
  *(undefined4 *)(param_1 + 0xa78494) = 0;
  *(undefined4 *)(param_1 + 0xa78490) = 0;
  *(undefined1 *)(param_1 + 0xa78498) = 0;
  return;
}

