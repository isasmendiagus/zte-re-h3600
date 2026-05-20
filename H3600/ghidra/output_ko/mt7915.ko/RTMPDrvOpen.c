// module: mt7915.ko
// function: RTMPDrvOpen @ 0x13d8d4
// size: 444 bytes
//

void RTMPDrvOpen(int param_1)

{
  undefined1 *unaff_r7;
  int *piVar1;
  
  *(uint *)(param_1 + 0xa39f88) = *(uint *)(param_1 + 0xa39f88) & 0xffffffdf;
  HcSetMaxStaNum();
  *(uint *)(param_1 + 0xa39f84) = *(uint *)(param_1 + 0xa39f84) | 0x10000000;
  if ((*(char *)(param_1 + 0x286285) != '\0') ||
     (MlmeAutoReconnectLastSSID(param_1,&DAT_0036db58 + param_1),
     *(char *)(param_1 + 0x286285) != '\0')) goto LAB_0013d918;
  (&DAT_0036df64)[param_1] = 0;
  (&DAT_0036df66)[param_1] = 0;
  (&DAT_0036df68)[param_1] = 0;
  if (((*(uint *)(&DAT_0036db84 + param_1) & 0xc0) == 0) ||
     ((*(uint *)(&DAT_0036dccc + param_1) & 0x20) == 0)) {
    piVar1 = &DebugLevel;
    if ((&DAT_0036df65)[param_1] == '\0') goto LAB_0013d9c4;
    if (-1 < DebugLevel) {
      printk("[PMF]%s:: Security is not WPA2/WPA2PSK AES\n","RTMPDrvOpen");
      goto LAB_0013d9c4;
    }
  }
  else {
    if ((&DAT_0036df65)[param_1] == '\0') {
      unaff_r7 = &DAT_00005b30;
    }
    (&DAT_0036df68)[param_1] = (&DAT_0036df69)[param_1];
    if ((&DAT_0036df65)[param_1] == '\0') {
      piVar1 = (int *)((uint)unaff_r7 & 0xffff | 0x5f0000);
    }
    else {
      piVar1 = &DebugLevel;
      (&DAT_0036df64)[param_1] = 1;
      (&DAT_0036df66)[param_1] = (&DAT_0036df67)[param_1];
      if ((&DAT_0036df67)[param_1] != '\0') {
        (&DAT_0036df68)[param_1] = 1;
      }
    }
LAB_0013d9c4:
    if (-1 < *piVar1) {
      printk("[PMF]%s:: MFPC=%d, MFPR=%d, SHA256=%d\n","RTMPDrvOpen",(&DAT_0036df64)[param_1],
             (&DAT_0036df66)[param_1],(&DAT_0036df68)[param_1]);
    }
    if (*(char *)(param_1 + 0x286285) != '\0') goto LAB_0013d918;
  }
  WscGenerateUUID(param_1,s_QUEUE_INFO_00371858 + param_1 + 8,
                  s_QUE_SIZE_PEAK_CURR_00371864 + param_1 + 0xc,0,0,0);
  WscInit(param_1,0,0);
  WscInitRegistrarPair(param_1,&DAT_0036ee3c + param_1,0);
LAB_0013d918:
  WSC_HDR_BTN_Init(param_1);
  vow_init(param_1);
  cp_support_is_enabled(param_1);
  return;
}

