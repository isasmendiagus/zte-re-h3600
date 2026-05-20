// module: mt7915.ko
// function: sta_mlme_deauth_req_action @ 0x753b8
// size: 716 bytes
//

void sta_mlme_deauth_req_action(int param_1,undefined4 *param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 local_40;
  undefined4 local_3c;
  undefined1 auStack_38 [28];
  
  local_40 = 0;
  local_3c = 0;
  iVar2 = GetStaCfgByWdev(param_1,param_2[0x24b]);
  iVar4 = param_2[0x24b];
  bVar1 = *(byte *)(iVar4 + 0xe);
  if (2 < DebugLevel) {
    printk(&_LC0,"sta_mlme_deauth_req_action");
  }
  if (iVar2 == 0) {
    printk(&_LC3,0xa1);
    dump_stack();
    if (iVar4 == 0) {
      printk(&_LC1,0xa2);
      dump_stack();
    }
  }
  else {
    if (iVar4 == 0) {
      printk(&_LC1,0xa2);
      dump_stack();
    }
    if (((*(char *)(param_1 + 0x286285) != '\x01') || (*(int *)(iVar4 + 0x14) != 2)) ||
       (iVar3 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0)),
       bVar1 < *(byte *)(iVar3 + 0x14a))) {
      iVar3 = os_alloc_mem(param_1,&local_40,0x900);
      if (iVar3 != 0) {
        if (2 < DebugLevel) {
          printk("AUTH - MlmeDeauthReqAction() allocate memory fail\n");
        }
        auth_fsm_state_transition(iVar4,0,"sta_mlme_deauth_req_action");
        cntl_auth_assoc_conf(param_2[0x24b],6,0x52);
        return;
      }
      if ((iVar4 != 0) && (*(int *)(iVar4 + 0x14) == 2)) {
        if (*(byte *)(iVar4 + 0x1a) < 0xf) {
          __ZTE_STA_Assoc_Process
                    (param_1,0x16,param_2,0xffffffff,*(undefined2 *)((int)param_2 + 6),0,0,
                     "sta_mlme_deauth_req_action",0xb9);
        }
        else {
          __ZTE_STA_Assoc_Process
                    (param_1,0x16,param_2,0xfffffffb,*(undefined2 *)((int)param_2 + 6),0,0,
                     "sta_mlme_deauth_req_action",0xbd);
        }
      }
      if (2 < DebugLevel) {
        printk("AUTH - Send DE-AUTH request (Reason=%d)...\n",*(undefined2 *)((int)param_2 + 6));
      }
      MgtMacHeaderInitExt(param_1,auStack_38,0xc,0,param_2,iVar4 + 0x1b,iVar2 + 0x413a);
      MakeOutgoingFrame(local_40,&local_3c,0x18,auStack_38,2,(int)param_2 + 6,0xffffffff);
      MiniportMMRequest(param_1,0,local_40,local_3c);
      os_free_mem(local_40);
      *(undefined2 *)(iVar2 + 0x2131f8) = *(undefined2 *)((int)param_2 + 6);
      *(undefined4 *)(iVar2 + 0x2131fa) = *param_2;
      *(undefined2 *)(iVar2 + 0x2131fe) = *(undefined2 *)(param_2 + 1);
      auth_fsm_state_transition(iVar4,0,"sta_mlme_deauth_req_action");
      cntl_auth_assoc_conf(param_2[0x24b],6,0);
    }
  }
  return;
}

