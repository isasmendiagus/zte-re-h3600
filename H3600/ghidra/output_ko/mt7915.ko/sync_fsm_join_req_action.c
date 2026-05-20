// module: mt7915.ko
// function: sync_fsm_join_req_action @ 0x10b2ec
// size: 980 bytes
//

void sync_fsm_join_req_action(int param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  undefined1 *puVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined1 auStack_29 [5];
  
  iVar4 = param_2[0x24b];
  iVar1 = GetStaCfgByWdev(param_1,iVar4);
  iVar2 = GetAssociatedAPByWdev(param_1,iVar4);
  if (2 < DebugLevel) {
    printk("%s - (Ssid %s)\n","sync_fsm_join_req_action",(int)param_2 + 0xb);
  }
  iVar5 = iVar1 + 0x4118;
  RTMPCancelTimer(iVar1 + 0x211e4c,auStack_29);
  FUN_001082fc(iVar4);
  *(undefined4 *)(iVar1 + 0x21239c) = 0xffffff80;
  *(undefined1 *)(iVar1 + 0x2123e9) = 0;
  *(undefined1 *)(iVar1 + 0x4118) = *(undefined1 *)(iVar1 + 0x4060);
  if (iVar2 != 0) {
    if (0 < DebugLevel) {
      printk("***** STALE  Peer AP entry present--Delete it ****\n");
    }
    MacTableDeleteEntry(param_1,*(undefined2 *)(iVar2 + 0xe0),iVar2 + 0xec);
  }
  iVar2 = *param_2;
  if (iVar2 == -1) {
    *(undefined1 *)(iVar1 + 0x4165) = *(undefined1 *)(iVar4 + 0x1a);
    *(undefined1 *)(iVar1 + 0x4176) = *(undefined1 *)(iVar4 + 0xade);
    memmove((void *)(iVar1 + 0x4177),(void *)(iVar4 + 0xadf),(uint)*(byte *)(iVar4 + 0xade));
    iVar5 = 0;
    *(undefined1 *)(iVar1 + 0x4183) = *(undefined1 *)(iVar4 + 0xaeb);
    memmove((void *)(iVar1 + 0x4184),(void *)(iVar4 + 0xaec),(uint)*(byte *)(iVar4 + 0xaeb));
    __memzero(iVar1 + 0x413a,6);
    *(undefined4 *)(iVar1 + 0x413a) = *(undefined4 *)(iVar1 + 0x213303);
    *(undefined2 *)(iVar1 + 0x413e) = *(undefined2 *)(iVar1 + 0x213307);
    __memzero((void *)(iVar1 + 0x4119),0x20);
    memcpy((void *)(iVar1 + 0x4119),(void *)((int)param_2 + 0xb),(uint)*(byte *)((int)param_2 + 10))
    ;
    *(undefined1 *)(iVar1 + 0x4139) = *(undefined1 *)((int)param_2 + 10);
LAB_0010b530:
    if ((((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7915) &&
        (*(int *)(iVar4 + 0x14) == 2)) && (SrDisSrBfrConnected(param_1,iVar4,0), -1 < DebugLevel)) {
      printk("%s - SrDisSrBfrConnected - FALSE\n","sync_fsm_join_req_action");
    }
    iVar2 = scan_active_probe_disallowed(param_1,*(undefined1 *)(iVar1 + 0x4165));
    if ((((iVar2 != 1) || (*param_2 == -1)) || (*(char *)(iVar5 + 0x85) != '\0')) &&
       (iVar2 = FUN_0010aec4(param_1,iVar4), iVar2 != 1)) goto LAB_0010b578;
  }
  else {
    iVar7 = iVar2 * 0xaf4;
    iVar6 = iVar1 + 0x4000 + iVar7;
    *(undefined4 *)(iVar1 + 0x413a) = *(undefined4 *)(iVar5 + iVar7 + 0x11e);
    *(undefined2 *)(iVar1 + 0x413e) = *(undefined2 *)(iVar5 + iVar7 + 0x122);
    if (*(char *)(iVar6 + 0x2b5) == '\0') {
      RTMPZeroMemory((void *)(iVar1 + 0x4119),0x20);
      memmove((void *)(iVar1 + 0x4119),(void *)(iVar5 + iVar7 + 0x1ad),
              (uint)*(byte *)(iVar6 + 0x2c4));
      *(undefined1 *)(iVar1 + 0x4139) = *(undefined1 *)(iVar6 + 0x2c4);
    }
    iVar6 = iVar1 + 0x4000 + iVar2 * 0xaf4;
    *(undefined1 *)(iVar1 + 0x4118) = *(undefined1 *)(iVar6 + 0x244);
    *(undefined1 *)(iVar1 + 0x4165) = *(undefined1 *)(iVar6 + 0x23c);
    *(undefined1 *)(iVar1 + 0x4167) = *(undefined1 *)(iVar6 + 0x23d);
    HcCrossChannelCheck(param_1,iVar4);
    *(undefined1 *)(iVar4 + 0x1a) = *(undefined1 *)(iVar1 + 0x4165);
    iVar6 = wlan_operate_scan(iVar4,*(undefined1 *)(iVar1 + 0x4165));
    if (iVar6 == 0) {
      iVar5 = iVar5 + iVar2 * 0xaf4 + 0x118;
      goto LAB_0010b530;
    }
  }
  RTMPSetTimer(iVar1 + 0x211e4c,2000);
  puVar3 = (undefined1 *)get_scan_ctrl_by_wdev(*(undefined4 *)(iVar4 + 8),iVar4);
  iVar2 = *(int *)(puVar3 + 0x90);
  *(undefined4 *)(puVar3 + 0x90) = 2;
  if (*(undefined4 **)(puVar3 + 0xaf5d0) == (undefined4 *)0x0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("ScanCtrl->ScanReqwdev is NULL\n");
  }
  else {
    if (DebugLevel < 2) {
      return;
    }
    printk("SYNC[%s, Band:%d, TYPE:%d]: [%s] ==============================================> [%s]\n"
           ,**(undefined4 **)(puVar3 + 0xaf5d0),puVar3[0x1c6],*puVar3,
           *(undefined4 *)(SYNC_FSM_STATE_STR + iVar2 * 4),SYNC_FSM_STATE_STR._8_4_);
  }
LAB_0010b578:
  if (1 < DebugLevel) {
    printk("ApCli SYNC - Start Probe the SSID %s on channel =%d\n",iVar1 + 0x4119,
           *(undefined1 *)(iVar1 + 0x4165));
  }
  return;
}

