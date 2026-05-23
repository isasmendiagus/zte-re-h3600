// module: mt7915.ko
// function: ate_conn_act @ 0x27c530
// size: 1084 bytes
//

undefined4 ate_conn_act(int param_1,int param_2)

{
  byte bVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  undefined2 uVar7;
  uint uVar8;
  undefined1 auStack_3c [4];
  undefined4 local_38;
  byte local_30;
  undefined1 local_2e;
  char local_2d;
  sbyte local_2c;
  undefined1 local_2b;
  byte local_2a;
  undefined1 local_29;
  char local_28;
  undefined1 local_26;
  
  iVar6 = *(int *)(param_1 + 8);
  if (param_2 == 0) {
    iVar3 = net_ad_wrap_service(iVar6);
    iVar4 = net_ad_wrap_service(iVar6);
    param_2 = MacTableInsertEntry(iVar6,(uint)*(byte *)(iVar4 + 0x4cc) * 0xd18 + iVar3 + 0x531,
                                  param_1,0x20,4,1);
    if (param_2 == 0) {
      if (DebugLevel < 0) {
        return 0xffffffff;
      }
      printk("%s: MacTableInsertEntry failed\n","ate_conn_act");
      return 0xffffffff;
    }
  }
  iVar3 = hc_get_chip_cap(*(undefined4 *)(iVar6 + 0xa797a0));
  bVar1 = *(byte *)(param_2 + 0xc4);
  if (bVar1 < 5) {
    *(byte *)(param_2 + 0xbf) = *(byte *)(param_2 + 0xbf) & 0x1f | bVar1 << 5;
    if (1 < bVar1) {
      *(undefined1 *)(param_2 + 0xd05) = *(undefined1 *)(iVar3 + 0x5f);
      *(undefined1 *)(param_2 + 0x18) = *(undefined1 *)(iVar3 + 0x5f);
      if (bVar1 == 4) {
        *(undefined1 *)(param_2 + 0xd05) = *(undefined1 *)(iVar3 + 0x61);
        *(undefined1 *)(param_2 + 0x1a) = *(undefined1 *)(iVar3 + 0x60);
        *(undefined1 *)(param_2 + 0x1b) = *(undefined1 *)(iVar3 + 0x61);
      }
    }
  }
  else {
    *(byte *)(param_2 + 0xbf) = *(byte *)(param_2 + 0xbf) & 0x1f | 0x80;
    *(undefined1 *)(param_2 + 0xd05) = *(undefined1 *)(iVar3 + 0x5f);
    *(undefined1 *)(param_2 + 0x18) = *(undefined1 *)(iVar3 + 0x5f);
    *(undefined1 *)(param_2 + 0xd05) = *(undefined1 *)(iVar3 + 0x61);
    *(undefined1 *)(param_2 + 0x1a) = *(undefined1 *)(iVar3 + 0x60);
    uVar2 = *(undefined1 *)(iVar3 + 0x61);
    *(uint *)(param_2 + 100) = *(uint *)(param_2 + 100) | 0x18;
    *(uint *)(param_2 + 0x78) = *(uint *)(param_2 + 0x78) | 0x400000;
    *(undefined1 *)(param_2 + 0x1b) = uVar2;
    *(undefined1 *)(param_2 + 0x1c) = *(undefined1 *)(iVar3 + 100);
  }
  *(undefined1 *)(param_2 + 0x2b) = 2;
  *(uint *)(param_2 + 0xb4) = *(uint *)(param_2 + 0xb4) | 1;
  iVar4 = wifi_sys_conn_act(param_1,param_2);
  if ((iVar4 != 1) && (-1 < DebugLevel)) {
    printk("%s(): connect action fail!\n","ate_conn_act");
  }
  uVar8 = *(uint *)("Get_RBIST_IQ_Data_Proc" + iVar6 + 0xc) & 0xffff;
  if (uVar8 == 0x7915 ||
      (uVar8 == 0x6867 ||
      (uVar8 == 0x7663 ||
      (uVar8 == 0x6632 || (uVar8 == 0x7622 || (uVar8 == 0x7615 || uVar8 == 0x7637)))))) {
    RAInit(iVar6,param_2);
  }
  uVar8 = 0;
  if (*(byte *)(param_2 + 0xc4) < 5) {
    uVar7 = *(undefined2 *)(iVar3 + 0x52);
  }
  else {
    uVar7 = *(undefined2 *)(iVar3 + 0x4e);
  }
  do {
    uVar5 = uVar8 & 0xff;
    uVar8 = uVar8 + 1;
    AsicUpdateBASession(iVar6,*(undefined2 *)(param_2 + 0xe0),uVar5,0,uVar7,1,1,1);
  } while (uVar8 != 8);
  if (*(char *)(iVar3 + 0x150) != '\x01') {
    if (-1 < DebugLevel) {
      printk("%s: fgRateAdaptFWOffload Not supported\n","ate_conn_act");
    }
    return 0xffffffff;
  }
  *(undefined1 *)(param_2 + 0xb7e) = 0;
  __memzero(auStack_3c,0x1c);
  local_30 = *(byte *)(param_2 + 0xc4);
  uVar8 = (uint)local_30;
  local_2e = *(undefined1 *)(param_2 + 200);
  if (uVar8 - 0xb < 2) {
    *(undefined4 *)(param_2 + 0xd0) = 7;
    local_30 = 1;
  }
  else if (uVar8 < 8) {
    local_2c = *(sbyte *)(param_2 + 0xc6);
    local_2d = '\0';
    if (*(char *)(param_2 + 0xc9) != '\0') {
      local_2d = '\x01' << local_2c;
    }
    goto LAB_0027c78c;
  }
  local_2c = *(sbyte *)(param_2 + 0xc6);
  local_2d = *(char *)(param_2 + 0xc9);
  local_28 = *(char *)(param_2 + 0xca);
  if (local_2c == 2) {
    local_2d = local_2d << 4;
    local_28 = local_28 << 4;
  }
  else if (local_2c == 3) {
    local_2d = local_2d << 6;
    local_28 = local_28 << 6;
  }
  else if (local_2c == 1) {
    local_2d = local_2d << 2;
    local_28 = local_28 << 2;
  }
LAB_0027c78c:
  if (*(char *)(param_2 + 199) != '\0') {
    switch(uVar8) {
    case 2:
    case 3:
      local_2b = 1;
      break;
    case 4:
      local_2b = 2;
      break;
    default:
      local_2b = 0;
      break;
    case 8:
    case 9:
    case 10:
    case 0xb:
      local_2b = 4;
    }
  }
  local_2a = *(byte *)(param_2 + 0xd0);
  if (*(char *)(param_2 + 0xd4) != '\0') {
    local_2a = local_2a | 0x10;
  }
  if (*(char *)(param_2 + 0xd5) != '\0') {
    local_2a = local_2a | 0x20;
  }
  local_29 = *(undefined1 *)(param_2 + 0xcd);
  iVar3 = net_ad_wrap_service(iVar6);
  iVar4 = HcGetBandByWdev(param_1);
  local_38 = 3;
  local_26 = *(undefined1 *)(iVar4 * 0xd18 + iVar3 + 0x113d);
  RAParamUpdate(iVar6,param_2,auStack_3c);
  return 0;
}

