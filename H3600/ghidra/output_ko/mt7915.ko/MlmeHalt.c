// module: mt7915.ko
// function: MlmeHalt @ 0x12db44
// size: 756 bytes
//

void MlmeHalt(int param_1)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  undefined1 auStack_29 [5];
  
  if (2 < DebugLevel) {
    printk("==> MlmeHalt\n");
  }
  *(uint *)(param_1 + 0xa39f84) = *(uint *)(param_1 + 0xa39f84) & 0xfffffffb;
  iVar1 = RtmpOSTaskKill(param_1 + 0x286298);
  if ((iVar1 == 1) && (-1 < DebugLevel)) {
    printk("kill mlme task failed!\n");
  }
  unregister_wsys_notifier(param_1 + 0xa7bed4,param_1 + 0x82925c);
  if ((*(uint *)(param_1 + 0xa39f84) & 0x100) == 0) {
    AsicDisableSync(param_1);
  }
  RTMPReleaseTimer(param_1 + 0x82910c,auStack_29);
  if ((*(byte *)(param_1 + 0x286294) & 1) != 0) {
    iVar1 = param_1 + 0x57ffc8;
    pcVar3 = s__d__d__d__d__d_0037169c + param_1 + 0x18;
    do {
      RTMPReleaseTimer(iVar1 + -0x5bc,auStack_29);
      RTMPReleaseTimer(iVar1 + -0x588,auStack_29);
      RTMPReleaseTimer(iVar1 + -0x554,auStack_29);
      RTMPReleaseTimer(iVar1 + -0x5f0,auStack_29);
      RTMPReleaseTimer(iVar1 + -0x624,auStack_29);
      RTMPReleaseTimer(iVar1,auStack_29);
      if (pcVar3[-4] != '\0') {
        pcVar3[-4] = '\0';
        RTMPCancelTimer(pcVar3,auStack_29);
      }
      pcVar3 = pcVar3 + 0x2137b0;
      if (*(char *)(iVar1 + 0xd00) != '\0') {
        RTMPReleaseTimer(iVar1 + 0xccc,auStack_29);
        *(undefined1 *)(iVar1 + 0xd00) = 0;
      }
      iVar2 = iVar1 + -0xd0;
      iVar1 = iVar1 + 0x2137b0;
      RTMPReleaseTimer(iVar2,auStack_29);
    } while (iVar1 != param_1 + 0x9a6f28);
  }
  RTMPReleaseTimer(param_1 + 0x829224,auStack_29);
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    RTMPReleaseTimer(param_1 + 0x829140,auStack_29);
    RTMPReleaseTimer(param_1 + 0x36b8d4,auStack_29);
    if (s__d__d__d__d__d_0037169c[param_1 + 0x14] != '\0') {
      s__d__d__d__d__d_0037169c[param_1 + 0x14] = '\0';
      RTMPReleaseTimer(s__d__d__d__d__d_0037169c + param_1 + 0x18,auStack_29);
    }
    if ((&DAT_00584e60)[param_1] != '\0') {
      (&DAT_00584e60)[param_1] = 0;
      RTMPReleaseTimer(param_1 + 0x584e64,auStack_29);
    }
  }
  GASCtrlExit(param_1);
  WNMCtrlExit(param_1);
  if ((*(uint *)(param_1 + 0xa39f84) & 0x100) == 0) {
    iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
    if (*(code **)(iVar1 + 0x38) != (code *)0x0) {
      (**(code **)(iVar1 + 0x38))(param_1);
    }
  }
  RtmpusecDelay(5000);
  MlmeQueueDestroy(param_1 + 0x7960f8);
  if (2 < DebugLevel) {
    printk("<== MlmeHalt\n");
  }
  return;
}

