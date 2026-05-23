// module: mt7915.ko
// function: GASStateMachineInit @ 0x22cac4
// size: 380 bytes
//

void GASStateMachineInit(int param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  char *pcVar5;
  uint uVar6;
  
  if (2 < DebugLevel) {
    printk(&_LC1,"GASStateMachineInit");
  }
  uVar4 = 0;
  while( true ) {
    uVar1 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    uVar6 = uVar4 & 0xff;
    iVar3 = uVar6 * 0x5834;
    uVar4 = uVar4 + 1;
    pcVar5 = "RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + param_1 + iVar3 + 0x1c;
    if (uVar1 <= uVar6) break;
    __memzero(pcVar5,0x2c);
    iVar3 = param_1 + iVar3;
    pcVar2 = "RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + iVar3 + 0x24;
    pcVar2[0] = '\0';
    pcVar2[1] = '\0';
    pcVar2[2] = '\0';
    pcVar2[3] = '\0';
    *(char **)("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + iVar3 + 0x1c) = pcVar5;
    *(char **)("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + iVar3 + 0x20) = pcVar5;
  }
  StateMachineInit(param_2,param_3,7,10,Drop,6,0);
  StateMachineSetAction(param_2,2,3,SendGASIndication);
  StateMachineSetAction(param_2,1,1,SendGASRsp);
  StateMachineSetAction(param_2,1,2,SendGASRsp);
  StateMachineSetAction(param_2,1,6,SendGASCBRsp);
  StateMachineSetAction(param_2,4,6,SendGASCBRsp);
  StateMachineSetAction(param_2,4,7,SendGASCBRsp);
  return;
}

