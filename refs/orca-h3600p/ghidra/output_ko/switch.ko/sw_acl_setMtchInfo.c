// module: switch.ko
// function: sw_acl_setMtchInfo @ 0x1199c
// size: 628 bytes
//

void sw_acl_setMtchInfo(int *param_1,int param_2)

{
  short sVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  ushort uVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  ushort uVar8;
  char *__s1;
  undefined4 uVar9;
  undefined4 local_1c [2];
  
  local_1c[0] = 0;
  if (param_1 == (int *)0x0 || param_2 == 0) {
    printk("[%s] params is NULL\n","sw_acl_setMtchInfo");
    return;
  }
  uVar5 = *(ushort *)((int)param_1 + 10) << 8 | *(ushort *)((int)param_1 + 10) >> 8;
  *(ushort *)(param_2 + 0x26) = uVar5;
  uVar2 = g_switch_debug_level;
  uVar8 = *(ushort *)(param_1 + 2) << 8 | *(ushort *)(param_1 + 2) >> 8;
  *(ushort *)(param_2 + 0x24) = uVar8;
  *(char *)(param_2 + 0x28) = (char)param_1[4];
  if (uVar2 < 3) {
    if ((param_1[3] & 0xfffffffdU) != 0) {
      puVar6 = (undefined4 *)*param_1;
      sVar1 = *(short *)(param_2 + 0x2e);
      uVar3 = puVar6[2];
      uVar9 = *puVar6;
      uVar7 = puVar6[3];
      *(undefined4 *)(param_2 + 8) = puVar6[1];
      *(undefined4 *)(param_2 + 4) = uVar9;
      *(undefined4 *)(param_2 + 0xc) = uVar3;
      *(undefined4 *)(param_2 + 0x10) = uVar7;
      puVar6 = (undefined4 *)param_1[1];
      uVar3 = puVar6[1];
      uVar7 = puVar6[2];
      uVar9 = puVar6[3];
      *(undefined4 *)(param_2 + 0x14) = *puVar6;
      *(undefined4 *)(param_2 + 0x18) = uVar3;
      *(undefined4 *)(param_2 + 0x1c) = uVar7;
      *(undefined4 *)(param_2 + 0x20) = uVar9;
      goto joined_r0x00011a7c;
    }
    *(int *)(param_2 + 4) = *param_1;
    *(int *)(param_2 + 0x14) = param_1[1];
  }
  else {
    printk("match dport %d,sport %d, prot %d\n",uVar5,uVar8);
    uVar2 = g_switch_debug_level;
    puVar6 = (undefined4 *)*param_1;
    if ((param_1[3] & 0xfffffffdU) == 0) {
      *(undefined4 **)(param_2 + 4) = puVar6;
      *(int *)(param_2 + 0x14) = param_1[1];
      if (2 < uVar2) {
        printk("acl filed sip 0x%08x,dip 0x%08x\n");
      }
    }
    else {
      uVar3 = puVar6[2];
      uVar9 = *puVar6;
      uVar7 = puVar6[3];
      *(undefined4 *)(param_2 + 8) = puVar6[1];
      *(undefined4 *)(param_2 + 4) = uVar9;
      *(undefined4 *)(param_2 + 0xc) = uVar3;
      *(undefined4 *)(param_2 + 0x10) = uVar7;
      puVar6 = (undefined4 *)param_1[1];
      uVar3 = puVar6[1];
      uVar7 = puVar6[2];
      uVar9 = puVar6[3];
      *(undefined4 *)(param_2 + 0x14) = *puVar6;
      *(undefined4 *)(param_2 + 0x18) = uVar3;
      *(undefined4 *)(param_2 + 0x1c) = uVar7;
      *(undefined4 *)(param_2 + 0x20) = uVar9;
      if (2 < uVar2) {
        printk("acl filed ipv6 sip %8.8x:%8.8x:%8.8x:%8.8x, dip %8.8x:%8.8x:%8.8x:%8.8x\n",
               *(undefined4 *)(param_2 + 4),*(undefined4 *)(param_2 + 8),
               *(undefined4 *)(param_2 + 0xc),*(undefined4 *)(param_2 + 0x10),
               *(undefined4 *)(param_2 + 0x14),*(undefined4 *)(param_2 + 0x18),
               *(undefined4 *)(param_2 + 0x1c),*(undefined4 *)(param_2 + 0x20));
      }
    }
  }
  sVar1 = *(short *)(param_2 + 0x2e);
joined_r0x00011a7c:
  if (sVar1 == 2) {
    iVar4 = get_sw_port_from_devname(param_1[7],local_1c,0);
    if (iVar4 == 0) {
      __s1 = (char *)param_1[7];
      iVar4 = strcmp(__s1,"pon");
      if ((iVar4 == 0) || (iVar4 = strcmp(__s1,"ptm0"), iVar4 == 0)) {
        *(undefined1 *)(param_2 + 0x9e) = 5;
      }
      else {
        *(char *)(param_2 + 0x9e) = (char)local_1c[0];
      }
      if (2 < g_switch_debug_level) {
        printk("[sw_acl_setMtchInfo] ptSession->inputdev_name %s, p_zteHffEntry->inport %d, g_pon_work_mode[0x%x]\n"
               ,param_1[7],*(undefined1 *)(param_2 + 0x9e),g_pon_work_mode);
      }
    }
    else if (g_switch_debug_level != 0) {
      printk("iret = %d\n");
    }
  }
  return;
}

