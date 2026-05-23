// module: mt7915.ko
// function: WscThreadExit @ 0x1ed8b4
// size: 1288 bytes
//

undefined4 WscThreadExit(int param_1)

{
  int iVar1;
  char *pcVar2;
  char cVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  char *pcVar7;
  undefined1 uStack_2a;
  undefined1 auStack_29 [5];
  
  iVar1 = RtmpOSTaskKill(param_1 + 0x794ae8);
  if ((iVar1 == 1) && (-1 < DebugLevel)) {
    printk("kill wsc task failed!\n");
  }
  if (*(int *)(param_1 + 0xa77c3c) != 0) {
    os_free_mem();
    *(undefined4 *)(param_1 + 0xa77c3c) = 0;
  }
  if (*(int *)(param_1 + 0x794b20) != 0) {
    os_free_mem();
    *(undefined4 *)(param_1 + 0x794b20) = 0;
  }
  cVar3 = *(char *)(param_1 + 0x286285);
  if (cVar3 == '\x01') {
    iVar1 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    if (iVar1 != 0) {
      iVar6 = 0;
      pcVar7 = "IF(ra0) Set_WscConfMode_Proc::(WscConfMode(0,1,2)=%d)\n" + param_1 + 0x10;
      do {
        _WscStop(param_1,0,pcVar7 + -0x27cc,0);
        iVar6 = iVar6 + 1;
        RTMPReleaseTimer(pcVar7,&uStack_2a);
        RTMPReleaseTimer(pcVar7 + -0xb70,&uStack_2a);
        RTMPReleaseTimer(pcVar7 + -0x38,&uStack_2a);
        RTMPReleaseTimer(pcVar7 + 0x444,&uStack_2a);
        RTMPReleaseTimer(pcVar7 + 0x164,&uStack_2a);
        RTMPReleaseTimer(pcVar7 + 0x19c,&uStack_2a);
        RTMPReleaseTimer(pcVar7 + 0x368,&uStack_2a);
        RTMPReleaseTimer(pcVar7 + 0x3a0,&uStack_2a);
        pcVar7[0x41c] = '\0';
        pcVar7[0x41d] = '\0';
        pcVar7[0x41e] = '\0';
        pcVar7[0x41f] = '\0';
        if (*(int *)(pcVar7 + 0x418) != 0) {
          os_free_mem();
          pcVar7[0x418] = '\0';
          pcVar7[0x419] = '\0';
          pcVar7[0x41a] = '\0';
          pcVar7[0x41b] = '\0';
        }
        pcVar7[0x424] = '\0';
        pcVar7[0x425] = '\0';
        pcVar7[0x426] = '\0';
        pcVar7[0x427] = '\0';
        if (*(int *)(pcVar7 + 0x428) != 0) {
          os_free_mem();
          pcVar7[0x428] = '\0';
          pcVar7[0x429] = '\0';
          pcVar7[0x42a] = '\0';
          pcVar7[0x42b] = '\0';
        }
        if (pcVar7[0x3d4] != '\0') {
          pcVar7[0x3d4] = '\0';
          RTMPCancelTimer(pcVar7 + 0x3a0,auStack_29);
        }
        if (*(int *)(pcVar7 + 0x35c) != 0) {
          os_free_mem();
          pcVar7[0x35c] = '\0';
          pcVar7[0x35d] = '\0';
          pcVar7[0x35e] = '\0';
          pcVar7[0x35f] = '\0';
        }
        pcVar2 = pcVar7 + 0x438;
        pcVar7 = pcVar7 + 0x5834;
        WscClearPeerList(pcVar2);
      } while (iVar6 != iVar1);
    }
    pcVar7 = s__________________________________00371600 + param_1 + 8;
    do {
      _WscStop(param_1,1,pcVar7 + -0x27cc,0);
      RTMPReleaseTimer(pcVar7,&uStack_2a);
      RTMPReleaseTimer(pcVar7 + -0xb70,&uStack_2a);
      RTMPReleaseTimer(pcVar7 + -0x38,&uStack_2a);
      RTMPReleaseTimer(pcVar7 + 0x444,&uStack_2a);
      RTMPReleaseTimer(pcVar7 + 0x164,&uStack_2a);
      RTMPReleaseTimer(pcVar7 + 0x19c,&uStack_2a);
      RTMPReleaseTimer(pcVar7 + 0x3c,&uStack_2a);
      RTMPReleaseTimer(pcVar7 + 0x74,&uStack_2a);
      RTMPReleaseTimer(pcVar7 + 0xac,&uStack_2a);
      RTMPReleaseTimer(pcVar7 + 0xe4,&uStack_2a);
      pcVar7[0x424] = '\0';
      pcVar7[0x425] = '\0';
      pcVar7[0x426] = '\0';
      pcVar7[0x427] = '\0';
      if (*(int *)(pcVar7 + 0x428) != 0) {
        os_free_mem();
        pcVar7[0x428] = '\0';
        pcVar7[0x429] = '\0';
        pcVar7[0x42a] = '\0';
        pcVar7[0x42b] = '\0';
      }
      pcVar7[0x41c] = '\0';
      pcVar7[0x41d] = '\0';
      pcVar7[0x41e] = '\0';
      pcVar7[0x41f] = '\0';
      if (*(int *)(pcVar7 + 0x418) != 0) {
        os_free_mem();
        pcVar7[0x418] = '\0';
        pcVar7[0x419] = '\0';
        pcVar7[0x41a] = '\0';
        pcVar7[0x41b] = '\0';
      }
      pcVar2 = pcVar7 + 0x438;
      pcVar7 = pcVar7 + 0x2137b0;
      WscClearPeerList(pcVar2);
    } while (pcVar7 != (char *)(param_1 + 0x798568));
    RTMPReleaseTimer(param_1 + 0x36da54,&uStack_2a);
    cVar3 = *(char *)(param_1 + 0x286285);
  }
  if ((cVar3 == '\0') && (*(char *)(param_1 + 0x794ab9) != '\0')) {
    uVar4 = 0;
    do {
      iVar1 = uVar4 * 0x2137b0;
      iVar6 = iVar1 + 0x370000;
      _WscStop(param_1,0,&DAT_0036ee3c + param_1 + iVar1,0);
      RTMPReleaseTimer(param_1 + iVar6 + 0x1608,&uStack_2a);
      RTMPReleaseTimer(param_1 + iVar6 + 0xa98,&uStack_2a);
      RTMPReleaseTimer(s_start___>__s_003715c4 + param_1 + iVar1 + 0xc,&uStack_2a);
      RTMPReleaseTimer(s_>>>_ENTRY_dic_handler_wifi__cmd__00371a4c + param_1 + iVar1,&uStack_2a);
      RTMPReleaseTimer(s_CPU_MODE_STACK_INFO__size_in_byt_0037176c + param_1 + iVar1,&uStack_2a);
      RTMPReleaseTimer(s_START_END_SIZE_PEAK_INTEGRITY_00371790 + param_1 + iVar1 + 0x14,&uStack_2a)
      ;
      RTMPReleaseTimer(param_1 + iVar6 + 0x1644,&uStack_2a);
      RTMPReleaseTimer(s_ISR_XTIME_RATIO_MAX_XTM_ENTRY_CN_00371668 + param_1 + iVar1 + 0x14,
                       &uStack_2a);
      RTMPReleaseTimer(s__d__d__d__d__d_0037169c + param_1 + iVar1 + 0x18,&uStack_2a);
      RTMPReleaseTimer(s____addtional_information_0037195c + param_1 + iVar1 + 0x14,&uStack_2a);
      RTMPReleaseTimer(s_exp_main__jump_from_cos_assert_003719a8 + param_1 + iVar1,&uStack_2a);
      iVar1 = param_1 + iVar1;
      pcVar7 = s_exp_main__maybe_jump_from_RST_00371a08 + iVar1 + 0x1c;
      pcVar7[0] = '\0';
      pcVar7[1] = '\0';
      pcVar7[2] = '\0';
      pcVar7[3] = '\0';
      if (*(int *)(s_exp_main__maybe_jump_from_RST_00371a08 + iVar1 + 0x18) != 0) {
        os_free_mem();
        pcVar7 = s_exp_main__maybe_jump_from_RST_00371a08 + iVar1 + 0x18;
        pcVar7[0] = '\0';
        pcVar7[1] = '\0';
        pcVar7[2] = '\0';
        pcVar7[3] = '\0';
      }
      iVar6 = param_1 + uVar4 * 0x2137b0;
      iVar1 = *(int *)(s_TotalTimeForDump_0x_x____d_secs__00371a28 + iVar6 + 8);
      pcVar7 = s_TotalTimeForDump_0x_x____d_secs__00371a28 + iVar6 + 4;
      pcVar7[0] = '\0';
      pcVar7[1] = '\0';
      pcVar7[2] = '\0';
      pcVar7[3] = '\0';
      if (iVar1 != 0) {
        os_free_mem();
        pcVar7 = s_TotalTimeForDump_0x_x____d_secs__00371a28 + iVar6 + 8;
        pcVar7[0] = '\0';
        pcVar7[1] = '\0';
        pcVar7[2] = '\0';
        pcVar7[3] = '\0';
      }
      uVar5 = uVar4 + 1 & 0xff;
      WscClearPeerList(s_TotalTimeForDump_0x_x____d_secs__00371a28 +
                       param_1 + uVar4 * 0x2137b0 + 0x18);
      uVar4 = uVar5;
    } while (uVar5 < *(byte *)(param_1 + 0x794ab9));
  }
  *(undefined1 *)(param_1 + 0x795971) = 0;
  return 1;
}

