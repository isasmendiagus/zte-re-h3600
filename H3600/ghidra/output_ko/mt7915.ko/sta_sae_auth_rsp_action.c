// module: mt7915.ko
// function: sta_sae_auth_rsp_action @ 0x763f0
// size: 644 bytes
//

void sta_sae_auth_rsp_action(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  void *local_1c;
  
  iVar2 = GetStaCfgByWdev(param_1,*(undefined4 *)(param_2 + 0x92c));
  iVar3 = *(int *)(param_2 + 0x92c);
  bVar1 = *(byte *)(iVar3 + 0xe);
  if (iVar2 == 0) {
    printk(&_LC3,0x31e);
    dump_stack();
    if (iVar3 == 0) {
      printk(&_LC1,799);
      dump_stack();
    }
    return;
  }
  if (iVar3 == 0) {
    printk(&_LC1,799);
    dump_stack();
  }
  if (((*(char *)(param_1 + 0x286285) == '\x01') && (*(int *)(iVar3 + 0x14) == 2)) &&
     (iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0)),
     *(byte *)(iVar2 + 0x14a) <= bVar1)) {
    return;
  }
  iVar2 = sae_handle_auth(param_1,"pci_sw_int_handler" + param_1,param_2,
                          *(undefined4 *)(param_2 + 0x908),iVar3 + 0x179,iVar3 + 0x814,
                          *(undefined1 *)(iVar3 + 0x810),*(undefined2 *)(param_2 + 0x1a),
                          *(undefined2 *)(param_2 + 0x1c),&local_1c);
  if (iVar2 == 0) {
    auth_fsm_state_transition(iVar3,0,"sta_sae_auth_rsp_action");
    cntl_auth_assoc_conf(iVar3,2,1);
    return;
  }
  if (local_1c == (void *)0x0) {
    if (DebugLevel < 3) {
      return;
    }
    printk("**************Unhandled ************\n");
    return;
  }
  hex_dump_with_lvl(&_LC20,local_1c,0x20,3);
  if (*(int *)(iVar3 + 0x14) == 0x100) {
    iVar2 = *(int *)(iVar3 + 4);
    if (iVar2 != 0) {
      if (2 < DebugLevel) {
        printk("%s Move pmk to rept_PMK\n","sta_sae_auth_rsp_action");
      }
      memmove((void *)(iVar2 + 0x42b1),local_1c,0x20);
      uVar4 = 0;
      goto LAB_0007650c;
    }
  }
  else {
    iVar2 = MacTableLookup(param_1,param_2 + 10);
    if (iVar2 != 0) {
      memmove((void *)(iVar2 + 0x30a),local_1c,0x20);
      if (DebugLevel < 1) {
        uVar4 = 0;
      }
      else {
        uVar4 = 0;
        printk("%s(): Security AKM = 0x%x, PairwiseCipher = 0x%x, GroupCipher = 0x%x\n",
               "sta_sae_auth_rsp_action",*(undefined4 *)(iVar2 + 0x17c),
               *(undefined4 *)(iVar2 + 0x2c4),*(undefined4 *)(iVar2 + 0x3a4));
      }
      goto LAB_0007650c;
    }
  }
  uVar4 = 1;
LAB_0007650c:
  auth_fsm_state_transition(iVar3,0,"sta_sae_auth_rsp_action");
  cntl_auth_assoc_conf(iVar3,2,uVar4);
  return;
}

