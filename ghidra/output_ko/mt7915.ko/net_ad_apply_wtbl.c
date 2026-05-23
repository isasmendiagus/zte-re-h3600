// module: mt7915.ko
// function: net_ad_apply_wtbl @ 0x25beec
// size: 808 bytes
//

undefined4 net_ad_apply_wtbl(int param_1,undefined4 param_2,int param_3)

{
  byte bVar1;
  undefined1 uVar2;
  char cVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  undefined2 uVar9;
  undefined1 auStack_44 [4];
  undefined4 local_40;
  byte local_38;
  undefined1 local_36;
  char local_35;
  byte local_34;
  undefined1 local_33;
  byte local_32;
  undefined1 local_31;
  char local_30;
  
  iVar5 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar5 == 0) {
    return 0x606;
  }
  if (param_3 == 0) {
    return 0x607;
  }
  bVar1 = *(byte *)(param_3 + 0xc4);
  if (bVar1 < 5) {
    *(byte *)(param_3 + 0xbf) = *(byte *)(param_3 + 0xbf) & 0x1f | bVar1 << 5;
    if (1 < bVar1) {
      *(undefined1 *)(param_3 + 0xd05) = *(undefined1 *)(param_1 + 0x44);
      *(undefined1 *)(param_3 + 0x18) = *(undefined1 *)(param_1 + 0x44);
      if (bVar1 == 4) {
        *(undefined1 *)(param_3 + 0xd05) = *(undefined1 *)(param_1 + 0x49);
        *(undefined1 *)(param_3 + 0x1a) = *(undefined1 *)(param_1 + 0x48);
        *(undefined1 *)(param_3 + 0x1b) = *(undefined1 *)(param_1 + 0x49);
      }
    }
  }
  else {
    *(byte *)(param_3 + 0xbf) = *(byte *)(param_3 + 0xbf) & 0x1f | 0x80;
    *(undefined1 *)(param_3 + 0xd05) = *(undefined1 *)(param_1 + 0x44);
    *(undefined1 *)(param_3 + 0x18) = *(undefined1 *)(param_1 + 0x44);
    *(undefined1 *)(param_3 + 0xd05) = *(undefined1 *)(param_1 + 0x49);
    *(undefined1 *)(param_3 + 0x1a) = *(undefined1 *)(param_1 + 0x48);
    uVar2 = *(undefined1 *)(param_1 + 0x49);
    *(uint *)(param_3 + 100) = *(uint *)(param_3 + 100) | 0x18;
    *(uint *)(param_3 + 0x78) = *(uint *)(param_3 + 0x78) | 0x400000;
    *(undefined1 *)(param_3 + 0x1b) = uVar2;
    *(undefined1 *)(param_3 + 0x1c) = *(undefined1 *)(param_1 + 0x4c);
  }
  *(undefined1 *)(param_3 + 0x2b) = 2;
  *(uint *)(param_3 + 0xb4) = *(uint *)(param_3 + 0xb4) | 1;
  if ((*(int *)(param_3 + 4) != 1) && (iVar6 = wifi_sys_conn_act(param_2,param_3), iVar6 == 0)) {
    printk("%s(): connect action fail!\n","net_ad_apply_wtbl");
  }
  iVar6 = hc_get_hif_type(*(undefined4 *)(iVar5 + 0xa797a0));
  if (iVar6 == 2) {
    RAInit(iVar5,param_3);
  }
  uVar8 = 0;
  if (*(byte *)(param_3 + 0xc4) < 5) {
    uVar9 = *(undefined2 *)(param_1 + 0x46);
  }
  else {
    uVar9 = *(undefined2 *)(param_1 + 0x4a);
  }
  do {
    uVar7 = uVar8 & 0xff;
    uVar8 = uVar8 + 1;
    AsicUpdateBASession(iVar5,*(undefined2 *)(param_3 + 0xe0),uVar7,0,uVar9,1,1,0);
  } while (uVar8 != 8);
  if (*(char *)(param_1 + 0x71) != '\x01') {
    return 0;
  }
  *(undefined1 *)(param_3 + 0xb7e) = 0;
  cVar3 = *(char *)(param_3 + 0xc9);
  cVar4 = *(char *)(param_3 + 0xca);
  sys_ad_zero_mem(auStack_44,0x1c);
  local_38 = *(byte *)(param_3 + 0xc4);
  uVar8 = (uint)local_38;
  local_36 = *(undefined1 *)(param_3 + 200);
  if (uVar8 < 8) {
    if (*(char *)(param_3 + 0xc9) == '\0') {
      local_34 = *(byte *)(param_3 + 0xc6);
      local_35 = '\0';
    }
    else {
      local_34 = *(byte *)(param_3 + 0xc6);
      local_35 = '\x01' << (uint)local_34;
    }
  }
  else {
    local_34 = *(byte *)(param_3 + 0xc6);
    if (local_34 == 2) {
      local_35 = cVar3 << 4;
      local_30 = cVar4 << 4;
    }
    else if (local_34 == 3) {
      local_35 = cVar3 << 6;
      local_30 = cVar4 << 6;
    }
    else {
      local_35 = cVar3;
      local_30 = cVar4;
      if (local_34 == 1) {
        local_35 = cVar3 << 2;
        local_30 = cVar4 << 2;
      }
    }
  }
  if (*(char *)(param_3 + 199) != '\0') {
    switch(uVar8) {
    case 2:
    case 3:
      local_33 = 1;
      break;
    case 4:
      local_33 = 2;
      local_32 = (byte)*(undefined4 *)(param_3 + 0xd0);
      goto LAB_0025c188;
    default:
      local_33 = 0;
      break;
    case 8:
    case 9:
    case 10:
    case 0xb:
      local_33 = 4;
    }
  }
  local_32 = (byte)*(undefined4 *)(param_3 + 0xd0);
  if (uVar8 - 0xb < 2) {
    local_32 = 7;
    local_38 = 1;
  }
LAB_0025c188:
  local_40 = 3;
  if (*(char *)(param_3 + 0xd4) != '\0') {
    local_32 = local_32 | 0x10;
  }
  if (*(char *)(param_3 + 0xd5) != '\0') {
    local_32 = local_32 | 0x20;
  }
  local_31 = *(undefined1 *)(param_3 + 0xcd);
  RAParamUpdate(iVar5,param_3,auStack_44);
  return 0;
}

