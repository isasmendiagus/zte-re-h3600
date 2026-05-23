// module: mt7915.ko
// function: BTMReqTimeout @ 0x223f50
// size: 384 bytes
//

void BTMReqTimeout(int param_1,void *param_2)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  char *pcVar5;
  undefined1 uStack_25;
  byte local_24;
  undefined1 auStack_23 [11];
  
  if (0 < DebugLevel) {
    printk(&_LC6,"BTMReqTimeout");
  }
  os_move_mem(&local_24,param_2,0xc);
  pcVar5 = "RT_OID_WSC_SET_CONF_MODE:: WscConfMode = %d\n" +
           param_1 + (uint)local_24 * 0x5834 + 0x20;
  down_interruptible(pcVar5);
  param_1 = param_1 + (uint)local_24 * 0x5834;
  piVar3 = (int *)**(int **)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + param_1 + 0x28);
  piVar2 = *(int **)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + param_1 + 0x28);
  while ((piVar1 = piVar3,
         piVar2 != (int *)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + param_1 + 0x28) &&
         (iVar4 = memcmp((char *)((int)piVar2 + 0xd),auStack_23,6), iVar4 != 0))) {
    piVar3 = (int *)*piVar1;
    piVar2 = piVar1;
  }
  up(pcVar5);
  if ((char)piVar2[0xd] == '\0') {
    if (0 < DebugLevel) {
      printk("%s receive btm req timeout the uplayer does not send btm req in time\n",
             "BTMReqTimeout");
    }
    down_interruptible(pcVar5);
    if (*piVar2 != 0) {
      *(int *)(*piVar2 + 4) = piVar2[1];
    }
    if ((int *)piVar2[1] != (int *)0x0) {
      *(int *)piVar2[1] = *piVar2;
    }
    *piVar2 = 0;
    piVar2[1] = 0;
    up(pcVar5);
    RTMPReleaseTimer(piVar2 + 0x13,&uStack_25);
    RTMPReleaseTimer(piVar2 + 6,&uStack_25);
    os_free_mem(piVar2);
    return;
  }
  if (0 < DebugLevel) {
    printk("%s receive btm req and set btm rsp timer no need to delete BTMPeerEntry\n",
           "BTMReqTimeout");
  }
  return;
}

