// module: mt7915.ko
// function: RRM_CfgInit @ 0x2202f4
// size: 524 bytes
//

void RRM_CfgInit(int param_1)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  bool bVar5;
  
  pcVar2 = "%u-%02x:%02x:%02x:%02x:%02x:%02x" + param_1 + 0x1c;
  iVar3 = 0;
  while( true ) {
    iVar4 = 0;
    iVar1 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    if (iVar1 <= iVar3) break;
    pcVar2[0x6a] = '\x1e';
    pcVar2[0x6b] = '\x14';
    pcVar2[0x69] = -0x38;
    RTMPInitTimer(param_1,pcVar2,rtmp_timer_RRM_QuietOffsetTimeout,param_1,0);
    RTMPInitTimer(param_1,pcVar2 + 0x34,rtmp_timer_RRM_QuietTimeout,param_1,0);
    iVar1 = iVar3 * 0x5834 + param_1;
    pcVar2[-8] = '\0';
    pcVar2[-10] = '\0';
    if (pcVar2[-0xc] == '\0') {
      pcVar2[-0xb] = '\0';
    }
    pcVar2[-0xffffffff00000006] = '\x01';
    pcVar2[-0xffffffff00000005] = '\0';
    "The entry Level %d - %02x:%02x:%02x:%02x:%02x:%02x is set complete!\n"[iVar1 + 0x30] = '\0';
    "The entry Level %d - %02x:%02x:%02x:%02x:%02x:%02x is set complete!\n"[iVar1 + 0x31] = '\0';
    iVar3 = iVar3 + 1;
    "The entry Level %d - %02x:%02x:%02x:%02x:%02x:%02x is set complete!\n"[iVar1 + 0x32] = '\0';
    pcVar2 = pcVar2 + 0x5834;
    "The entry Level %d - %02x:%02x:%02x:%02x:%02x:%02x is set complete!\n"[iVar1 + 0x33] = '\0';
    "The entry Level %d - %02x:%02x:%02x:%02x:%02x:%02x is set complete!\n"[iVar1 + 0x34] = '\0';
    "The entry Level %d - %02x:%02x:%02x:%02x:%02x:%02x is set complete!\n"[iVar1 + 0x35] = '\0';
    "The entry Level %d - %02x:%02x:%02x:%02x:%02x:%02x is set complete!\n"[iVar1 + 0x36] = '\0';
    "The entry Level %d - %02x:%02x:%02x:%02x:%02x:%02x is set complete!\n"[iVar1 + 0x2f] = '\x02';
    *(undefined4 *)
     ("The entry Level %d - %02x:%02x:%02x:%02x:%02x:%02x is set complete!\n" + iVar1 + 0x2b) =
         *(undefined4 *)
          ("The entry Level %d - %02x:%02x:%02x:%02x:%02x:%02x is set complete!\n" + iVar1 + 0x33);
    *(undefined4 *)
     ("The entry Level %d - %02x:%02x:%02x:%02x:%02x:%02x is set complete!\n" + iVar1 + 0x27) =
         *(undefined4 *)
          ("The entry Level %d - %02x:%02x:%02x:%02x:%02x:%02x is set complete!\n" + iVar1 + 0x2f);
  }
  iVar3 = param_1 + 0x36e684;
  do {
    *(undefined1 *)(iVar3 + 0x69) = 200;
    *(undefined1 *)(iVar3 + 0x6a) = 0x1e;
    *(undefined1 *)(iVar3 + 0x6b) = 0x14;
    RTMPInitTimer(param_1,iVar3,rtmp_timer_RRM_QuietOffsetTimeout,param_1,0);
    RTMPInitTimer(param_1,iVar3 + 0x34,rtmp_timer_RRM_QuietTimeout,param_1,0);
    *(undefined1 *)(iVar3 + -8) = 0;
    *(undefined1 *)(iVar3 + -10) = 0;
    iVar1 = param_1 + iVar4 * 0x2137b0;
    if (*(char *)(iVar3 + -0xc) == '\0') {
      *(undefined1 *)(iVar3 + -0xb) = 0;
    }
    *(undefined2 *)(iVar3 + -6) = 1;
    bVar5 = iVar4 != 1;
    (&DAT_0036e6ff)[iVar1] = 0;
    (&DAT_0036e700)[iVar1] = 0;
    (&DAT_0036e701)[iVar1] = 0;
    iVar4 = 1;
    (&DAT_0036e702)[iVar1] = 0;
    iVar3 = iVar3 + 0x2137b0;
    (&DAT_0036e6fc)[iVar1] = 0;
    (&DAT_0036e6fd)[iVar1] = 0;
    (&DAT_0036e6fe)[iVar1] = 0;
    (&DAT_0036e6fb)[iVar1] = 0x70;
    *(undefined4 *)(&DAT_0036e6f7 + iVar1) = *(undefined4 *)(&DAT_0036e6ff + iVar1);
    *(undefined4 *)(&DAT_0036e6f3 + iVar1) = *(undefined4 *)(&DAT_0036e6fb + iVar1);
  } while (bVar5);
  return;
}

