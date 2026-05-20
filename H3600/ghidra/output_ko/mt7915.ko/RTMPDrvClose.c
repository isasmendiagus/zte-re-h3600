// module: mt7915.ko
// function: RTMPDrvClose @ 0x13da94
// size: 956 bytes
//

void RTMPDrvClose(int param_1)

{
  char *pcVar1;
  int iVar2;
  char cVar3;
  undefined1 local_21;
  
  *(uint *)(param_1 + 0xa39f84) = *(uint *)(param_1 + 0xa39f84) | 0x80000000;
  if (*(char *)(param_1 + 0x286285) == '\0') {
    if (((*(uint *)(&DAT_0057ffbc + param_1) & 1) != 0) && ((&DAT_00580018)[param_1] != '\0')) {
      RTMP_FORCE_WAKEUP(param_1,&DAT_0036db58 + param_1);
    }
    if (((*(uint *)(param_1 + 0x79376c) & 1) != 0) && (*(char *)(param_1 + 0x7937c8) != '\0')) {
      RTMP_FORCE_WAKEUP(param_1,&DAT_00581308 + param_1);
    }
    iVar2 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
    *(undefined1 *)(iVar2 + 0x90) = 0;
  }
  __memzero(param_1 + 0x794b61,0xba);
  iVar2 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar2 == 2) {
    *(uint *)(param_1 + 0xa39f84) = *(uint *)(param_1 + 0xa39f84) | 0x40;
  }
  *(undefined1 *)(param_1 + 0x794c30) = 0;
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    local_21 = 0;
    if ((*(byte *)(param_1 + 0x795652) & 1) != 0) {
      RTMPCancelTimer(param_1 + 0x795654,&local_21);
      *(undefined1 *)(param_1 + 0x795652) = 0;
      cVar3 = *(char *)(param_1 + 0x286285);
      if (cVar3 == '\0') goto LAB_0013ddd4;
      goto LAB_0013dde8;
    }
  }
  else {
    if (*(char *)(param_1 + 0x286285) != '\0') goto LAB_0013db24;
LAB_0013ddd4:
    MacTableReset(param_1);
    MATEngineExit(param_1);
    cVar3 = *(char *)(param_1 + 0x286285);
LAB_0013dde8:
    if (cVar3 != '\x01') goto LAB_0013db24;
  }
  *(undefined4 *)(&DAT_003678e8 + param_1) = 0;
  *(undefined4 *)(&DAT_003678ec + param_1) = 0;
  MATEngineExit(param_1);
  APShutdown(param_1);
LAB_0013db24:
  ATEExit(param_1);
  MlmeHalt(param_1);
  NICRestartFirmware(param_1);
  hif_poll_txrx_empty(*(undefined4 *)(param_1 + 0xa797a0),0xff);
  MeasureReqTabExit(param_1);
  TpcReqTabExit(param_1);
  RtmpMgmtTaskExit(param_1);
  if ((*(uint *)(param_1 + 0xa39f84) & 0x2000) != 0) {
    iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
    if (*(code **)(iVar2 + 0xbc) != (code *)0x0) {
      (**(code **)(iVar2 + 0xbc))(param_1,2);
    }
    chip_interrupt_disable(param_1);
  }
  if ((((*(uint *)(param_1 + 0x286280) & 0xfffffffb) == 1) &&
      (iVar2 = RT28xxPciAsicRadioOff(param_1,2,0), iVar2 == 0)) && (-1 < DebugLevel)) {
    printk("%s call RT28xxPciAsicRadioOff fail !!\n","RTMPDrvClose");
  }
  if ((*(uint *)(param_1 + 0xa39f84) & 2) != 0) {
    *(uint *)(param_1 + 0xa39f84) = *(uint *)(param_1 + 0xa39f84) & 0xfffffffd;
  }
  RTMPResetSkuParam(param_1);
  RTMPResetBackOffParam(param_1);
  tm_exit(param_1);
  qm_exit(param_1);
  tr_ctl_exit(param_1);
  WfSysPosExit(param_1);
  *(uint *)(param_1 + 0xa39f84) = *(uint *)(param_1 + 0xa39f84) & 0xffffffbf;
  UserCfgExit(param_1);
  iVar2 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar2 == 2) {
    ExitTxSTypeTable(param_1);
  }
  BackgroundScanDeInit(param_1);
  AutoChSelRelease(param_1);
  *(uint *)(param_1 + 0xa39f84) = *(uint *)(param_1 + 0xa39f84) & 0xefffffff;
  __memzero(param_1 + 0xa1920,0x1e4038);
  RepeaterCliReset(param_1);
  RtmpusecDelay(2000);
  RTMP_AllTimerListRelease(param_1);
  FwOwn(param_1);
  HwCtrlExit(param_1);
  os_free_mem(*(undefined4 *)("Set_IRR_TTGOnOff" + param_1 + 4));
  pcVar1 = "Set_IRR_TTGOnOff" + param_1 + 4;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  if (*(int *)(param_1 + 0xa7c214) != 0) {
    os_zero_mem(*(int *)(param_1 + 0xa7c214),*(undefined2 *)(param_1 + 0xa7c210));
    os_free_mem(*(undefined4 *)(param_1 + 0xa7c214));
    *(undefined4 *)(param_1 + 0xa7c214) = 0;
    *(undefined2 *)(param_1 + 0xa7c210) = 0;
  }
  if (*(int *)(param_1 + 0xa78acc) != 0) {
    os_free_mem();
  }
  if (*(int *)(param_1 + 0xa78a88) != 0) {
    os_free_mem();
  }
  if (*(int *)(param_1 + 0xa78a8c) != 0) {
    os_free_mem();
  }
  if (*(int *)(param_1 + 0xa78a90) != 0) {
    os_free_mem();
  }
  multi_profile_exit(param_1);
  return;
}

