// module: mt7915.ko
// function: sta_mlme_disassoc_req_action @ 0x7d108
// size: 700 bytes
//

void sta_mlme_disassoc_req_action(undefined4 param_1,undefined4 *param_2)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined1 uStack_41;
  byte *local_40;
  undefined4 local_3c;
  undefined1 auStack_38 [24];
  
  local_40 = (byte *)0x0;
  local_3c = 0;
  iVar2 = GetStaCfgByWdev(param_1,param_2[0x24b]);
  iVar4 = param_2[0x24b];
  if (iVar2 != 0) {
    if ((*(int *)(iVar4 + 0x14) == 0x100) && (*(int *)(iVar4 + 4) == 0)) {
      printk(&_LC8,0x6fa);
      dump_stack();
    }
    iVar3 = os_alloc_mem(param_1,&local_40,0x900);
    if (iVar3 == 0) {
      RTMPCancelTimer(BN_mod_sqr + iVar2,&uStack_41);
      if ((iVar4 != 0) && (*(int *)(iVar4 + 0x14) == 2)) {
        if (*(byte *)(iVar4 + 0x1a) < 0xf) {
          __ZTE_STA_Assoc_Process
                    (param_1,0x18,param_2,0xffffffff,*(undefined2 *)((int)param_2 + 6),0,0,
                     "sta_mlme_disassoc_req_action",0x735);
        }
        else {
          __ZTE_STA_Assoc_Process
                    (param_1,0x18,param_2,0xfffffffb,*(undefined2 *)((int)param_2 + 6),0,0,
                     "sta_mlme_disassoc_req_action",0x739);
        }
      }
      if (2 < DebugLevel) {
        printk("ASSOC - Send DISASSOC request[BSSID::%02x:%02x:%02x:%02x:%02x:%02x (Reason=%d)\n",
               *(undefined1 *)param_2,*(undefined1 *)((int)param_2 + 1),
               *(undefined1 *)((int)param_2 + 2),*(undefined1 *)((int)param_2 + 3),
               *(undefined1 *)(param_2 + 1),*(undefined1 *)((int)param_2 + 5),
               *(undefined2 *)((int)param_2 + 6));
      }
      MgtMacHeaderInitExt(param_1,auStack_38,10,0,param_2,iVar4 + 0x1b,param_2);
      MakeOutgoingFrame(local_40,&local_3c,0x18,auStack_38,2,(undefined1 *)((int)param_2 + 6),
                        0xffffffff);
      MiniportMMRequest(param_1,0,local_40,local_3c);
      *local_40 = *local_40 & 0xf | 0xc0;
      MiniportMMRequest(param_1,0,local_40,local_3c);
      os_free_mem(local_40);
      *(undefined2 *)(iVar2 + 0x2131f0) = 8;
      *(undefined4 *)(iVar2 + 0x2131f2) = *param_2;
      uVar1 = *(undefined2 *)(param_2 + 1);
      *(undefined2 *)(iVar2 + 0x2131f6) = uVar1;
      if (*(int *)(iVar4 + 0x14) != 0x100) {
        RTMPSetTimer(BN_mod_sqr + iVar2,500,uVar1);
        assoc_fsm_state_transition(iVar4,3);
      }
    }
    else if (2 < DebugLevel) {
      printk("ASSOC - MlmeDisassocReqAction() allocate memory failed\n");
    }
    cntl_auth_assoc_conf(iVar4,7);
    return;
  }
  printk(&_LC1,0x6f2);
  dump_stack();
  return;
}

