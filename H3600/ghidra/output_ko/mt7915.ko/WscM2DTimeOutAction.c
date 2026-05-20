// module: mt7915.ko
// function: WscM2DTimeOutAction @ 0x1e407c
// size: 584 bytes
//

void WscM2DTimeOutAction(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined1 auStack_21 [5];
  
  if (param_2 == 0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s: pWscControl is NULL!!\n","WscM2DTimeOutAction");
    return;
  }
  iVar3 = *(int *)(param_2 + 0x29e8);
  if (iVar3 == 0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s: pAd is NULL!!\n","WscM2DTimeOutAction");
    return;
  }
  if (*(char *)(iVar3 + 0x286285) == '\x01') {
    iVar2 = MacTableLookup(iVar3,param_2 + 0x1c55);
    if (2 < DebugLevel) {
      printk("UPnP StateMachine TimeOut(State=%d!)\n",*(undefined4 *)(param_2 + 0x10));
    }
    if ((iVar2 == 0) || (*(int *)(param_2 + 0x2790) != 0)) {
LAB_001e412c:
      if (2 < DebugLevel) {
        printk("%s():pEntry maybe gone or already received M2 Packet!\n","WscM2DTimeOutAction");
      }
      goto LAB_001e40d8;
    }
    if (*(int *)(param_2 + 0x2c48) == 0) {
      RTMPCancelTimer(param_2 + 0x27cc,auStack_21);
      iVar1 = DebugLevel;
      *(undefined1 *)(param_2 + 0x27c8) = 0;
      if (2 < iVar1) {
        printk("%s(): send EAP-Fail to wireless Station!\n","WscM2DTimeOutAction");
      }
      WscSendEapFail(iVar3,param_2,1);
      if (iVar2 != 0) {
        *(undefined1 *)(iVar2 + 0xd25) = 0;
      }
      goto LAB_001e4234;
    }
  }
  else {
    if (*(char *)(iVar3 + 0x286285) == '\0') {
      if (DebugLevel < 3) {
        if (*(int *)(param_2 + 0x2790) != 0) goto LAB_001e40d8;
      }
      else {
        iVar3 = 2;
LAB_001e424c:
        printk("UPnP StateMachine TimeOut(State=%d!)\n",*(undefined4 *)(param_2 + 0x10));
        if ((iVar3 == 0) || (*(int *)(param_2 + 0x2790) != 0 && iVar3 == 2)) goto LAB_001e412c;
      }
    }
    else if (2 < DebugLevel) {
      iVar3 = 0xff;
      goto LAB_001e424c;
    }
    if (*(int *)(param_2 + 0x2c48) == 0) {
      RTMPCancelTimer(param_2 + 0x27cc,auStack_21);
      *(undefined1 *)(param_2 + 0x27c8) = 0;
LAB_001e4234:
      *(undefined1 *)(param_2 + 0x1c52) = 0;
      *(undefined4 *)(param_2 + 0x10) = 0;
      goto LAB_001e40d8;
    }
  }
  if (2 < DebugLevel) {
    printk("%s(): waiting for M2DACK balance, extend the time!\n","WscM2DTimeOutAction");
  }
  RTMPModTimer(param_2 + 0x2c10,5000);
LAB_001e40d8:
  *(undefined1 *)(param_2 + 0x2c44) = 0;
  *(undefined4 *)(param_2 + 0x2c48) = 0;
  *(undefined4 *)(param_2 + 0x2790) = 0;
  return;
}

