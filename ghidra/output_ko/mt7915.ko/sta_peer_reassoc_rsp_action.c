// module: mt7915.ko
// function: sta_peer_reassoc_rsp_action @ 0x7d860
// size: 800 bytes
//

void sta_peer_reassoc_rsp_action(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined1 uStack_6d;
  undefined1 uStack_6c;
  undefined1 local_6b;
  undefined2 local_6a;
  short local_68;
  undefined2 local_66;
  int local_64;
  undefined1 auStack_5d [6];
  undefined1 auStack_57 [11];
  undefined1 auStack_4c [40];
  
  uVar5 = *(undefined4 *)(param_2 + 0x92c);
  local_6b = 0xff;
  local_64 = 0;
  iVar1 = GetStaCfgByWdev(param_1,uVar5);
  if (iVar1 == 0) {
    printk(&_LC1,0x8f9);
    dump_stack();
    return;
  }
  os_alloc_mem(param_1,&local_64,0x310);
  if (local_64 == 0) {
    if (DebugLevel < 1) {
      return;
    }
    printk("%s():mem alloc failed!\n","sta_peer_reassoc_rsp_action");
    return;
  }
  __memzero(local_64,0x310);
  iVar2 = PeerAssocRspSanity(iVar1,param_2,*(undefined4 *)(param_2 + 0x908),auStack_5d,&local_6a,
                             &local_68,&local_66,&local_6b,auStack_4c,auStack_57,&uStack_6d,local_64
                            );
  if (iVar2 == 0) {
    if (2 < DebugLevel) {
      printk("REASSOC - %s() sanity check fail\n","sta_peer_reassoc_rsp_action");
    }
  }
  else {
    iVar2 = memcmp(auStack_5d,(void *)(iVar1 + 0x413a),6);
    if (iVar2 == 0) {
      if (2 < DebugLevel) {
        printk("REASSOC - receive REASSOC_RSP to me (status=%d)\n",local_68);
      }
      RTMPCancelTimer(iVar1 + 0x211ee8,&uStack_6c);
      iVar2 = local_64;
      if (local_68 == 0) {
        iVar1 = MacTableLookup2(param_1,iVar1 + 0x212428,uVar5);
        if (iVar1 != 0) {
          MacTableDeleteEntry(param_1,*(undefined2 *)(iVar1 + 0xe0),iVar1 + 0xec);
        }
        iVar1 = MacTableLookup2(param_1,auStack_5d,uVar5);
        if (iVar1 != 0) {
          MacTableDeleteEntry(param_1,*(undefined2 *)(iVar1 + 0xe0),iVar1 + 0xec);
        }
        iVar1 = MacTableInsertEntry(param_1,auStack_5d,uVar5,1,0,1);
        if (iVar1 == 0) {
          if (-1 < DebugLevel) {
            printk("%s():MacTableInsertEntry  failed!\n","sta_peer_reassoc_rsp_action");
          }
          goto LAB_0007d928;
        }
        uVar3 = dot11_max_sup_rate(iVar2 + 0x244);
        FUN_0007d3c8(param_1,auStack_5d,local_6a,local_66,auStack_4c,local_64,iVar1);
        StaUpdateMacTableEntry(param_1,iVar1,uVar3,local_64,local_6a);
        RTMPSetSupportMCS(param_1,0,iVar1,iVar2 + 0x244,*(byte *)(local_64 + 0x240) & 4,
                          local_64 + 0x2a4,local_64 + 0x274,*(byte *)(local_64 + 0x240) & 1);
        uVar4 = *(uint *)(local_64 + 0x240);
        if ((uVar4 & 0x20) != 0) {
          parse_he_bss_color_info(uVar5);
          uVar4 = *(uint *)(local_64 + 0x240);
        }
        if ((uVar4 & 0x100) != 0) {
          update_peer_he_muedca_ies(iVar1,local_64 + 0x240);
        }
      }
      assoc_fsm_state_transition(uVar5,0);
      cntl_auth_assoc_conf(uVar5,4,local_68);
    }
  }
LAB_0007d928:
  if (local_64 != 0) {
    os_free_mem();
  }
  return;
}

