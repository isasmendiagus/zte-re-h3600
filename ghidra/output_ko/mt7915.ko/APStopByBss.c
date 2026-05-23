// module: mt7915.ko
// function: APStopByBss @ 0x11574
// size: 728 bytes
//

void APStopByBss(int param_1,int *param_2)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  undefined1 uStack_21;
  
  if (param_2 == (int *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s() Invalid Mbss\n","APStopByBss");
    }
  }
  else {
    if (2 < DebugLevel) {
      printk("===> %s() mbss_idx %d\n","APStopByBss",param_2[0x1018]);
    }
    if (*param_2 == 0) {
      if (-1 < DebugLevel) {
        printk("%s() Invalid wdev(%d)\n","APStopByBss",(char)param_2[3]);
      }
    }
    else {
      pcVar3 = &DAT_00580e8d + param_1;
      *(uint *)(param_1 + 0x795124) = *(uint *)(param_1 + 0x795124) & 0xffdfffff;
      RTMP_IndicateMediaState(param_1,0);
      do {
        if (((pcVar3[-0x20f66d] != '\x01') && (pcVar3[-0x21331b] == *(char *)((int)param_2 + 0x1a)))
           && (cVar1 = *pcVar3, cVar1 != '\0')) {
          *pcVar3 = '\0';
          ApCliIfDown(param_1);
          *pcVar3 = cVar1;
        }
        pcVar3 = pcVar3 + 0x2137b0;
      } while (pcVar3 != (char *)(param_1 + 0x9a7ded));
      if (2 < DebugLevel) {
        printk("===> %s() Disabling BCN\n","APStopByBss");
      }
      UpdateBeaconHandler(param_1,param_2,6);
      MacTableResetWdev(param_1,param_2);
      param_2[0x2c6] = param_2[0x2c6] & 0xffdfffff;
      greenap_check_when_ap_bss_change(param_1);
      RtmpOsCmdUp(mt_ate_ampdu_frame + param_1);
      AsicSetPreTbtt(param_1,0,0);
      AsicSetPiggyBack(param_1,0);
      if ((*(uint *)(param_1 + 0xa39f84) & 0x100) == 0) {
        AsicDisableSync(param_1);
      }
      MWDSDisable(param_1,(char)param_2[0x1018],1,1);
      param_2[0x237] = 0;
      iVar2 = wdev_do_linkdown(param_2);
      if ((iVar2 != 1) && (2 < DebugLevel)) {
        printk("%s() linkdown fail!!!\n","APStopByBss");
      }
      if ((*(ushort *)(param_2 + 6) & 0xb1) == 0) {
        iVar2 = wdev_do_close(param_2);
      }
      else {
        WrapDfsRadarDetectStop(param_1);
        DfsZeroHandOffRecovery(param_1,param_2);
        iVar2 = wdev_do_close(param_2);
      }
      if ((iVar2 != 1) && (2 < DebugLevel)) {
        printk("%s() close fail!!!\n","APStopByBss");
      }
      APReleaseRekeyTimer(param_1,param_2);
      if ((&DAT_003687e4)[param_1] == '\x01') {
        RTMPCancelTimer(param_1 + 0x3687b0,&uStack_21);
        (&DAT_003687e4)[param_1] = 0;
        (&DAT_003687e5)[param_1] = 0;
      }
      vow_reset(param_1);
    }
  }
  return;
}

