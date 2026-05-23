// module: mt7915.ko
// function: sta_cntl_join_conf @ 0x73d94
// size: 992 bytes
//

void sta_cntl_join_conf(void *param_1)

{
  int iVar1;
  int iVar2;
  size_t sVar3;
  uint uVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined4 *puVar7;
  int iVar8;
  short local_68;
  undefined4 local_66;
  undefined2 local_62;
  undefined4 local_60;
  undefined2 local_5c;
  undefined2 local_5a;
  undefined4 local_58;
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [36];
  
  iVar6 = *(int *)((int)param_1 + 0x92c);
  iVar8 = *(int *)(iVar6 + 8);
  iVar1 = GetStaCfgByWdev(iVar8,iVar6);
  if (iVar1 == 0) {
    printk(&_LC1,0x49e);
    dump_stack();
    return;
  }
  os_move_mem(&local_68,param_1,2);
  if (local_68 != 0) {
    if (local_68 == 0x51) {
      cntl_fsm_state_transition(iVar6,0,"sta_cntl_join_conf");
    }
    else if (*(int *)(iVar6 + 0x14) == 2) {
      if ((*(byte *)(iVar8 + 0x286294) & 3) != 3) {
        *(int *)(iVar1 + 0x211e40) = *(int *)(iVar1 + 0x211e40) + 1;
        IterateOnBssTab(iVar8,iVar6);
        return;
      }
      FUN_000702fc(iVar8,iVar6);
    }
    return;
  }
  iVar2 = GetAssociatedAPByWdev(iVar8,iVar6);
  uVar4 = (uint)(*(int *)(iVar1 + 0x2c) << 0x12) >> 0x1f;
  if (iVar2 == 0) {
    uVar4 = 0;
  }
  if ((uVar4 == 0) || ((*(uint *)(iVar2 + 0x17c) & 0x2000) == 0)) {
    if (*(int *)(iVar6 + 0x14) == 0x100) {
      iVar2 = *(int *)(iVar6 + 4);
      if (iVar2 == 0) {
        printk(&_LC3,0x509);
        dump_stack();
      }
      *(undefined2 *)(iVar2 + 0x70) = 0;
      if (0 < DebugLevel) {
        printk("(%s) Repeater Cli Trigger Auth Req CliIdx = %d !!!\n","sta_cntl_join_conf",
               *(undefined1 *)(iVar6 + 0xe));
      }
    }
    else {
      *(undefined2 *)(iVar1 + 0x213358) = 0;
    }
    if (((*(uint *)(iVar6 + 0x2c) & 6) == 0) || ((*(uint *)(iVar6 + 0x174) & 0xe) == 0)) {
      local_5a = 0;
    }
    else {
      local_5a = 1;
    }
    local_60 = *(undefined4 *)(iVar1 + 0x413a);
    local_5c = *(undefined2 *)(iVar1 + 0x413e);
    local_58 = 300;
    if ((*(uint *)(iVar6 + 0x174) & 0xf) == 0) {
      sVar3 = strlen((char *)(iVar6 + 0x179));
      SetWPAPSKKey(iVar8,(char *)(iVar6 + 0x179),sVar3,iVar1 + 0x4119,
                   *(undefined1 *)(iVar1 + 0x4139),iVar6 + 0x1ba);
    }
    MlmeEnqueueWithWdev(iVar8,2,0,0x10,&local_60,0,iVar6);
  }
  else {
    __memzero(&local_66,6);
    puVar7 = (undefined4 *)(iVar1 + 0x413a);
    if (*(int *)(iVar6 + 0x14) == 0x100) {
      puVar5 = (undefined4 *)(*(int *)(iVar6 + 4) + 0x83);
      local_66 = *puVar5;
    }
    else {
      puVar5 = (undefined4 *)(iVar1 + 0x1b);
      local_66 = *puVar5;
    }
    local_62 = *(undefined2 *)(puVar5 + 1);
    iVar2 = sae_get_pmk_cache("pci_sw_int_handler" + iVar8,&local_66,puVar7,auStack_50,auStack_40);
    if (iVar2 == 0) {
      local_60 = *puVar7;
      local_5c = *(undefined2 *)(iVar1 + 0x413e);
      local_5a = 3;
      local_58 = 300;
      auth_fsm_state_transition(iVar6,0,"sta_cntl_join_conf");
      MlmeEnqueueWithWdev(iVar8,2,8,0x10,&local_60,0,iVar6);
      if (0 < DebugLevel) {
        printk("CNTL(%s) - use SAE\n","sta_cntl_join_conf");
      }
    }
    else {
      sta_add_pmkid_cache(iVar8,puVar7,auStack_50,auStack_40,0x20,*(undefined1 *)(iVar1 + 0xe),iVar6
                         );
      local_60 = *puVar7;
      local_5c = *(undefined2 *)(iVar1 + 0x413e);
      local_5a = 0;
      local_58 = 300;
      MlmeEnqueueWithWdev(iVar8,2,0,0x10,&local_60,0,iVar6);
      if (0 < DebugLevel) {
        printk("CNTL(%s) - use pmkid\n","sta_cntl_join_conf");
      }
    }
  }
  cntl_fsm_state_transition(iVar6,2,"sta_cntl_join_conf");
  return;
}

