// module: mt7915.ko
// function: show_time_log_info @ 0x147934
// size: 584 bytes
//

undefined4 show_time_log_info(undefined4 param_1,char *param_2)

{
  int iVar1;
  char cVar2;
  char *pcVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  bool bVar8;
  char *local_2c [2];
  
  local_2c[0] = param_2;
  pcVar3 = strsep(local_2c,":");
  if (pcVar3 == (char *)0x0) {
    cVar2 = '\0';
    if (local_2c[0] == (char *)0x0) {
      uVar4 = 0x28;
      cVar2 = '\0';
      goto LAB_001479a0;
    }
LAB_00147978:
    uVar4 = os_str_toul(local_2c[0],0,10);
    uVar4 = uVar4 & 0xff;
  }
  else {
    cVar2 = os_str_toul(pcVar3,0,10);
    if (local_2c[0] != (char *)0x0) goto LAB_00147978;
    uVar4 = 0xff;
  }
  if (cVar2 == '\x01') {
    if (5 < uVar4) {
      uVar4 = 6;
    }
    uVar6 = (uint)DAT_005f39cc;
    if (0 < DebugLevel) {
      printk("sae time log:\n");
    }
    uVar7 = 1;
    do {
      bVar8 = uVar6 == 0;
      uVar6 = uVar6 - 1 & 0xff;
      if (bVar8) {
        uVar6 = 5;
      }
      if (0 < DebugLevel) {
        printk(&_LC7,uVar7);
      }
      iVar1 = uVar6 * 0x8c;
      FUN_00147694(iVar1 + 0x5f39d0);
      FUN_00147694(iVar1 + 0x5f39e4);
      FUN_00147694(iVar1 + 0x5f39f8);
      FUN_00147694(iVar1 + 0x5f3a0c);
      FUN_00147694(iVar1 + 0x5f3a20);
      FUN_00147694(iVar1 + 0x5f3a34);
      FUN_00147694(iVar1 + 0x5f3a48);
      uVar5 = uVar7 & 0xff;
      uVar7 = uVar7 + 1;
    } while (uVar5 < uVar4);
    return 1;
  }
  if (0x27 < uVar4) {
    uVar4 = 0x28;
  }
LAB_001479a0:
  uVar6 = (uint)_LANCHOR0;
  if (0 < DebugLevel) {
    printk("misc time log:\n");
  }
  uVar7 = 0;
  do {
    if (uVar6 == 0) {
      uVar6 = 0x27;
    }
    else {
      uVar6 = uVar6 - 1 & 0xff;
    }
    if ((cVar2 == '\0') || ((&DAT_005f36bc)[uVar6 * 0x14] == cVar2)) {
      uVar7 = uVar7 + 1 & 0xff;
      if (0 < DebugLevel) {
        printk(&_LC7,uVar7);
      }
      FUN_00147694(&DAT_005f36ac + uVar6 * 0x14);
    }
  } while ((uVar7 < uVar4) && (_LANCHOR0 != uVar6));
  return 1;
}

