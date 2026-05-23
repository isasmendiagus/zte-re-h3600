// module: mt7915.ko
// function: sta_peer_deauth_action @ 0x7568c
// size: 896 bytes
//

void sta_peer_deauth_action(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  undefined2 local_42;
  undefined1 auStack_40 [6];
  undefined1 auStack_3a [6];
  undefined1 auStack_34 [6];
  undefined4 local_2e;
  undefined2 local_2a;
  
  iVar2 = GetStaCfgByWdev(param_1,*(undefined4 *)(param_2 + 0x92c));
  iVar5 = *(int *)(param_2 + 0x92c);
  bVar1 = *(byte *)(iVar5 + 0xe);
  if (2 < DebugLevel) {
    printk(&_LC0,"sta_peer_deauth_action");
  }
  if (iVar2 == 0) {
    printk(&_LC3,0x151);
    dump_stack();
    if (iVar5 == 0) {
      printk(&_LC1,0x152);
      dump_stack();
    }
  }
  else {
    if (iVar5 == 0) {
      printk(&_LC1,0x152);
      dump_stack();
    }
    if (*(int *)(iVar2 + 0x12f4) == 0x1a) {
      uVar4 = RTMPMsecsToJiffies(200);
      wait_for_completion_timeout(iVar2 + 0x3f44,uVar4);
    }
    if (((*(char *)(param_1 + 0x286285) != '\x01') || (*(int *)(iVar5 + 0x14) != 2)) ||
       (iVar3 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0)),
       bVar1 < *(byte *)(iVar3 + 0x14a))) {
      iVar3 = PeerDeauthSanity(param_1,param_2,*(undefined4 *)(param_2 + 0x908),auStack_40,
                               auStack_3a,auStack_34,&local_42);
      if (iVar3 == 0) {
        if (2 < DebugLevel) {
          printk("AUTH_RSP - PeerDeauthAction() sanity check fail\n");
        }
      }
      else {
        auth_fsm_state_transition(iVar5,0,"sta_peer_deauth_action");
        if (((*(uint *)(iVar2 + 0x212464) & 1) != 0) &&
           (iVar3 = memcmp((void *)(iVar2 + 0x212428),auStack_3a,6), iVar3 == 0)) {
          if (2 < DebugLevel) {
            printk("AUTH_RSP - receive DE-AUTH from our AP (Reason=%d)\n",local_42);
          }
          if ((iVar5 != 0) && (*(int *)(iVar5 + 0x14) == 2)) {
            if (*(byte *)(iVar5 + 0x1a) < 0xf) {
              __ZTE_STA_Assoc_Process
                        (param_1,0x11,auStack_3a,0xffffffff,local_42,0,0,"sta_peer_deauth_action",
                         0x171);
            }
            else {
              __ZTE_STA_Assoc_Process
                        (param_1,0x11,auStack_3a,0xfffffffb,local_42,0,0,"sta_peer_deauth_action",
                         0x175);
            }
          }
          if (*(int *)(*(int *)(param_2 + 0x92c) + 0x14) == 2) {
            sta_reset_owe_parameters(param_1,bVar1);
          }
          if (*(int *)(iVar5 + 0x14) == 0x100) {
            local_2e = *(undefined4 *)(*(int *)(iVar5 + 4) + 0x83);
            local_2a = *(undefined2 *)(*(int *)(iVar5 + 4) + 0x87);
          }
          else {
            local_2e = *(undefined4 *)(iVar2 + 0x1b);
            local_2a = *(undefined2 *)(iVar2 + 0x1f);
          }
          iVar2 = sta_search_pmkid_cache(param_1,auStack_3a,bVar1,iVar5);
          if (iVar2 != -1) {
            if (0 < DebugLevel) {
              printk("%s: Delete pmkid on de-auth\n","sta_peer_deauth_action");
            }
            sta_delete_pmkid_cache(param_1,auStack_3a,bVar1,iVar5);
          }
          iVar2 = search_sae_instance("pci_sw_int_handler" + param_1,&local_2e,auStack_3a);
          if (iVar2 != 0) {
            if (0 < DebugLevel) {
              printk("%s: Delete Existing sae instance on de-auth\n","sta_peer_deauth_action");
            }
            delete_sae_instance(iVar2);
          }
          cntl_fsm_state_transition(iVar5,4,"sta_peer_deauth_action");
          iVar2 = cntl_auth_assoc_conf(iVar5,6,local_42);
          if (iVar2 == 0) {
            LinkDown(param_1,2,iVar5,param_2);
          }
        }
      }
    }
  }
  return;
}

