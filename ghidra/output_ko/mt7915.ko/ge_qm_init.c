// module: mt7915.ko
// function: ge_qm_init @ 0xd1d30
// size: 416 bytes
//

undefined4 ge_qm_init(int param_1)

{
  char *pcVar1;
  char cVar2;
  int iVar3;
  
  iVar3 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  *(undefined4 *)(param_1 + 0x285b3c) = 0;
  *(undefined4 *)(param_1 + 0x285b50) = 0;
  *(undefined4 *)(param_1 + 0x285b4c) = 0;
  *(undefined4 *)(param_1 + 0x285b54) = 0;
  *(undefined4 *)(param_1 + 0x285b98) = 0;
  *(undefined4 *)(param_1 + 0x285ba0) = 0;
  *(undefined4 *)(param_1 + 0x285b9c) = 0;
  *(undefined4 *)(param_1 + 0x285ba4) = 0;
  *(undefined4 *)(param_1 + 0x28633c) = 0;
  *(undefined4 *)(param_1 + 0x286340) = 0;
  *(undefined4 *)(param_1 + 0x286344) = 0;
  *(undefined4 *)(param_1 + 0x286348) = 0;
  *(undefined4 *)(param_1 + 0x286338) = 0x400;
  __memzero(param_1 + 0x28634c,0x10060);
  *(undefined4 *)(param_1 + 0x28a354) = 5;
  *(undefined4 *)(param_1 + 0x28a358) = 0x800;
  *(undefined4 *)(param_1 + 0x28e36c) = 5;
  *(undefined4 *)(param_1 + 0x28e370) = 0x800;
  pcVar1 = "SetTriggerBbpProc" + param_1 + 8;
  pcVar1[0] = '\x05';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  pcVar1 = "SetTriggerBbpProc" + param_1 + 0xc;
  pcVar1[0] = '\0';
  pcVar1[1] = '\b';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  *(undefined4 *)(&DAT_0029639c + param_1) = 5;
  *(undefined4 *)(&DAT_002963a0 + param_1) = 0x800;
  cVar2 = *(char *)(iVar3 + 0x15b);
  *(undefined4 *)(param_1 + 0x285c14) = 0;
  if (cVar2 == '\0') {
    *(undefined4 *)(param_1 + 0x285bf0) = 0;
    *(undefined4 *)(param_1 + 0x285bf8) = 0;
    *(undefined4 *)(param_1 + 0x285bf4) = 0;
    *(undefined4 *)(param_1 + 0x285bfc) = 0;
  }
  RTMPInitTimer(param_1,param_1 + 0x285c18,rtmp_timer_amsdu_history_exec,param_1,1);
  RTMPSetTimer(param_1 + 0x285c18,1000);
  *(undefined1 *)(param_1 + 0x9daa2) = *(undefined1 *)(iVar3 + 0x1c5);
  *(undefined1 *)(param_1 + 0x9daa1) = 0;
  iVar3 = *(int *)(iVar3 + 0x1f0);
  if (iVar3 == 0) {
    iVar3 = 0x200;
  }
  *(int *)(param_1 + 0xa18f8) = iVar3;
  *(int *)(param_1 + 0x286308) = param_1 + 0x286308;
  *(int *)(param_1 + 0x28630c) = param_1 + 0x286308;
  *(int *)(param_1 + 0x286310) = param_1 + 0x286310;
  *(int *)(param_1 + 0x286314) = param_1 + 0x286310;
  *(int *)(param_1 + 0x286318) = param_1 + 0x286318;
  *(int *)(param_1 + 0x28631c) = param_1 + 0x286318;
  *(int *)(param_1 + 0x286320) = param_1 + 0x286320;
  *(int *)(param_1 + 0x286324) = param_1 + 0x286320;
  return 0;
}

