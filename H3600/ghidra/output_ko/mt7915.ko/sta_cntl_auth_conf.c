// module: mt7915.ko
// function: sta_cntl_auth_conf @ 0x6fd20
// size: 596 bytes
//

void sta_cntl_auth_conf(void *param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  short local_2a;
  undefined4 local_28;
  undefined2 local_24;
  ushort local_22;
  undefined4 local_20;
  
  iVar3 = *(int *)((int)param_1 + 0x92c);
  uVar4 = *(undefined4 *)(iVar3 + 8);
  iVar1 = GetStaCfgByWdev(uVar4,iVar3);
  if (iVar1 == 0) {
    printk(&_LC1,0x562);
    dump_stack();
    return;
  }
  os_move_mem(&local_2a,param_1,2);
  if (local_2a != 0) {
    if (2 < DebugLevel) {
      printk("CNTL - AUTH FAIL, try again...\n");
    }
    if ((*(uint *)(iVar3 + 0x2c) & 0x2000) == 0) {
      if ((*(uint *)(iVar3 + 0x2c) & 6) == 0) {
        local_22 = 0;
        uVar2 = 0;
      }
      else {
        local_22 = (ushort)((*(uint *)(iVar3 + 0x174) & 0xe) != 0);
        uVar2 = 0;
      }
    }
    else {
      uVar2 = 8;
      local_22 = 3;
    }
    local_28 = *(undefined4 *)(iVar1 + 0x413a);
    local_24 = *(undefined2 *)(iVar1 + 0x413e);
    local_20 = 300;
    MlmeEnqueueWithWdev(uVar4,2,uVar2,0x10,&local_28,0,iVar3);
    cntl_fsm_state_transition(iVar3,3,"sta_cntl_auth_conf");
    return;
  }
  if (2 < DebugLevel) {
    printk("CNTL - AUTH OK\n");
  }
  if (*(int *)(iVar3 + 0x14) == 0x100) {
    iVar5 = *(int *)(iVar3 + 4);
    if (iVar5 == 0) {
      printk(&_LC3,0x56b);
      dump_stack();
    }
    *(undefined2 *)(iVar5 + 0x72) = 0;
  }
  else {
    *(undefined2 *)(iVar1 + 0x21335a) = 0;
  }
  uVar2 = 5000;
  if ((*(uint *)(iVar1 + 0x2123d8) & 0x6000) == 0) {
    uVar2 = 300;
  }
  AssocParmFill(uVar4,&local_28,iVar1 + 0x413a,*(undefined2 *)(iVar1 + 0x416c),uVar2,
                *(undefined2 *)(iVar1 + 0x2124a6));
  if (*(char *)(iVar1 + 0x213176) == '\0') {
    MlmeEnqueueWithWdev(uVar4,1,0,0x10,&local_28,0,iVar3);
  }
  else {
    MlmeEnqueueWithWdev(uVar4,1,1,0x10,&local_28,0,iVar3);
    *(undefined1 *)(iVar1 + 0x213176) = 0;
  }
  cntl_fsm_state_transition(iVar3,5,"sta_cntl_auth_conf");
  return;
}

