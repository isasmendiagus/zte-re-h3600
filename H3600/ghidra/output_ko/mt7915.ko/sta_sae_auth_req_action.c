// module: mt7915.ko
// function: sta_sae_auth_req_action @ 0x76248
// size: 420 bytes
//

void sta_sae_auth_req_action(int param_1,undefined4 *param_2)

{
  byte bVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar3 = GetStaCfgByWdev(param_1,param_2[0x24b]);
  iVar5 = param_2[0x24b];
  bVar1 = *(byte *)(iVar5 + 0xe);
  if (0 < DebugLevel) {
    printk("==>%s()\n","sta_sae_auth_req_action");
  }
  if (iVar3 == 0) {
    printk(&_LC3,0x2e8);
    dump_stack();
    if (iVar5 == 0) {
      printk(&_LC1,0x2e9);
      dump_stack();
      return;
    }
  }
  else {
    if (iVar5 == 0) {
      printk(&_LC1,0x2e9);
      dump_stack();
    }
    if (((*(char *)(param_1 + 0x286285) != '\x01') || (*(int *)(iVar5 + 0x14) != 2)) ||
       (iVar4 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0)),
       bVar1 < *(byte *)(iVar4 + 0x14a))) {
      *(undefined4 *)(iVar3 + 0x413a) = *param_2;
      *(undefined2 *)(iVar3 + 0x413e) = *(undefined2 *)(param_2 + 1);
      if (*(int *)(iVar5 + 0x14) == 0x100) {
        uVar2 = *(undefined1 *)(*(int *)(iVar5 + 4) + 0x42b0);
      }
      else {
        uVar2 = *(undefined1 *)(iVar3 + 0x213393);
      }
      iVar3 = sae_auth_init(param_1,"pci_sw_int_handler" + param_1,iVar5 + 0x1b,param_2,
                            iVar3 + 0x413a,iVar5 + 0x179,uVar2);
      if (iVar3 != 0) {
        auth_fsm_state_transition(iVar5,3,"sta_sae_auth_req_action");
        return;
      }
      auth_fsm_state_transition(iVar5,0,"sta_sae_auth_req_action");
      cntl_auth_assoc_conf(iVar5,2,0x51);
      return;
    }
  }
  return;
}

