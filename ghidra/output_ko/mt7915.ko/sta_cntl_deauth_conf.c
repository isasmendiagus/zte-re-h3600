// module: mt7915.ko
// function: sta_cntl_deauth_conf @ 0x7393c
// size: 428 bytes
//

void sta_cntl_deauth_conf(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined4 uVar6;
  char cVar7;
  
  iVar3 = *(int *)(param_1 + 0x92c);
  uVar6 = *(undefined4 *)(iVar3 + 8);
  iVar1 = GetStaCfgByWdev(uVar6,iVar3);
  if (iVar1 == 0) {
    printk(&_LC1,0x6b2);
    dump_stack();
    return;
  }
  if (2 < DebugLevel) {
    printk("CNTL - DeAuth successful\n");
  }
  cVar7 = *(char *)(iVar1 + 0x213336);
  if (*(int *)(iVar3 + 0x14) == 0x100) {
    iVar5 = *(int *)(iVar3 + 4);
    if (iVar5 == 0) {
      printk(&_LC3,0x6bc);
      dump_stack();
    }
    cVar7 = *(char *)(iVar5 + 1);
    puVar4 = (undefined4 *)(iVar5 + 0x98);
LAB_00073a4c:
    if (cVar7 != '\0') goto LAB_00073a54;
  }
  else {
    puVar4 = (undefined4 *)(iVar1 + 0x21334c);
    if (*(int *)(iVar3 + 0x14) == 2) {
      uVar2 = HcGetBandByWdev(iVar3);
      repeater_disconnect_by_band(uVar6,uVar2);
      goto LAB_00073a4c;
    }
    if (cVar7 == '\0') goto LAB_000739a8;
LAB_00073a54:
    *puVar4 = 1;
    LinkDown(uVar6,0,iVar3,param_1);
  }
  if (*(int *)(iVar3 + 0x14) == 0x100) {
    cntl_fsm_state_transition(iVar3,0,"sta_cntl_deauth_conf",param_4);
    return;
  }
LAB_000739a8:
  *(undefined1 *)(iVar1 + 0x213336) = 0;
  __memzero(iVar1 + 0x413a,6);
  *(undefined1 *)(iVar1 + 0x4139) = 0;
  __memzero(iVar1 + 0x4119,0x20);
  *(undefined4 *)(iVar1 + 0x21239c) = 0;
  cntl_fsm_state_transition(iVar3,0,"sta_cntl_deauth_conf");
  if (*(char *)(iVar3 + 0x888) != '\x02') {
    return;
  }
  if ((*(uint *)(iVar3 + 0x2c) & 0x90) == 0) {
    return;
  }
  if (4 < *(int *)(iVar1 + 0x12f4)) {
    return;
  }
  *(int *)(iVar1 + 0x211e40) = *(int *)(iVar1 + 0x211e40) + 1;
  IterateOnBssTab(uVar6,iVar3);
  return;
}

