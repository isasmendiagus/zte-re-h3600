// module: mt7915.ko
// function: WscEAPOLStartAction @ 0x1ee7f8
// size: 1036 bytes
//

void WscEAPOLStartAction(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  void *__s1;
  int iVar5;
  int local_2c [2];
  
  if (2 < DebugLevel) {
    printk("-----> WscEAPOLStartAction\n");
  }
  iVar2 = *(int *)(param_2 + 0x92c);
  if (iVar2 == 0) {
    printk(&_LC68,0x2c5);
    dump_stack();
  }
  (**(code **)(*(int *)(iVar2 + 0x904) + 0xb8))(param_1,param_2 + 10,iVar2,local_2c);
  if (local_2c[0] == 0) {
    if (DebugLevel < 3) {
      return;
    }
    printk("pEntry is NULL.\n");
    goto joined_r0x001eea90;
  }
  if (*(int *)(iVar2 + 0x14) == 1 || *(int *)(iVar2 + 0x14) == 0x20) {
    iVar1 = param_1;
    if (*(byte *)(local_2c[0] + 0xe4) < 2) {
      iVar1 = param_1 + (uint)*(byte *)(local_2c[0] + 0xe4) * 0x2137b0;
    }
    puVar4 = (undefined4 *)(&DAT_0036ee3c + iVar1);
    if (puVar4 == (undefined4 *)0x0) {
      iVar3 = 0;
    }
    else {
      if (0 < DebugLevel) {
        printk("CON_WPS: Stop the ApCli WPS, state [%d]\n",*(undefined4 *)(&DAT_0036ee4c + iVar1));
      }
      iVar3 = 0;
      if ((*(int *)(s_OTH__d__d_N_A__0037170c + iVar1 + 0x14) != 0) &&
         (iVar3 = 0, *(int *)(&DAT_0036ee4c + iVar1) != 0)) {
        if (0 < DebugLevel) {
          printk("<----- WscConWpsStop\n");
        }
        _WscStop(param_1,1,puVar4,0);
        iVar3 = 0;
        *puVar4 = 0;
      }
    }
  }
  else {
    iVar3 = 2;
  }
  _raw_spin_lock_bh(iVar2 + 0x3ee4);
  WscInsertPeerEntryByMAC(iVar2 + 0x3ee8,local_2c[0] + 0xec);
  _raw_spin_unlock_bh(iVar2 + 0x3ee4);
  WscMaintainPeerList(param_1,iVar2 + 0x12e4);
  if (*(char *)(iVar2 + 0x3ef0) != '\0') {
    __s1 = (void *)(local_2c[0] + 0xec);
    iVar1 = memcmp(__s1,(void *)(*(int *)(iVar2 + 0x3ee8) + 8),6);
    if (iVar1 != 0) {
      if (2 < DebugLevel) {
        printk("This is not first WSC peer, ignore this EAPOL_Start!\n");
        __s1 = (void *)(local_2c[0] + 0xec);
      }
      hex_dump("pEntry->Addr",__s1,6);
      if (iVar3 == 0) {
        WscApShowPeerList(param_1,0);
      }
      else if (iVar3 == 2) {
        WscStaShowPeerList(param_1,0);
      }
      goto joined_r0x001eea90;
    }
  }
  if (2 < DebugLevel) {
    printk("WscState = %d\n",*(undefined4 *)(iVar2 + 0x12f4));
  }
  iVar5 = local_2c[0];
  iVar1 = DebugLevel;
  if ((*(byte *)(local_2c[0] + 0xd25) != 0) && (9 < *(int *)(iVar2 + 0x12f4))) {
    if (DebugLevel < 3) {
      return;
    }
    printk("Ignore EAPOL-Start.\n");
    goto joined_r0x001eea90;
  }
  *(byte *)(local_2c[0] + 0xd25) = *(byte *)(local_2c[0] + 0xd25) | 1;
  if (iVar1 < 3) {
    *(undefined1 *)(iVar2 + 0x2f36) = 1;
    memmove((void *)(iVar2 + 0x2f39),(void *)(local_2c[0] + 0xec),6);
    if (*(char *)(iVar5 + 0xd24) == '\0') {
LAB_001ee9f4:
      *(undefined1 *)(iVar5 + 0xd24) = 1;
      goto LAB_001ee9fc;
    }
  }
  else {
    printk("WscEAPOLStartAction - receive EAPOL-Start from %02x:%02x:%02x:%02x:%02x:%02x\n",
           *(undefined1 *)(local_2c[0] + 0xec),*(undefined1 *)(local_2c[0] + 0xed),
           *(undefined1 *)(local_2c[0] + 0xee),*(undefined1 *)(local_2c[0] + 0xef),
           *(undefined1 *)(local_2c[0] + 0xf0),*(undefined1 *)(local_2c[0] + 0xf1));
    iVar5 = local_2c[0];
    *(undefined1 *)(iVar2 + 0x2f36) = 1;
    iVar1 = DebugLevel;
    memmove((void *)(iVar2 + 0x2f39),(void *)(local_2c[0] + 0xec),6);
    if (*(char *)(iVar5 + 0xd24) == '\0') goto LAB_001ee9f4;
LAB_001ee9fc:
    if (2 < iVar1) {
      printk("WscEAPOLStartAction(ra%d) - send EAP-Req(Id) to %02x:%02x:%02x:%02x:%02x:%02x\n",
             *(undefined1 *)(iVar5 + 0xe4),*(undefined1 *)(iVar5 + 0xec),
             *(undefined1 *)(iVar5 + 0xed),*(undefined1 *)(iVar5 + 0xee),
             *(undefined1 *)(iVar5 + 0xef),*(undefined1 *)(iVar5 + 0xf0),
             *(undefined1 *)(iVar5 + 0xf1));
      iVar5 = local_2c[0];
    }
  }
  WscSendEapReqId(param_1,iVar5,iVar3);
  if (*(char *)(iVar2 + 0x3aac) == '\0') {
    *(undefined1 *)(iVar2 + 0x3aac) = 1;
    RTMPSetTimer(iVar2 + 0x3ab0,5000);
  }
joined_r0x001eea90:
  if (2 < DebugLevel) {
    printk("<----- WscEAPOLStartAction\n");
  }
  return;
}

