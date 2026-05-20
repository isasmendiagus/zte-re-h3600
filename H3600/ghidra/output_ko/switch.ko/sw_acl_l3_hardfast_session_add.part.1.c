// module: switch.ko
// function: sw_acl_l3_hardfast_session_add.part.1 @ 0x125e0
// size: 1644 bytes
//

int sw_acl_l3_hardfast_session_add_part_1(int param_1)

{
  ushort uVar1;
  undefined2 uVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  char *pcVar7;
  byte bVar8;
  uint *puVar9;
  uint *puVar10;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 uStack_c4;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  char local_b8 [4];
  undefined4 local_b4;
  undefined1 local_8c;
  short local_8a;
  undefined2 local_88;
  ushort local_86;
  undefined1 local_84;
  undefined1 local_83;
  undefined4 local_82;
  undefined2 local_7e;
  undefined4 local_7c;
  undefined2 local_78;
  undefined4 local_74;
  ushort local_64;
  byte local_50;
  ushort local_4e;
  undefined1 local_4c;
  undefined4 local_48;
  undefined1 local_44;
  uint local_34 [4];
  uint local_24;
  undefined2 local_20;
  undefined2 local_1e;
  byte local_1c;
  
  __memzero(local_b8,0xa0);
  iVar4 = TO_WAN(*(undefined4 *)(param_1 + 0x18));
  local_b8[0] = iVar4 == 0;
  if (2 < g_switch_debug_level) {
    printk("[%s] direction(0-up 1=dw)=%d\n","sw_acl_l3_hardfast_session_add",local_b8[0]);
  }
  if (1 < g_switch_debug_level) {
    printk("ip4Addr=%d, dest=%d, natip=%d, natport=%d, pip6Addr=%d, destport=%d, sdports=%d\n",
           *(undefined4 *)(param_1 + 4),*(undefined2 *)(param_1 + 10),
           *(undefined4 *)(param_1 + 0x20),*(undefined2 *)(param_1 + 0x2c),
           *(undefined4 *)(param_1 + 4),*(undefined2 *)(param_1 + 10),*(undefined4 *)(param_1 + 8));
  }
  if (*(char *)(param_1 + 0x14) == '\0') {
    sVar3 = local_8a;
    if (*(char *)(param_1 + 0x15) != '\0') {
      iVar4 = *(int *)(param_1 + 0xc);
      if (iVar4 == 0) {
        sVar3 = 0;
      }
      else {
        sVar3 = 1;
        if ((iVar4 != 1) && (sVar3 = local_8a, iVar4 == 2)) {
          sVar3 = 3;
        }
      }
    }
  }
  else {
    local_8a = 2;
    sVar3 = local_8a;
  }
  local_8a = sVar3;
  if (2 < g_switch_debug_level) {
    printk("uc_l2=%d, uc_l3=%d, l3Fast.l3_num=%d\n",*(char *)(param_1 + 0x14),
           *(undefined1 *)(param_1 + 0x15),local_8a);
  }
  sw_acl_setMtchInfo(param_1,local_b8);
  if (local_8a == 2) {
    if (param_1 == 0) {
      printk("[%s] params is NULL\n","sw_acl_setModInfo_L2");
      goto LAB_00012b84;
    }
    local_84 = 0;
    local_8c = (undefined1)*(undefined2 *)(param_1 + 0x52);
    if ((*(byte *)(param_1 + 0x4d) & 8) == 0) {
      if (((*(byte *)(param_1 + 0x4d) & 0xc) == 4) && (local_b8[0] == '\0')) {
        local_86 = 0xffff;
        local_8c = 0xff;
      }
      else {
        local_86 = 0xffff;
      }
    }
    else {
      local_88 = 0xffff;
      local_86 = *(ushort *)(param_1 + 0x34) << 8 | *(ushort *)(param_1 + 0x34) >> 8;
    }
    if (g_switch_debug_level < 3) goto LAB_00012740;
    printk("l2 len %d,  cvlan %d, svlan %d\n",local_8c,local_88,local_86);
LAB_00012864:
    local_cc = 0;
    uVar6 = (*(ushort *)(param_1 + 0x34) & 0xff) << 8 | (uint)(*(ushort *)(param_1 + 0x34) >> 8);
    if (2 < g_switch_debug_level) {
      printk("bTxVlan %d, vlan %d\n",((uint)*(byte *)(param_1 + 0x4d) << 0x1c) >> 0x1f,uVar6);
    }
  }
  else {
    if (param_1 == 0) {
      printk("[%s] params is NULL\n","sw_acl_setModInfo_L3");
LAB_00012b84:
      local_cc = 0;
      printk("[%s] params is NULL\n","sw_acl_setFwdInfo");
      goto LAB_000127a8;
    }
    local_82 = **(undefined4 **)(param_1 + 0x28);
    local_7e = *(undefined2 *)(*(undefined4 **)(param_1 + 0x28) + 1);
    local_7c = **(undefined4 **)(param_1 + 0x24);
    local_78 = *(undefined2 *)(*(undefined4 **)(param_1 + 0x24) + 1);
    local_84 = 0;
    if (*(int *)(param_1 + 0xc) == 2) {
      uVar2 = *(undefined2 *)(param_1 + 0x52);
      local_8c = (undefined1)uVar2;
joined_r0x00012a24:
      if (2 < g_switch_debug_level) {
        printk("l2_len %d, bTxVlan %d, bRxVlan %d, txVlan %d, rxVlan %d\n",uVar2,
               ((uint)*(byte *)(param_1 + 0x4d) << 0x1c) >> 0x1f,
               ((uint)*(byte *)(param_1 + 0x4d) << 0x1d) >> 0x1f,
               *(ushort *)(param_1 + 0x34) << 8 | *(ushort *)(param_1 + 0x34) >> 8,
               *(ushort *)(param_1 + 0x32) << 8 | *(ushort *)(param_1 + 0x32) >> 8);
      }
    }
    else {
      local_74 = *(undefined4 *)(param_1 + 0x20);
      local_64 = *(ushort *)(param_1 + 0x2c) << 8 | *(ushort *)(param_1 + 0x2c) >> 8;
      if (2 < g_switch_debug_level) {
        printk("set nat ip:0x%08x, set nat port %d\n",local_74,local_64);
        uVar2 = *(undefined2 *)(param_1 + 0x52);
        local_8c = (undefined1)uVar2;
        goto joined_r0x00012a24;
      }
      local_8c = (undefined1)*(undefined2 *)(param_1 + 0x52);
    }
    uVar6 = (uint)*(byte *)(param_1 + 0x4d);
    if ((*(byte *)(param_1 + 0x4d) & 8) == 0) {
      if (((uVar6 & 0xc) == 4) && (local_b8[0] == '\0')) {
        local_86 = 0xffff;
        local_8c = 0xff;
      }
      else {
        local_86 = 0xffff;
      }
    }
    else {
      local_88 = 0xffff;
      local_86 = *(ushort *)(param_1 + 0x34) << 8 | *(ushort *)(param_1 + 0x34) >> 8;
    }
    local_4e = *(ushort *)(param_1 + 0x2e) << 8 | *(ushort *)(param_1 + 0x2e) >> 8;
    local_50 = (byte)((uVar6 << 0x1f) >> 0x1f);
    if (2 < g_switch_debug_level) {
      printk("is ppp %d, set sessionid %d\n",uVar6 & 1,local_4e);
      if (*(int *)(param_1 + 0xc) == 2) goto LAB_00012804;
      goto LAB_00012864;
    }
    if (*(int *)(param_1 + 0xc) == 2) {
LAB_00012804:
      if (local_b8[0] == '\0') {
        local_4c = *(undefined1 *)(param_1 + 0x3c);
        puVar10 = (uint *)(*(int *)(param_1 + 0x44) + -4);
        local_48 = *(undefined4 *)(param_1 + 0x40);
        puVar9 = (uint *)(*(int *)(param_1 + 0x48) + -4);
        local_44 = *(undefined1 *)(param_1 + 0x3d);
        iVar4 = 0;
        pcVar7 = local_b8;
        do {
          puVar10 = puVar10 + 1;
          uVar6 = *puVar10;
          iVar4 = iVar4 + 1;
          *(uint *)(pcVar7 + 0x84) =
               uVar6 << 0x18 | (uVar6 >> 8 & 0xff) << 0x10 | (uVar6 >> 0x10 & 0xff) << 8 |
               uVar6 >> 0x18;
          puVar9 = puVar9 + 1;
          uVar6 = *puVar9;
          *(uint *)(pcVar7 + 0x94) =
               uVar6 << 0x18 | (uVar6 >> 8 & 0xff) << 0x10 | (uVar6 >> 0x10 & 0xff) << 8 |
               uVar6 >> 0x18;
          pcVar7 = pcVar7 + -4;
        } while (iVar4 != 4);
      }
      goto LAB_00012864;
    }
LAB_00012740:
    local_cc = 0;
    uVar6 = (*(ushort *)(param_1 + 0x34) & 0xff) << 8;
  }
  iVar4 = TO_WAN(*(undefined4 *)(param_1 + 0x18));
  if (iVar4 != 0) {
    bVar8 = *(byte *)(param_1 + 0x4d);
    if (g_switch_debug_level < 2) {
      local_1c = bVar8 & 8;
      local_20 = 0;
      if ((bVar8 & 8) != 0) {
        local_1c = (byte)(uVar6 >> 0xd);
      }
    }
    else {
      local_1c = *(byte *)(param_1 + 0x51);
      if ((bVar8 & 0x10) != 0) {
        local_83 = *(undefined1 *)(param_1 + 0x4c);
        local_84 = 1;
      }
      if (2 < g_switch_debug_level) {
        printk("sip %d, gemport %d, tcont %d, q %d\n",local_b4,local_1e,local_20,local_1c);
      }
    }
    goto LAB_000127a8;
  }
  get_sw_port_from_devname(*(undefined4 *)(param_1 + 0x18),&local_cc);
  local_1c = *(byte *)(param_1 + 0x51);
  local_1e = (undefined2)local_cc;
  if (g_switch_debug_level < 3) {
LAB_00012960:
    bVar8 = *(byte *)(param_1 + 0x4d);
    if ((bVar8 & 8) != 0) {
      uVar1 = *(ushort *)(param_1 + 0x34);
      goto LAB_00012978;
    }
LAB_00012a68:
    local_86 = 0xffff;
  }
  else {
    printk("down ptSession->outdev_name %s\n",*(undefined4 *)(param_1 + 0x18));
    if (2 < g_switch_debug_level) {
      printk("down uni port %d\n",local_1e);
      goto LAB_00012960;
    }
    bVar8 = *(byte *)(param_1 + 0x4d);
    if ((bVar8 & 8) == 0) goto LAB_00012a68;
    uVar1 = *(ushort *)(param_1 + 0x34);
LAB_00012978:
    local_88 = 0xffff;
    local_86 = uVar1 << 8 | uVar1 >> 8;
  }
  if ((bVar8 & 0x10) != 0) {
    if (*(int *)(param_1 + 0xc) == 0) {
      local_83 = *(undefined1 *)(param_1 + 0x4c);
      local_84 = 1;
    }
    else if (*(int *)(param_1 + 0xc) == 1) {
      local_84 = 1;
      local_83 = *(undefined1 *)(param_1 + 0x4c);
    }
  }
LAB_000127a8:
  iVar4 = zte_api_fast_l3_session_add(local_b8,&local_cc);
  if ((((iVar4 != 0) && (iVar5 = __printk_ratelimit("sw_acl_l3_hardfast_session_add"), iVar5 != 0))
      && (g_switch_debug_level != 0)) &&
     (iVar5 = ___ratelimit(&_rs_58399,"sw_acl_l3_hardfast_session_add"), iVar5 != 0)) {
    printk("[%s] zte_api_fast_l3_session_add failed %d\n","sw_acl_l3_hardfast_session_add",iVar4);
  }
  *(undefined4 *)(param_1 + 0x58) = local_cc;
  *(undefined4 *)(param_1 + 0x5c) = local_c8;
  *(undefined4 *)(param_1 + 0x60) = uStack_c4;
  *(undefined4 *)(param_1 + 100) = uStack_c0;
  *(undefined4 *)(param_1 + 0x68) = uStack_bc;
  return iVar4;
}

