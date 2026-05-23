// module: mt7915.ko
// function: IterateOnBssTab @ 0x73254
// size: 900 bytes
//

void IterateOnBssTab(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint local_4c [12];
  
  iVar1 = GetStaCfgByWdev();
  puVar2 = (undefined4 *)get_scan_tab_by_wdev(param_1,param_2);
  if (iVar1 == 0) {
    printk(&_LC1,0x107d);
    dump_stack();
    return;
  }
  *(undefined4 *)(iVar1 + 0x2124cc) = *(undefined4 *)(param_2 + 0x174);
  *(undefined4 *)(iVar1 + 0x2124d0) = *(undefined4 *)(param_2 + 0x254);
  uVar6 = *(uint *)(iVar1 + 0x211e40);
  if ((*(uint *)(iVar1 + 0x4228) <= uVar6) || (*(char *)(iVar1 + 0x4060) != '\x01')) {
    if (2 < DebugLevel) {
      printk("CNTL - All roaming failed, restore to channel %d, Total BSS[%02d]\n",
             *(undefined1 *)(param_2 + 0x1a),*puVar2);
    }
    *(undefined4 *)(iVar1 + 0x4228) = 0;
    BssTableDeleteEntry(puVar2,iVar1 + 0x4236,*(undefined1 *)(iVar1 + 0x423c));
    cntl_fsm_state_transition(param_2,0,"IterateOnBssTab");
    return;
  }
  uVar4 = *(uint *)(uVar6 * 0xaf4 + iVar1 + 0x42f4) & *(uint *)(param_2 + 0x2c);
  *(uint *)(iVar1 + 0x2124d4) = uVar4;
  if ((uVar4 & 0x48) == 0x48) {
    *(undefined4 *)(iVar1 + 0x2124d4) = 0x40;
    uVar4 = *(uint *)(param_2 + 0x2c);
  }
  else if ((uVar4 & 0x90) == 0x90) {
    *(undefined4 *)(iVar1 + 0x2124d4) = 0x80;
    uVar4 = *(uint *)(param_2 + 0x2c);
  }
  else {
    uVar4 = *(uint *)(param_2 + 0x2c);
    if ((uVar4 & 0x2080) == 0x2080) {
      *(undefined4 *)(iVar1 + 0x2124d4) = 0x2000;
      uVar4 = *(uint *)(param_2 + 0x2c);
    }
  }
  if ((uVar4 & 0x18) != 0) {
    iVar5 = uVar6 * 0xaf4 + iVar1;
    uVar3 = *(undefined4 *)(iVar5 + 0x42fc);
    *(undefined4 *)(iVar1 + 0x2124cc) = 0;
    *(undefined4 *)(iVar1 + 0x2124d0) = uVar3;
    if (((*(uint *)(param_2 + 0x174) & 0x20) == 0) || ((*(uint *)(iVar5 + 0x42f8) & 0x20) == 0)) {
      *(undefined4 *)(iVar1 + 0x2124cc) = 0x10;
      uVar4 = *(uint *)(param_2 + 0x2c);
    }
    else {
      *(undefined4 *)(iVar1 + 0x2124cc) = 0x20;
      uVar4 = *(uint *)(param_2 + 0x2c);
    }
  }
  if ((uVar4 & 0x20c0) == 0) {
    if ((*(uint *)(param_2 + 0x2c) & 0x10000) == 0) goto LAB_00073420;
    iVar5 = uVar6 * 0xaf4 + iVar1;
    uVar3 = *(undefined4 *)(iVar5 + 0x42fc);
    *(undefined4 *)(iVar1 + 0x2124cc) = 0;
    *(undefined4 *)(iVar1 + 0x2124d0) = uVar3;
    if (((*(uint *)(param_2 + 0x174) & 0x100) == 0) || ((*(uint *)(iVar5 + 0x42f8) & 0x100) == 0)) {
      if (((*(uint *)(param_2 + 0x174) & 0x40) != 0) &&
         ((*(uint *)(uVar6 * 0xaf4 + iVar1 + 0x42f8) & 0x40) != 0)) goto LAB_00073400;
    }
    else {
LAB_000734d8:
      *(undefined4 *)(iVar1 + 0x2124cc) = 0x100;
    }
  }
  else {
    iVar5 = uVar6 * 0xaf4 + iVar1;
    uVar3 = *(undefined4 *)(iVar5 + 0x42fc);
    *(undefined4 *)(iVar1 + 0x2124cc) = 0;
    *(undefined4 *)(iVar1 + 0x2124d0) = uVar3;
    uVar4 = *(uint *)(param_2 + 0x174);
    if (((uVar4 & 0x20) == 0) || ((*(uint *)(iVar5 + 0x42f8) & 0x20) == 0)) {
      if (((uVar4 & 0x40) == 0) || ((*(uint *)(uVar6 * 0xaf4 + iVar1 + 0x42f8) & 0x40) == 0)) {
        if (((uVar4 & 0x80) == 0) || ((*(uint *)(uVar6 * 0xaf4 + iVar1 + 0x42f8) & 0x80) == 0)) {
          if (((uVar4 & 0x100) != 0) && ((*(uint *)(uVar6 * 0xaf4 + iVar1 + 0x42f8) & 0x100) != 0))
          goto LAB_000734d8;
          if ((*(uint *)(param_2 + 0x2c) & 0x2000) == 0) {
            *(undefined4 *)(iVar1 + 0x2124cc) = 0x10;
          }
        }
        else {
          *(undefined4 *)(iVar1 + 0x2124cc) = 0x80;
        }
      }
      else {
LAB_00073400:
        *(undefined4 *)(iVar1 + 0x2124cc) = 0x40;
      }
    }
    else {
      *(undefined4 *)(iVar1 + 0x2124cc) = 0x20;
    }
  }
  *(undefined2 *)(iVar1 + 0x2124d8) = *(undefined2 *)(uVar6 * 0xaf4 + iVar1 + 0x4300);
LAB_00073420:
  if (2 < DebugLevel) {
    printk("CNTL - iterate BSS %ld of %d\n",uVar6);
  }
  local_4c[0] = uVar6;
  MlmeEnqueueWithWdev(param_1,4,0,0x2c,local_4c,0,param_2);
  cntl_fsm_state_transition(param_2,1,"IterateOnBssTab");
  return;
}

