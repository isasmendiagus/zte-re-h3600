// module: mt7915.ko
// function: sta_cntl_disassoc_conf @ 0x735dc
// size: 452 bytes
//

void sta_cntl_disassoc_conf(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  bool bVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  char cVar8;
  
  iVar5 = *(int *)(param_1 + 0x92c);
  uVar7 = *(undefined4 *)(iVar5 + 8);
  iVar2 = GetStaCfgByWdev(uVar7,iVar5);
  if (iVar2 == 0) {
    printk(&_LC1,0x6ff);
    dump_stack();
    return;
  }
  if (2 < DebugLevel) {
    printk("CNTL - Dis-associate successful\n");
  }
  cVar8 = *(char *)(iVar2 + 0x213336);
  if (*(int *)(iVar5 + 0x14) == 0x100) {
    iVar4 = *(int *)(iVar5 + 4);
    if (iVar4 == 0) {
      printk(&_LC3,0x709);
      dump_stack();
    }
    cVar8 = *(char *)(iVar4 + 1);
    puVar6 = (undefined4 *)(iVar4 + 0x98);
LAB_000736e4:
    if (cVar8 != '\0') goto LAB_000736ec;
  }
  else {
    puVar6 = (undefined4 *)(iVar2 + 0x21334c);
    if (*(int *)(iVar5 + 0x14) == 2) {
      uVar3 = HcGetBandByWdev(iVar5);
      repeater_disconnect_by_band(uVar7,uVar3);
      goto LAB_000736e4;
    }
    if (cVar8 == '\0') goto LAB_00073648;
LAB_000736ec:
    *puVar6 = 2;
    LinkDown(uVar7,0,iVar5,param_1);
  }
  if (*(int *)(iVar5 + 0x14) == 0x100) {
    cntl_fsm_state_transition(iVar5,0,"sta_cntl_disassoc_conf",param_4);
    return;
  }
LAB_00073648:
  *(undefined1 *)(iVar2 + 0x213336) = 0;
  __memzero(iVar2 + 0x413a,6);
  *(undefined1 *)(iVar2 + 0x4139) = 0;
  __memzero(iVar2 + 0x4119,0x20);
  *(undefined4 *)(iVar2 + 0x21239c) = 0;
  *(int *)(iVar2 + 0x211e40) = *(int *)(iVar2 + 0x211e40) + 1;
  iVar4 = *(int *)(iVar2 + 0x12f4);
  if (1 < iVar4) {
    cntl_fsm_state_transition(iVar5,0,"sta_cntl_disassoc_conf");
    CntlWscIterate(uVar7,iVar2);
    return;
  }
  bVar1 = *(char *)(iVar2 + 0x3cc8) == '\0';
  if (iVar4 == 1 || !bVar1) {
    return;
  }
  IterateOnBssTab(uVar7,iVar5,iVar4 != 1 && bVar1,param_4);
  return;
}

