// module: mt7915.ko
// function: MlmeInit @ 0x129720
// size: 1148 bytes
//

int MlmeInit(int param_1)

{
  int iVar1;
  int iVar2;
  undefined *puVar3;
  
  if (2 < DebugLevel) {
    printk("--> MLME Initialize\n");
  }
  *(undefined4 *)(param_1 + 0x796104) = 0;
  *(undefined4 *)(param_1 + 0x7960f8) = 0;
  *(undefined4 *)(param_1 + 0x7960fc) = 0;
  *(undefined4 *)(param_1 + 0x796100) = 0;
  iVar1 = param_1 + 0x796108;
  do {
    *(undefined1 *)(iVar1 + 0x922) = 0;
    *(undefined4 *)(iVar1 + 0x908) = 0;
    iVar2 = iVar1 + 0x930;
    __memzero(iVar1,0x900);
    iVar1 = iVar2;
  } while (iVar2 != param_1 + 0x829108);
  *(undefined1 *)(param_1 + 0x7960f0) = 0;
  *(undefined4 *)(param_1 + 0x7960f4) = 0;
  sync_fsm_init(param_1,0,param_1 + 0x8292f4,param_1 + 0x82930c);
  sync_fsm_init(param_1,1,param_1 + 0x8d88cc,param_1 + 0x8d88e4);
  if ((*(byte *)(param_1 + 0x286294) & 1) != 0) {
    BssTableInit(param_1 + 0x829438);
    BssTableInit(param_1 + 0x8d8a10);
    puVar3 = &DAT_0036db58 + param_1;
    do {
      iVar1 = GetStaCfgByWdev(param_1,puVar3);
      if (iVar1 != 0) {
        *(undefined4 *)(puVar3 + 0xca8) = 0;
        *(undefined4 *)(puVar3 + 0xe30) = 0;
        *(undefined4 *)(puVar3 + 0xbdc) = 0;
        sta_auth_init(puVar3);
        sta_assoc_init(puVar3);
      }
      puVar3 = puVar3 + 0x2137b0;
    } while (puVar3 != (undefined *)(param_1 + 0x794ab8));
  }
  if (*(char *)(param_1 + 0x286285) == '\0') {
    RTMPInitTimer(param_1,param_1 + 0x580c94,rtmp_timer_StaQuickResponeForRateUpExec,param_1,0);
    (&DAT_00580cc8)[param_1] = 0;
  }
  WscStateMachineInit(param_1,param_1 + 0x795bb8,param_1 + 0x795bd0);
  WpaStateMachineInit(param_1,param_1 + 0x796094,param_1 + 0x7960ac);
  GASStateMachineInit(param_1,param_1 + 0x795bdc,param_1 + 0x795bf4);
  RRMBcnReqStateMachineInit(param_1,param_1 + 0x795d0c,param_1 + 0x795d24);
  NRStateMachineInit(param_1,param_1 + 0x795d48,param_1 + 0x795d60);
  WNMCtrlInit(param_1);
  BTMStateMachineInit(param_1,param_1 + 0x795d78,param_1 + 0x795d90);
  ActionStateMachineInit(param_1,param_1 + 0x795ba0,param_1 + 0x795b20);
  GetStaTxRateStateMachineInit(param_1,param_1 + 0x7960c8,param_1 + 0x7960e0);
  RTMPInitTimer(param_1,param_1 + 0x82910c,rtmp_timer_MlmePeriodicExecTimer,param_1,1);
  RTMPSetTimer(param_1 + 0x82910c,100);
  RTMPInitTimer(param_1,param_1 + 0x829224,rtmp_timer_AsicRxAntEvalTimeout,param_1,0);
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    RTMPInitTimer(param_1,param_1 + 0x829140,rtmp_timer_APSDPeriodicExec,param_1,1);
    RTMPSetTimer(param_1 + 0x829140,0x32);
    RTMPInitTimer(param_1,param_1 + 0x36b8d4,rtmp_timer_APQuickResponeForRateUpExec,param_1,0);
    (&DAT_0036b908)[param_1] = 0;
  }
  iVar1 = param_1 + 0x286298;
  RtmpOSTaskInit(iVar1,"RtmpMlmeTask",param_1,param_1 + 0xa78454,param_1 + 0xa78478);
  iVar1 = RtmpOSTaskAttach(iVar1,MlmeThread,iVar1);
  if ((iVar1 == 1) && (-1 < DebugLevel)) {
    printk("%s: unable to start MlmeThread\n",*(undefined4 *)(param_1 + 4));
  }
  *(int *)(param_1 + 0x829268) = param_1 + 0x795b20;
  *(code **)(param_1 + 0x82925c) = mlme_for_wsys_notify_handle;
  *(undefined4 *)(param_1 + 0x829264) = 2;
  register_wsys_notifier(param_1 + 0xa7bed4,param_1 + 0x82925c);
  if (2 < DebugLevel) {
    printk("<-- MLME Initialize\n");
  }
  *(uint *)(param_1 + 0xa39f84) = *(uint *)(param_1 + 0xa39f84) | 4;
  return iVar1;
}

