// module: mt7915.ko
// function: sta_cntl_auth2_conf @ 0x73aec
// size: 676 bytes
//

void sta_cntl_auth2_conf(void *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  short local_2a;
  undefined4 local_28;
  undefined2 local_24;
  undefined2 local_22;
  undefined4 local_20;
  
  puVar4 = *(undefined4 **)((int)param_1 + 0x92c);
  iVar5 = puVar4[2];
  iVar1 = GetStaCfgByWdev(iVar5,puVar4);
  if (iVar1 != 0) {
    iVar2 = GetAssociatedAPByWdev(iVar5,puVar4);
    os_move_mem(&local_2a,param_1,2);
    if (local_2a == 0) {
      if (2 < DebugLevel) {
        printk("CNTL - AUTH OK\n");
      }
      AssocParmFill(iVar5,&local_28,iVar1 + 0x413a,*(undefined2 *)(iVar1 + 0x416c),300,
                    *(undefined2 *)(iVar1 + 0x2124a6));
      MlmeEnqueueWithWdev(iVar5,1,0,0x10,&local_28,0,puVar4);
      cntl_fsm_state_transition(puVar4,5,"sta_cntl_auth2_conf");
    }
    else if ((*(uint *)(iVar1 + 0x2c) & 6) == 6) {
      if (2 < DebugLevel) {
        printk("CNTL - AUTH FAIL, try OPEN system...\n");
      }
      local_28 = *(undefined4 *)(iVar1 + 0x413a);
      local_24 = *(undefined2 *)(iVar1 + 0x413e);
      local_22 = 0;
      local_20 = 300;
      MlmeEnqueueWithWdev(iVar5,2,0,0x10,&local_28,0,puVar4);
      cntl_fsm_state_transition(puVar4,2,"sta_cntl_auth2_conf");
    }
    else {
      if (2 < DebugLevel) {
        printk("CNTL - AUTH [%s, wdev_type=%d] FAIL, give up; try next BSS\n",*puVar4,puVar4[5]);
      }
      iVar3 = puVar4[5];
      if (iVar3 == 2 && iVar2 != 0) {
        MacTableDeleteEntry(iVar5,*(undefined2 *)(iVar2 + 0xe0),iVar2 + 0xec);
        iVar3 = puVar4[5];
      }
      if ((iVar3 == 0x100) &&
         (HW_REMOVE_REPT_ENTRY(iVar5,*(undefined1 *)((int)puVar4 + 0xe)), -1 < DebugLevel)) {
        printk("%s:wdev(type=%d,func_idx=%d)auth fail reason(%d) and free rept_entry\n",
               "sta_cntl_auth2_conf",puVar4[5],*(undefined1 *)((int)puVar4 + 0xe),local_2a);
      }
      cntl_fsm_state_transition(puVar4,0,"sta_cntl_auth2_conf");
      *(int *)(iVar1 + 0x211e40) = *(int *)(iVar1 + 0x211e40) + 1;
      if (puVar4[5] == 2) {
        if ((*(byte *)(iVar5 + 0x286294) & 3) == 3) {
          FUN_000702fc(iVar5,puVar4);
        }
        else {
          IterateOnBssTab();
        }
      }
    }
    return;
  }
  printk(&_LC1,0x5c6);
  dump_stack();
  return;
}

