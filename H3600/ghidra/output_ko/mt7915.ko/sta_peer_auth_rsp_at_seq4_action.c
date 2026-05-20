// module: mt7915.ko
// function: sta_peer_auth_rsp_at_seq4_action @ 0x75a14
// size: 592 bytes
//

void sta_peer_auth_rsp_at_seq4_action(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined1 uStack_33;
  undefined1 auStack_32 [2];
  short local_30;
  short local_2e;
  int local_2c;
  undefined4 local_26;
  undefined2 local_22;
  
  local_2c = 0;
  iVar2 = GetStaCfgByWdev(param_1,*(undefined4 *)(param_2 + 0x92c));
  iVar5 = *(int *)(param_2 + 0x92c);
  bVar1 = *(byte *)(iVar5 + 0xe);
  if (2 < DebugLevel) {
    printk(&_LC0,"sta_peer_auth_rsp_at_seq4_action");
  }
  if (iVar2 == 0) {
    printk(&_LC3,0x29e);
    dump_stack();
    if (iVar5 == 0) {
      printk(&_LC1,0x29f);
      dump_stack();
    }
  }
  else {
    if (iVar5 == 0) {
      printk(&_LC1,0x29f);
      dump_stack();
    }
    iVar4 = *(int *)(iVar5 + 0x14);
    if ((*(char *)(param_1 + 0x286285) == '\x01') && (iVar4 == 2)) {
      iVar4 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
      if (*(byte *)(iVar4 + 0x14a) <= bVar1) {
        return;
      }
      iVar4 = *(int *)(iVar5 + 0x14);
    }
    if (iVar4 == 0x100) {
      iVar4 = *(int *)(iVar5 + 4) + 0x3c;
    }
    else {
      iVar4 = iVar2 + 0x211e80;
    }
    os_alloc_mem(0,&local_2c,0x80);
    if (local_2c == 0) {
      if (-1 < DebugLevel) {
        printk("%s: ChlgText Allocate memory fail!!!\n","sta_peer_auth_rsp_at_seq4_action");
      }
    }
    else {
      iVar3 = PeerAuthSanity(param_1,param_2,*(undefined4 *)(param_2 + 0x908),&local_26,auStack_32,
                             &local_30,&local_2e,local_2c);
      if (iVar3 == 0) {
        if (2 < DebugLevel) {
          printk("AUTH - PeerAuthRspAtSeq4Action() sanity check fail\n");
        }
      }
      else {
        iVar3 = memcmp((void *)(iVar2 + 0x413a),&local_26,6);
        if ((iVar3 == 0) && (local_30 == 4)) {
          if (2 < DebugLevel) {
            printk("AUTH - Receive AUTH_RSP seq#4 to me\n");
          }
          RTMPCancelTimer(iVar4,&uStack_33);
          if (local_2e != 0) {
            *(short *)(iVar2 + 0x213200) = local_2e;
            *(undefined4 *)(iVar2 + 0x213202) = local_26;
            *(undefined2 *)(iVar2 + 0x213206) = local_22;
          }
          auth_fsm_state_transition(iVar5,0,"sta_peer_auth_rsp_at_seq4_action");
          cntl_auth_assoc_conf(*(undefined4 *)(param_2 + 0x92c),2,local_2e);
        }
      }
      if (local_2c != 0) {
        os_free_mem();
      }
    }
  }
  return;
}

