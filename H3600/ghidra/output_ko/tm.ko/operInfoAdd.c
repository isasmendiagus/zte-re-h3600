// module: tm.ko
// function: operInfoAdd @ 0x59074
// size: 8732 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: stack */

undefined4
operInfoAdd(undefined4 *param_1,undefined4 *param_2,uint *param_3,uint *param_4,undefined4 param_5,
           undefined2 *param_6,uint *param_7,int param_8,uint param_9,uint *param_10)

{
  short sVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  int iVar8;
  uint *puVar9;
  int *piVar10;
  undefined4 *puVar11;
  uint uVar12;
  void *__s2;
  void *pvVar13;
  uint uVar14;
  byte bVar15;
  ushort uVar16;
  undefined4 *puVar17;
  void *pvVar18;
  char cVar19;
  byte bVar20;
  undefined2 uVar21;
  char *pcVar22;
  int iVar23;
  undefined4 *puVar24;
  undefined4 *puVar25;
  uint uVar26;
  uint *puVar27;
  int *piVar28;
  size_t sVar29;
  undefined4 uVar30;
  uint uVar31;
  int *piVar32;
  ushort uVar33;
  int *piVar34;
  undefined4 uVar35;
  undefined4 *puVar36;
  undefined4 uVar37;
  bool bVar38;
  undefined4 *local_ec;
  uint local_e8;
  uint local_dc;
  ushort local_cc;
  ushort local_ca;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  uint uStack_bc;
  uint local_b8;
  undefined4 local_b4;
  uint uStack_b0;
  uint local_ac;
  uint local_a8;
  uint uStack_a4;
  undefined1 auStack_a0 [124];
  
  local_c0 = CONCAT22(local_c0._2_2_,CONCAT11(local_c0._1_1_,(byte)local_c0));
  local_c4 = CONCAT13(local_c4._3_1_,
                      CONCAT12(local_c4._2_1_,CONCAT11(local_c4._1_1_,(undefined1)local_c4)));
  uVar30 = *(undefined4 *)(param_8 + 0x10);
  if (param_1 == (undefined4 *)0x0) {
    printk("ERROR: flow info is NULL\n");
    return 0xfffffff4;
  }
  if ((tmInfoListInited == '\0') && (iVar8 = operListInit(), iVar8 != 0)) {
    return 0xfffffff4;
  }
  iVar8 = opcDbSetCrtList(uVar30);
  if (iVar8 != 0) {
    return 0xfffffff4;
  }
  __memzero(auStack_a0,0x78);
  g_pktLenChged = iVar8;
  if (g_qosEn != '\0') {
    if (((*(char *)(param_6 + 4) == '\0') && (*(char *)(param_2 + 6) == '\0')) &&
       (*(char *)(param_2 + 7) == '\0')) {
      if (TM_OPC_DEBUG == 0) {
        uVar31 = 0x80000000;
      }
      else {
        uVar31 = 0x80000000;
        printk("no qos modify action\n");
      }
      goto LAB_00059134;
    }
    piVar10 = s_tmQosInfoListHead;
    if (param_7 == (uint *)0x0) {
      printk("ERROR:pp_qosInfo is NULL\n");
      goto LAB_000593b4;
    }
    do {
      if (((((char)piVar10[2] == '\x01') && (pcVar22 = (char *)piVar10[4], pcVar22 != (char *)0x0))
          && ((*(char *)((int)param_7 + 1) == pcVar22[1] &&
              (((char)*param_7 == *pcVar22 && (*(char *)((int)param_7 + 3) == pcVar22[3])))))) &&
         (*(char *)((int)param_7 + 2) == pcVar22[2])) {
        uVar31 = piVar10[3];
        goto LAB_00059c48;
      }
      piVar32 = piVar10 + 1;
      piVar10 = (int *)*piVar32;
    } while ((int *)*piVar32 != (int *)0x0);
    puVar9 = (uint *)kmem_cache_alloc(_DAT_000df0e4,0x20);
    if (puVar9 == (uint *)0x0) {
      printk("ERROR: malloc memory fail!!\n");
      goto LAB_000593b4;
    }
    __memzero(puVar9,5);
    cVar19 = l_qosAllAlloc;
    piVar10 = s_tmQosInfoListHead;
    if (s_tmQosInfoListHead[4] == 0) {
      s_tmQosInfoListHead[4] = (int)puVar9;
      uVar31 = 0;
LAB_00059c00:
      piVar32 = s_tmQosInfoListHead;
      if (cVar19 == '\0') {
        __memzero(puVar9,5);
        *puVar9 = *param_7;
        *(char *)(puVar9 + 1) = (char)param_7[1];
        *(undefined1 *)(piVar10 + 2) = 0;
        piVar10[3] = uVar31;
LAB_00059c30:
        writeQosInfoToRam_constprop_7(param_7,uVar31);
        opcDbQosEntryValidSet(uVar31,1);
LAB_00059c48:
        uVar31 = uVar31 << 0x10 | 0x80000000;
        goto LAB_00059134;
      }
    }
    else {
      piVar10 = (int *)kmem_cache_alloc(_DAT_000df0e4,0x20);
      if (piVar10 == (int *)0x0) {
        printk("ERROR:memory alloc Fail!!\n");
        kfree(puVar9);
        goto LAB_000593b4;
      }
      __memzero(piVar10,0x14);
      uVar31 = s_tmQosInfoListTail[3] + 1;
      piVar32 = s_tmQosInfoListHead;
      if (uVar31 < 0x200) {
        if (l_qosAllAlloc == '\0') {
          *piVar10 = (int)s_tmQosInfoListTail;
          piVar10[4] = (int)puVar9;
          piVar32 = s_tmQosInfoListTail + 1;
          s_tmQosInfoListTail = piVar10;
          *piVar32 = (int)piVar10;
          cVar19 = l_qosAllAlloc;
          piVar10[1] = 0;
          goto LAB_00059c00;
        }
      }
      else {
        l_qosAllAlloc = '\x01';
      }
    }
    do {
      if (((char)piVar32[2] == '\0') && (piVar32[4] != 0)) {
        __memzero(&local_c8,5);
        uVar31 = param_7[1];
        local_c8 = *param_7;
        local_c4 = CONCAT31(local_c4._1_3_,(char)uVar31);
        *(undefined1 *)(piVar32 + 2) = 0;
        puVar27 = (uint *)piVar32[4];
        *puVar27 = local_c8;
        *(char *)(puVar27 + 1) = (char)uVar31;
        uVar31 = piVar32[3];
        kfree(puVar9);
        kfree(piVar10);
        goto LAB_00059c30;
      }
      piVar28 = piVar32 + 1;
      piVar32 = (int *)*piVar28;
    } while ((int *)*piVar28 != (int *)0x0);
    if (TM_OPC_DEBUG != 0) {
      printk("exceed max qos info ram depth %d\n",0x200);
    }
    kfree(puVar9);
    kfree(piVar10);
LAB_000593b4:
    printk("ERROR:add qos info to list Fail\n");
    return 0xfffffff4;
  }
  if ((*(char *)((int)param_1 + 0x1f) != '\0') || (*(char *)((int)param_1 + 0x16) != '\0')) {
    if (param_4 == (uint *)0x0) {
      printk("ERROR:pp_natInfo is NULL\n");
      goto LAB_000599cc;
    }
    piVar10 = s_tmNatInfoListHead;
    do {
      if ((char)piVar10[2] == '\x01') {
        iVar8 = piVar10[4];
        if (iVar8 != 0) {
          iVar23 = memcmp((void *)((int)param_4 + 2),(void *)(iVar8 + 2),4);
          if ((iVar23 == 0) &&
             (iVar8 = memcmp((void *)((int)param_4 + 6),(void *)(iVar8 + 6),6), iVar8 == 0)) {
            local_dc = piVar10[3];
            goto LAB_0005916c;
          }
        }
      }
      piVar10 = (int *)piVar10[1];
    } while (piVar10 != (int *)0x0);
    puVar9 = (uint *)kmem_cache_alloc(_DAT_000df0e4,0x20);
    if (puVar9 == (uint *)0x0) {
      printk("ERROR: malloc memory fail!!\n");
      goto LAB_000599cc;
    }
    __memzero(puVar9,0x12);
    cVar19 = l_natAllAlloc;
    piVar10 = s_tmNatInfoListHead;
    if (s_tmNatInfoListHead[4] == 0) {
      s_tmNatInfoListHead[4] = (int)puVar9;
      local_dc = 0;
LAB_00059dc4:
      if (cVar19 == '\0') {
        __memzero(puVar9,0x12);
        uVar31 = param_4[1];
        uVar12 = param_4[2];
        uVar26 = param_4[3];
        *puVar9 = *param_4;
        puVar9[1] = uVar31;
        puVar9[2] = uVar12;
        puVar9[3] = uVar26;
        *(short *)(puVar9 + 4) = (short)param_4[4];
        *(undefined1 *)(piVar10 + 2) = 0;
        piVar10[3] = local_dc;
LAB_00059e18:
        local_ec = &local_c8;
        __memzero(local_ec,10);
        local_c8 = *(uint *)((int)param_4 + 6);
        uVar30 = *(undefined4 *)((int)param_4 + 2);
        local_c4._0_3_ = (int3)uVar30 << 0x10;
        local_c4._3_1_ = (byte)((uint)uVar30 >> 8);
        local_c0._0_2_ = (ushort)((uint)uVar30 >> 0x10);
        local_c4 = CONCAT22(local_c4._2_2_,*(undefined2 *)((int)param_4 + 10));
        iVar8 = pp_pm_set_next_hop_ram_info(local_dc,local_ec);
        if (iVar8 != 0) {
          printk("ERROR:writeNatInfoToRam Fail\n");
          return 0xfffffff4;
        }
        goto LAB_0005916c;
      }
    }
    else {
      piVar10 = (int *)kmem_cache_alloc(_DAT_000df0e4,0x20);
      if (piVar10 == (int *)0x0) {
        printk("ERROR:memory alloc Fail!!\n");
        kfree(puVar9);
        goto LAB_000599cc;
      }
      __memzero(piVar10,0x14);
      piVar32 = s_tmNatInfoListTail;
      local_dc = s_tmNatInfoListTail[3] + 1;
      if (local_dc < 0x200) {
        if (l_natAllAlloc == '\0') {
          *piVar10 = (int)s_tmNatInfoListTail;
          s_tmNatInfoListTail = piVar10;
          piVar10[4] = (int)puVar9;
          cVar19 = l_natAllAlloc;
          piVar32[1] = (int)piVar10;
          piVar10[1] = 0;
          goto LAB_00059dc4;
        }
      }
      else {
        l_natAllAlloc = '\x01';
      }
    }
    piVar32 = s_tmNatInfoListHead;
    do {
      if (((char)piVar32[2] == '\0') && (piVar32[4] != 0)) {
        __memzero(&local_c8,0x12);
        local_c8 = *param_4;
        local_c4 = param_4[1];
        local_c0 = param_4[2];
        uStack_bc = param_4[3];
        uVar31 = param_4[4];
        local_b8 = CONCAT22(local_b8._2_2_,(short)uVar31);
        *(undefined1 *)(piVar32 + 2) = 0;
        puVar27 = (uint *)piVar32[4];
        *puVar27 = local_c8;
        puVar27[1] = local_c4;
        puVar27[2] = local_c0;
        puVar27[3] = uStack_bc;
        *(short *)(puVar27 + 4) = (short)uVar31;
        local_dc = piVar32[3];
        kfree(puVar9);
        kfree(piVar10);
        if (local_dc == 0xffffffff) goto LAB_00059164;
        goto LAB_00059e18;
      }
      piVar32 = (int *)piVar32[1];
    } while (piVar32 != (int *)0x0);
    if (TM_OPC_DEBUG != 0) {
      printk("exceed max nat info ram depth %d\n",0x200);
    }
    kfree(puVar9);
    kfree(piVar10);
LAB_000599cc:
    printk("ERROR:add nat info to list Fail\n");
    return 0xfffffff4;
  }
LAB_00059164:
  local_dc = 0xffffffff;
LAB_0005916c:
  if (*(char *)(param_2 + 3) != '\0') {
    piVar10 = s_tmVlanInfoListHead;
    if (param_3 == (uint *)0x0) {
      printk("ERROR:pp_vlanInfo is NULL\n");
      goto LAB_00059a40;
    }
    do {
      if ((((((char)piVar10[2] == '\x01') && (iVar8 = piVar10[4], iVar8 != 0)) &&
           (*(short *)(iVar8 + 6) == *(short *)((int)param_3 + 6))) &&
          ((*(short *)(iVar8 + 8) == (short)param_3[2] &&
           (*(short *)(iVar8 + 2) == *(short *)((int)param_3 + 2))))) &&
         (*(short *)(iVar8 + 4) == (short)param_3[1])) {
        local_e8 = piVar10[3];
        goto LAB_00059448;
      }
      piVar32 = piVar10 + 1;
      piVar10 = (int *)*piVar32;
    } while ((int *)*piVar32 != (int *)0x0);
    if (l_vlanAllAlloc == '\0') {
      puVar9 = (uint *)kmem_cache_alloc(_DAT_000df0e4,0x20);
      if (puVar9 == (uint *)0x0) {
        printk("ERROR: malloc memory fail!!\n");
        goto LAB_00059a40;
      }
      __memzero(puVar9,10);
      piVar10 = s_tmVlanInfoListHead;
      if (s_tmVlanInfoListHead[4] == 0) {
        s_tmVlanInfoListHead[4] = (int)puVar9;
        local_e8 = 0;
      }
      else {
        piVar10 = (int *)kmem_cache_alloc(_DAT_000df0e4,0x20);
        if (piVar10 == (int *)0x0) {
          printk("ERROR:memory alloc Fail!!\n");
          kfree(puVar9);
          goto LAB_00059a40;
        }
        __memzero(piVar10,0x14);
        local_e8 = s_tmVlanInfoListTail[3] + 1;
        if ((0x3ff < local_e8) || (l_vlanAllAlloc != '\0')) {
          l_vlanAllAlloc = '\x01';
          piVar32 = s_tmVlanInfoListHead;
          goto LAB_000599fc;
        }
        *piVar10 = (int)s_tmVlanInfoListTail;
        piVar10[4] = (int)puVar9;
        piVar32 = s_tmVlanInfoListTail + 1;
        s_tmVlanInfoListTail = piVar10;
        *piVar32 = (int)piVar10;
        piVar10[1] = 0;
      }
      piVar32 = s_tmVlanInfoListHead;
      if (l_vlanAllAlloc == '\0') {
        __memzero(puVar9,10);
        uVar31 = param_3[1];
        *puVar9 = *param_3;
        puVar9[1] = uVar31;
        *(short *)(puVar9 + 2) = (short)param_3[2];
        *(undefined1 *)(piVar10 + 2) = 0;
        piVar10[3] = local_e8;
LAB_00059d28:
        local_ec = &local_c8;
        __memzero(local_ec,4);
        local_c8 = (uint)(byte)((*(byte *)((int)param_3 + 3) & 1) << 4 |
                               *(char *)((int)param_3 + 2) << 5) << 0x18;
        local_c8 = CONCAT22(local_c8._2_2_ | (ushort)param_3[1] & 0xfff,
                            (ushort)(byte)((*(byte *)((int)param_3 + 7) & 1) << 4 |
                                          *(char *)((int)param_3 + 6) << 5) << 8 |
                            (ushort)param_3[2] & 0xfff);
        iVar8 = pp_pm_set_vlan_modify_ram_info(local_e8,local_ec);
        if (iVar8 != 0) {
          printk("ERROR:writeVlanInfoToRam Fail\n");
          return 0xfffffff4;
        }
        goto LAB_00059448;
      }
    }
    else {
      piVar10 = (int *)0x0;
      puVar9 = (uint *)0x0;
      piVar32 = s_tmVlanInfoListHead;
    }
LAB_000599fc:
    do {
      if (((char)piVar32[2] == '\0') && (piVar32[4] != 0)) {
        __memzero(&local_c8,10);
        local_c8 = *param_3;
        local_c4 = param_3[1];
        uVar31 = param_3[2];
        local_c0 = CONCAT22(local_c0._2_2_,(short)uVar31);
        *(undefined1 *)(piVar32 + 2) = 0;
        puVar27 = (uint *)piVar32[4];
        *puVar27 = local_c8;
        puVar27[1] = local_c4;
        *(short *)(puVar27 + 2) = (short)uVar31;
        local_e8 = piVar32[3];
        kfree(puVar9,local_c4,&local_c0);
        kfree(piVar10);
        if (local_e8 != 0xffffffff) goto LAB_00059d28;
        goto LAB_00059440;
      }
      piVar28 = piVar32 + 1;
      piVar32 = (int *)*piVar28;
    } while ((int *)*piVar28 != (int *)0x0);
    printk("exceed max vlan info ram depth %d\n",0x400);
    kfree(puVar9);
    kfree(piVar10);
LAB_00059a40:
    printk("ERROR:add vlan info to list Fail\n");
    return 0xfffffff4;
  }
LAB_00059440:
  local_e8 = 0xffffffff;
LAB_00059448:
  uVar30 = param_2[4];
  if ((param_9 & 0xf03005c) == 0) goto LAB_00059464;
  uVar31 = param_9 & 8;
  if (uVar31 == 0) {
    uVar12 = 2;
  }
  else {
    uVar12 = 3;
  }
  if ((param_9 & 0x30000) == 0) {
    if ((param_9 & 0x3000000) != 0) {
      uVar12 = uVar12 + 3;
    }
    if ((param_9 & 0xc000000) != 0) {
      uVar12 = uVar12 + 3;
    }
  }
  else {
    if ((param_9 & 0x3000000) == 0) {
      uVar12 = uVar12 + 3;
    }
    else {
      uVar12 = uVar12 + 4;
    }
    if ((param_9 & 0xc000000) != 0) {
      uVar12 = uVar12 + 1;
    }
  }
  if ((param_9 & 4) == 0) goto switchD_00059ef0_caseD_0;
  switch(uVar30) {
  case 0:
  case 0xe:
    goto switchD_00059ef0_caseD_0;
  case 1:
  case 3:
  case 4:
  case 5:
  case 7:
  case 8:
  case 9:
  case 10:
    uVar12 = uVar12 + 1;
    break;
  case 2:
  case 0xb:
  case 0xc:
  case 0xd:
    uVar12 = uVar12 + 2;
    break;
  case 6:
    uVar12 = uVar12 + 3;
    break;
  default:
    printk("error vlan oper %d\n",uVar30);
switchD_00059ef0_caseD_0:
    if (uVar12 != 2) goto LAB_0005a0d8;
LAB_00059464:
    uVar21 = 0;
    iVar8 = 0;
LAB_0005946c:
    *(undefined2 *)((int)param_2 + 0x1e) = uVar21;
    *(undefined2 *)(param_2 + 8) = 0xffff;
    *(short *)(param_2 + 5) = (short)local_e8;
    goto joined_r0x0005ac38;
  }
  if (0xe < uVar12) {
    printk("ERROR:(%s:%d)","tm_acl_v2.c",0x1472);
    printk("l_depth invalid parameter\n");
    goto LAB_0005a2d8;
  }
LAB_0005a0d8:
  piVar10 = (int *)kmem_cache_alloc(_DAT_000df0f4,0x20);
  if (piVar10 == (int *)0x0) {
    printk("ERROR:(%s:%d)","tm_acl_v2.c",0x147b);
    printk("malloc memory fail!!\n");
    goto LAB_0005a2d8;
  }
  __s2 = (void *)kmem_cache_alloc(___unregister_chrdev,0x20);
  if (__s2 == (void *)0x0) {
    printk("ERROR:(%s:%d)","tm_acl_v2.c",0x1483);
    printk("malloc memory fail!!\n");
    kfree(piVar10);
    goto LAB_0005a2d8;
  }
  __memzero(&local_c8,0x24);
  __memzero(piVar10,0x188);
  __memzero(__s2,0xa8);
  piVar10[6] = (int)__s2;
  *(undefined2 *)((int)__s2 + 8) = 6;
  *(undefined4 *)((int)__s2 + 4) = 2;
  pvVar18 = __s2;
  piVar32 = piVar10;
  if ((param_9 & 4) == 0) {
    if (uVar31 != 0) {
      *(undefined4 *)((int)__s2 + 0x10) = 5;
      *(undefined2 *)((int)__s2 + 0x14) = *param_6;
      piVar10[7] = (int)piVar10;
      piVar10[8] = 0;
      piVar10[0xd] = (int)__s2 + 0xc;
      goto LAB_0005a40c;
    }
    goto LAB_0005a418;
  }
  local_cc = 0;
  local_ca = 0;
  if (*(char *)(param_6 + 4) == '\0') {
    uVar26 = 0x1000;
  }
  else {
    uVar26 = 0x800;
  }
  if (*(char *)((int)param_6 + 9) == '\0') {
    uVar26 = uVar26 | 0x400;
  }
  else {
    uVar26 = uVar26 | 0x200;
  }
  if (*(char *)((int)param_6 + 7) == '\0') {
    uVar26 = uVar26 | 0x100;
  }
  else {
    uVar26 = uVar26 | 0x80;
  }
  if (*(char *)(param_6 + 6) == '\0') {
    uVar33 = 0x1000;
  }
  else {
    uVar33 = 0x800;
  }
  if (*(char *)((int)param_6 + 0xd) == '\0') {
    uVar33 = uVar33 | 0x400;
  }
  else {
    uVar33 = uVar33 | 0x200;
  }
  if (*(char *)((int)param_6 + 0xb) == '\0') {
    uVar33 = uVar33 | 0x100;
  }
  else {
    uVar33 = uVar33 | 0x80;
  }
  local_c4 = 1;
  local_b8 = 1;
  local_ac = 1;
  local_c0 = local_c0 & 0xffff0000;
  local_b4 = local_b4 & 0xffff0000;
  local_a8 = local_a8 & 0xffff0000;
  getTpidAddr(param_6[1],&local_cc);
  getTpidAddr(param_6[2],&local_ca);
  if (*(char *)(param_6 + 5) == '\0') {
    uVar26 = uVar26 | 0x4000;
  }
  else {
    uVar26 = uVar26 | 0x2000 | (local_cc & 7) << 4;
  }
  if (*(char *)(param_6 + 7) == '\0') {
    uVar33 = uVar33 | 0x4000;
  }
  else {
    uVar33 = uVar33 | 0x2000 | (local_ca & 7) << 4;
  }
  switch(uVar30) {
  case 0:
  case 0xe:
    goto switchD_0005a264_caseD_0;
  case 1:
  case 7:
    uVar30 = 6;
    g_pktLenChged = g_pktLenChged + 4;
    bVar2 = 6;
    local_c0._0_1_ = (byte)((local_cc & 7) << 4) | 0x80;
    uVar14 = 1;
    local_c0._0_2_ = CONCAT11(0xaa,(byte)local_c0);
    break;
  case 2:
    g_pktLenChged = g_pktLenChged + 8;
    bVar2 = 6;
    sVar1 = (local_cc & 7) << 4;
    local_c0._0_1_ = (byte)sVar1 | 0x80;
    uVar30 = 6;
    local_c0._0_2_ = CONCAT11(0xaa,(byte)local_c0);
    local_b4 = CONCAT22(local_b4._2_2_,sVar1) | 0x2a80;
    uVar14 = 2;
    local_b8 = 6;
    break;
  case 3:
    uVar30 = 6;
    uVar14 = 1;
    uVar33 = (local_cc & 7) << 4;
    uVar16 = uVar33 | 0xaa80;
    local_c0._0_1_ = (byte)uVar16;
    local_c0._0_2_ = CONCAT11(0xaa,(byte)local_c0);
    if (*(char *)(param_6 + 3) != '\0') {
      uVar16 = uVar33 | 0xa280;
    }
    bVar2 = 6;
    g_pktLenChged = g_pktLenChged + 4;
    if (*(char *)(param_6 + 3) != '\0') {
      local_c0._0_2_ = uVar16;
    }
    break;
  case 4:
  case 8:
    uVar14 = 1;
    uVar30 = 9;
    bVar2 = 9;
    g_pktLenChged = g_pktLenChged + -4;
    local_c0 = (uint)local_c0._2_2_ << 0x10;
    break;
  case 5:
    uVar30 = 7;
    bVar2 = 7;
    local_c0 = CONCAT22(local_c0._2_2_,~((ushort)~(ushort)((uVar26 << 0x11) >> 0x10) >> 1));
    uVar14 = 1;
    break;
  case 6:
    local_b4 = CONCAT22(local_b4._2_2_,~((ushort)~(ushort)((uVar26 << 0x11) >> 0x10) >> 1));
    bVar2 = 6;
    uVar30 = 6;
    uVar33 = (local_ca & 7) << 4;
    local_c0._0_1_ = (byte)uVar33 | 0x80;
    if (*(char *)(param_6 + 3) != '\0') {
      uVar33 = uVar33 | 0x2280;
    }
    local_c0._0_2_ = CONCAT11(0x2a,(byte)local_c0);
    uVar14 = 2;
    if (*(char *)(param_6 + 3) != '\0') {
      local_c0._0_2_ = uVar33;
    }
    local_b8 = 7;
    g_pktLenChged = g_pktLenChged + 4;
    break;
  case 9:
    uVar30 = 7;
    uVar14 = 1;
    *(undefined2 *)((int)__s2 + 8) = 8;
    local_c0 = CONCAT22(local_c0._2_2_,uVar33);
    bVar2 = 7;
    break;
  case 10:
    uVar30 = 7;
    bVar2 = 7;
    local_c0 = CONCAT22(local_c0._2_2_,~((ushort)~(ushort)((uVar26 << 0x11) >> 0x10) >> 1));
    if (*(char *)(param_6 + 3) == '\0') {
      uVar14 = 1;
    }
    else {
      uVar14 = 1;
      local_c0 = CONCAT22(local_c0._2_2_,
                          ~((ushort)~(ushort)(((uVar26 & 0xffffe7ff) << 0x11) >> 0x10) >> 1));
    }
    break;
  case 0xb:
    uVar30 = 9;
    bVar2 = 9;
    g_pktLenChged = g_pktLenChged + -8;
    local_b8 = 9;
    uVar14 = 2;
    local_c0 = (uint)local_c0._2_2_ << 0x10;
    local_b4 = (uint)local_b4._2_2_ << 0x10;
    break;
  case 0xc:
    local_b4 = CONCAT22(local_b4._2_2_,uVar33);
    uVar30 = 9;
    g_pktLenChged = g_pktLenChged + -4;
    bVar2 = 9;
    uVar14 = 2;
    local_c0 = (uint)local_c0._2_2_ << 0x10;
    local_b8 = 7;
    break;
  case 0xd:
    uVar30 = 7;
    local_b4 = CONCAT22(local_b4._2_2_,uVar33);
    local_c0 = CONCAT22(local_c0._2_2_,~((ushort)~(ushort)((uVar26 << 0x11) >> 0x10) >> 1));
    bVar2 = 7;
    uVar14 = 2;
    local_b8 = 7;
    break;
  default:
    printk("error vlan oper %d\n",0);
    goto switchD_0005a264_caseD_0;
  }
  local_c4 = (uint)bVar2;
  uVar26 = 0;
  puVar11 = &local_c8;
  pvVar13 = __s2;
  piVar28 = piVar10;
  bVar38 = false;
  while( true ) {
    pvVar18 = (void *)((int)pvVar13 + 0xc);
    *(undefined4 *)((int)pvVar13 + 0x10) = uVar30;
    piVar32 = piVar28 + 7;
    uVar26 = uVar26 + 1;
    *(undefined2 *)((int)pvVar13 + 0x14) = *(undefined2 *)(puVar11 + 2);
    piVar28[0xd] = (int)pvVar18;
    piVar28[7] = (int)piVar28;
    if (bVar38) {
      piVar28[1] = (int)piVar32;
    }
    else {
      piVar28[2] = (int)piVar32;
    }
    piVar28[8] = 0;
    if (uVar14 <= uVar26) break;
    uVar30 = puVar11[4];
    puVar11 = puVar11 + 3;
    pvVar13 = pvVar18;
    piVar28 = piVar32;
    bVar38 = true;
  }
  if (uVar31 == 0) {
    uVar31 = 1;
  }
  else {
    *(undefined4 *)((int)pvVar13 + 0x1c) = 5;
    *(undefined2 *)((int)pvVar13 + 0x20) = *param_6;
    uVar31 = 1;
    piVar28[0x14] = (int)pvVar13 + 0x18;
    piVar28[8] = (int)(piVar28 + 0xe);
    piVar28[0xe] = (int)piVar32;
    piVar28[0xf] = 0;
    pvVar18 = (void *)((int)pvVar13 + 0x18);
    piVar32 = piVar28 + 0xe;
  }
LAB_0005a418:
  uVar26 = param_9 & 0x20000;
  if (uVar26 != 0) {
    piVar34 = piVar32 + 0x15;
    uVar30 = 2;
    local_c4 = 2;
    local_a8 = local_a8 & 0xffff0000;
    local_c0 = CONCAT22((short)(local_c0 >> 0x10),0x8000);
    local_b4 = CONCAT22(local_b4._2_2_,*param_6);
    local_b8 = 5;
    local_ac = 10;
    pvVar13 = pvVar18;
    piVar28 = piVar32;
    puVar11 = &local_c8;
    while( true ) {
      bVar38 = uVar31 == 0;
      *(undefined4 *)((int)pvVar13 + 0x10) = uVar30;
      piVar32 = piVar28 + 7;
      *(undefined2 *)((int)pvVar13 + 0x14) = *(undefined2 *)(puVar11 + 2);
      uVar31 = 1;
      piVar28[0xd] = (int)pvVar13 + 0xc;
      piVar28[7] = (int)piVar28;
      if (bVar38) {
        piVar28[2] = (int)piVar32;
      }
      else {
        piVar28[1] = (int)piVar32;
      }
      piVar28[8] = 0;
      if (piVar32 == piVar34) break;
      uVar30 = puVar11[4];
      pvVar13 = (void *)((int)pvVar13 + 0xc);
      piVar28 = piVar32;
      puVar11 = puVar11 + 3;
    }
    pvVar18 = (void *)((int)pvVar18 + 0x24);
    uVar31 = 1;
    g_pktLenChged = g_pktLenChged + 8;
  }
  uVar14 = param_9 & 0x10000;
  if (uVar14 != 0) {
    piVar34 = piVar32 + 0x15;
    uVar30 = 2;
    local_c4 = 2;
    local_c0 = CONCAT22((short)(local_c0 >> 0x10),0x8000);
    local_b4 = CONCAT22(local_b4._2_2_,*param_6);
    local_b8 = 5;
    local_ac = 3;
    local_a8 = CONCAT22(local_a8._2_2_,4);
    pvVar13 = pvVar18;
    piVar28 = piVar32;
    puVar11 = &local_c8;
    while( true ) {
      bVar38 = uVar31 == 0;
      *(undefined4 *)((int)pvVar13 + 0x10) = uVar30;
      piVar32 = piVar28 + 7;
      *(undefined2 *)((int)pvVar13 + 0x14) = *(undefined2 *)(puVar11 + 2);
      uVar31 = 1;
      piVar28[0xd] = (int)pvVar13 + 0xc;
      piVar28[7] = (int)piVar28;
      if (bVar38) {
        piVar28[2] = (int)piVar32;
      }
      else {
        piVar28[1] = (int)piVar32;
      }
      piVar28[8] = 0;
      if (piVar32 == piVar34) break;
      uVar30 = puVar11[4];
      pvVar13 = (void *)((int)pvVar13 + 0xc);
      piVar28 = piVar32;
      puVar11 = puVar11 + 3;
    }
    pvVar18 = (void *)((int)pvVar18 + 0x24);
    uVar31 = 1;
    g_pktLenChged = g_pktLenChged + -8;
  }
  if ((param_9 & 0x1000000) == 0) {
    iVar8 = 3;
  }
  else {
    if (uVar26 == 0) {
      iVar8 = 3;
      uVar30 = 2;
      bVar2 = 2;
      local_a8 = CONCAT22(local_a8._2_2_,(short)g_dslite_sel);
      local_b4 = CONCAT22(local_b4._2_2_,*param_6);
      local_c0._0_2_ = 0x8000;
      local_b8 = 5;
      local_ac = 0xb;
    }
    else {
      iVar8 = 1;
      uVar30 = 0xb;
      bVar2 = 0xb;
      local_c0._0_2_ = (short)g_dslite_sel;
    }
    local_c4 = (uint)bVar2;
    piVar34 = piVar32 + iVar8 * 7;
    pvVar13 = pvVar18;
    piVar28 = piVar32;
    puVar11 = &local_c8;
    while( true ) {
      bVar38 = uVar31 == 0;
      *(undefined4 *)((int)pvVar13 + 0x10) = uVar30;
      piVar32 = piVar28 + 7;
      *(undefined2 *)((int)pvVar13 + 0x14) = *(undefined2 *)(puVar11 + 2);
      uVar31 = 1;
      piVar28[0xd] = (int)pvVar13 + 0xc;
      piVar28[7] = (int)piVar28;
      if (bVar38) {
        piVar28[2] = (int)piVar32;
      }
      else {
        piVar28[1] = (int)piVar32;
      }
      piVar28[8] = 0;
      if (piVar32 == piVar34) break;
      uVar30 = puVar11[4];
      pvVar13 = (void *)((int)pvVar13 + 0xc);
      piVar28 = piVar32;
      puVar11 = puVar11 + 3;
    }
    pvVar18 = (void *)((int)pvVar18 + iVar8 * 0xc);
    uVar31 = 1;
    g_pktLenChged = g_pktLenChged + 0x28;
    g_dsliteSet = 1;
  }
  if ((param_9 & 0x2000000) != 0) {
    if (uVar14 == 0) {
      uVar30 = 2;
      bVar2 = 2;
      local_c0 = CONCAT22(local_c0._2_2_,0x8000);
      local_b4 = CONCAT22(local_b4._2_2_,*param_6);
      local_b8 = 5;
      local_ac = 3;
      local_a8 = CONCAT22(local_a8._2_2_,0x14);
    }
    else {
      iVar8 = 1;
      uVar30 = 3;
      bVar2 = 3;
      local_c0 = CONCAT22(local_c0._2_2_,0x14);
    }
    local_c4 = (uint)bVar2;
    piVar34 = piVar32 + iVar8 * 7;
    pvVar13 = pvVar18;
    piVar28 = piVar32;
    puVar11 = &local_c8;
    while( true ) {
      bVar38 = uVar31 == 0;
      *(undefined4 *)((int)pvVar13 + 0x10) = uVar30;
      piVar32 = piVar28 + 7;
      *(undefined2 *)((int)pvVar13 + 0x14) = *(undefined2 *)(puVar11 + 2);
      uVar31 = 1;
      piVar28[0xd] = (int)pvVar13 + 0xc;
      piVar28[7] = (int)piVar28;
      if (bVar38) {
        piVar28[2] = (int)piVar32;
      }
      else {
        piVar28[1] = (int)piVar32;
      }
      piVar28[8] = 0;
      if (piVar32 == piVar34) break;
      uVar30 = puVar11[4];
      pvVar13 = (void *)((int)pvVar13 + 0xc);
      piVar28 = piVar32;
      puVar11 = puVar11 + 3;
    }
    uVar31 = 1;
    pvVar18 = (void *)((int)pvVar18 + iVar8 * 0xc);
    g_pktLenChged = g_pktLenChged + -0x28;
    g_dsliteDel = 1;
  }
  if ((param_9 & 0x4000000) == 0) {
    iVar8 = 3;
  }
  else {
    if (uVar26 == 0) {
      uVar30 = 2;
      bVar2 = 2;
      local_a8 = CONCAT22(local_a8._2_2_,(short)g_v6rd_sel);
      local_b4 = CONCAT22(local_b4._2_2_,*param_6);
      iVar8 = 3;
      local_c0._0_2_ = 0x8000;
      local_b8 = 5;
      local_ac = 0xc;
    }
    else {
      iVar8 = 1;
      uVar30 = 0xc;
      bVar2 = 0xc;
      local_c0._0_2_ = (short)g_v6rd_sel;
    }
    local_c4 = (uint)bVar2;
    piVar34 = piVar32 + iVar8 * 7;
    piVar28 = piVar32;
    pvVar13 = pvVar18;
    puVar11 = &local_c8;
    while( true ) {
      bVar38 = uVar31 == 0;
      *(undefined4 *)((int)pvVar13 + 0x10) = uVar30;
      piVar32 = piVar28 + 7;
      *(undefined2 *)((int)pvVar13 + 0x14) = *(undefined2 *)(puVar11 + 2);
      uVar31 = 1;
      piVar28[0xd] = (int)pvVar13 + 0xc;
      piVar28[7] = (int)piVar28;
      if (bVar38) {
        piVar28[2] = (int)piVar32;
      }
      else {
        piVar28[1] = (int)piVar32;
      }
      piVar28[8] = 0;
      if (piVar32 == piVar34) break;
      uVar30 = puVar11[4];
      piVar28 = piVar32;
      pvVar13 = (void *)((int)pvVar13 + 0xc);
      puVar11 = puVar11 + 3;
    }
    pvVar18 = (void *)((int)pvVar18 + iVar8 * 0xc);
    uVar31 = 1;
    g_pktLenChged = g_pktLenChged + 0x14;
    g_v6rdSet = 1;
  }
  if ((param_9 & 0x8000000) == 0) {
    *(undefined2 *)((int)pvVar18 + 0x14) = 0;
    *(undefined4 *)((int)pvVar18 + 0x10) = 1;
    piVar28 = piVar32 + 7;
    piVar32[0xd] = (int)pvVar18 + 0xc;
    piVar32[7] = (int)piVar32;
    if (uVar31 != 0) goto LAB_0005ab40;
    piVar32[2] = (int)piVar28;
  }
  else {
    if (uVar14 == 0) {
      uVar30 = 2;
      bVar2 = 2;
      local_c0 = CONCAT22(local_c0._2_2_,0x8000);
      local_b4 = CONCAT22(local_b4._2_2_,*param_6);
      local_b8 = 5;
      local_ac = 3;
      local_a8 = CONCAT22(local_a8._2_2_,10);
    }
    else {
      iVar8 = 1;
      uVar30 = 3;
      bVar2 = 3;
      local_c0 = CONCAT22(local_c0._2_2_,10);
    }
    local_c4 = (uint)bVar2;
    piVar34 = piVar32 + iVar8 * 7;
    puVar11 = &local_c8;
    pvVar13 = pvVar18;
    while( true ) {
      bVar38 = uVar31 == 0;
      *(undefined4 *)((int)pvVar13 + 0x10) = uVar30;
      piVar28 = piVar32 + 7;
      *(undefined2 *)((int)pvVar13 + 0x14) = *(undefined2 *)(puVar11 + 2);
      uVar31 = 1;
      piVar32[0xd] = (int)pvVar13 + 0xc;
      piVar32[7] = (int)piVar32;
      if (bVar38) {
        piVar32[2] = (int)piVar28;
      }
      else {
        piVar32[1] = (int)piVar28;
      }
      piVar32[8] = 0;
      if (piVar28 == piVar34) break;
      uVar30 = puVar11[4];
      piVar32 = piVar28;
      puVar11 = puVar11 + 3;
      pvVar13 = (void *)((int)pvVar13 + 0xc);
    }
    g_pktLenChged = g_pktLenChged + -0x14;
    *(undefined4 *)((int)pvVar18 + iVar8 * 0xc + 0x10) = 1;
    g_v6rdDel = 1;
    piVar28 = piVar34 + 7;
    *(undefined2 *)((int)pvVar18 + iVar8 * 0xc + 0x14) = 0;
    piVar34[0xd] = (int)pvVar18 + iVar8 * 0xc + 0xc;
    piVar34[7] = (int)piVar34;
    piVar32 = piVar34;
LAB_0005ab40:
    piVar32[1] = (int)piVar28;
  }
  if (*(int *)(s_tmCmdInfoListHead + 0x18) != 0) {
    iVar8 = s_tmCmdInfoListHead;
    do {
      while ((*(char *)(iVar8 + 0x14) != '\x01' || (*(uint *)(iVar8 + 0xc) != uVar12))) {
        iVar8 = *(int *)(iVar8 + 4);
        if (iVar8 == 0) goto LAB_0005abc4;
      }
      pvVar18 = *(void **)(iVar8 + 0x18);
      iVar23 = memcmp(pvVar18,__s2,uVar12 * 0xc);
      if (iVar23 == 0) {
        iVar8 = *(int *)(iVar8 + 0x10);
        kfree(__s2);
        kfree(piVar10);
        uVar21 = (undefined2)iVar8;
        goto LAB_0005946c;
      }
      iVar8 = *(int *)(iVar8 + 4);
      if (iVar8 == 0) goto LAB_0005abc4;
    } while (pvVar18 != (void *)0x0);
  }
  printk("cmd list error!!\n");
LAB_0005abc4:
  piVar28 = s_tmCmdInfoListTail;
  if (g_direction < 2) {
    iVar23 = s_tmCmdInfoListTail[4];
    iVar8 = iVar23 + 0xe;
    piVar10[4] = iVar8;
    if (iVar23 + 0x1cU < 0x2000) {
      if (l_cmdAllAlloc == '\0') {
        piVar32[8] = 0;
        piVar10[3] = uVar12;
        piVar10[1] = 0;
        *piVar10 = (int)piVar28;
        piVar28[1] = (int)piVar10;
        iVar8 = piVar10[4];
        s_tmCmdInfoListTail = piVar10;
        *(undefined1 *)(piVar10 + 5) = 0;
        goto LAB_0005ad18;
      }
    }
    else {
LAB_0005ad18:
      if ((iVar8 + 0xeU < 0x2000) || (1 < g_direction)) goto LAB_0005abe0;
      l_cmdAllAlloc = '\x01';
    }
  }
  else {
    iVar8 = piVar10[4];
LAB_0005abe0:
    if (l_cmdAllAlloc == '\0') {
      memcpy(auStack_a0,__s2,uVar12 * 0xc);
LAB_0005ac00:
      if ((0 < iVar8) &&
         (iVar23 = writeCmdInfoToRam_constprop_8(auStack_a0,uVar12,iVar8), iVar23 != 0)) {
        printk("ERROR:writeCmdInfoToRam Fail\n");
        return 0xfffffff4;
      }
      *(short *)((int)param_2 + 0x1e) = (short)iVar8;
      *(undefined2 *)(param_2 + 8) = 0xffff;
      *(short *)(param_2 + 5) = (short)local_e8;
joined_r0x0005ac38:
      piVar10 = s_tmSubRamInfoListHead;
      if (param_2 == (undefined4 *)0x0) {
        printk("ERROR:add subram info is NULL\n");
        goto LAB_000598ec;
      }
      do {
        if ((((((char)piVar10[2] == '\x01') && (iVar23 = piVar10[4], iVar23 != 0)) &&
             (*(char *)(param_2 + 2) == *(char *)(iVar23 + 8))) &&
            ((((param_2[1] & 0xffffff00) == (*(uint *)(iVar23 + 4) & 0xffffff00) &&
              (*(short *)(iVar23 + 0x14) == (short)local_e8)) &&
             (((param_2[6] & 0xffff00ff) == (*(uint *)(iVar23 + 0x18) & 0xffff00ff) &&
              ((param_2[7] == *(int *)(iVar23 + 0x1c) &&
               (*(char *)((int)param_2 + 9) == *(char *)(iVar23 + 9))))))))) &&
           (*(short *)(iVar23 + 0x20) == -1)) {
          uVar33 = *(ushort *)(iVar23 + 2);
          *(undefined2 *)((int)param_1 + 0x1a) = (undefined2)local_dc;
          *(ushort *)(param_1 + 5) = uVar33;
          goto LAB_0005954c;
        }
        piVar32 = piVar10 + 1;
        piVar10 = (int *)*piVar32;
      } while ((int *)*piVar32 != (int *)0x0);
      puVar11 = (undefined4 *)kmem_cache_alloc(_DAT_000df0e8,0x20);
      if (puVar11 == (undefined4 *)0x0) {
        printk("ERROR: malloc memory fail!!\n");
        goto LAB_000598ec;
      }
      __memzero(puVar11,0x24);
      piVar10 = s_tmSubRamInfoListHead;
      if (s_tmSubRamInfoListHead[4] == 0) {
        s_tmSubRamInfoListHead[4] = (int)puVar11;
        uVar31 = 0;
        cVar19 = l_subRamAllAlloc;
LAB_00059a68:
        piVar28 = s_tmSubRamInfoListHead;
        if (cVar19 == '\0') {
          __memzero(puVar11,0x24);
          puVar36 = puVar11;
          puVar24 = param_2;
          do {
            puVar25 = puVar24 + 4;
            uVar37 = puVar24[1];
            puVar17 = puVar36 + 4;
            uVar35 = puVar24[2];
            uVar30 = puVar24[3];
            *puVar36 = *puVar24;
            puVar36[1] = uVar37;
            puVar36[2] = uVar35;
            puVar36[3] = uVar30;
            puVar36 = puVar17;
            puVar24 = puVar25;
          } while (puVar25 != param_2 + 8);
          *puVar17 = *puVar25;
          *(undefined1 *)(piVar10 + 2) = 0;
          *(short *)((int)puVar11 + 2) = (short)uVar31;
          piVar10[3] = uVar31;
          uVar33 = *(ushort *)((int)puVar11 + 2);
LAB_00059adc:
          *(ushort *)((int)param_2 + 2) = uVar33;
          if (param_2 == (undefined4 *)0x0) {
LAB_00059bdc:
            printk("ERROR:writeSubRamInfoToRam Fail\n");
            return 0xfffffff4;
          }
          __memzero(&local_c8,8);
          uVar12 = local_c4;
          local_c8 = CONCAT13(*(char *)(param_2 + 5) << 2,(undefined3)local_c8);
          uVar31 = local_c8 & 0xfc001fff;
          uVar26 = uVar31 | (*(ushort *)((int)param_2 + 0x1e) & 0x1fff) << 0xd;
          bVar2 = (*(byte *)((int)param_2 + 6) & 1) << 4;
          bVar7 = (byte)(uVar26 >> 8);
          bVar3 = (*(byte *)((int)param_2 + 7) & 1) << 3;
          bVar6 = *(byte *)(param_2 + 6);
          sVar1 = (*(ushort *)(param_2 + 8) & 0x1ff) << 4;
          local_c4._1_1_ =
               local_c4._1_1_ & 0xc0 | (*(byte *)((int)param_2 + 9) & 1) << 5 |
               (byte)((ushort)sVar1 >> 8);
          bVar4 = (*(byte *)((int)param_2 + 5) & 1) << 2;
          bVar5 = (*(byte *)(param_2 + 2) & 1) << 1;
          bVar20 = bVar7 & 0xe1 | bVar2 | bVar3 | bVar4 | bVar5;
          bVar15 = (byte)sVar1 | (byte)(((uint)*(ushort *)(param_2 + 5) << 0x16) >> 0x1c);
          local_c8._2_2_ = (ushort)(uVar26 >> 0x10);
          local_c8._0_1_ = (undefined1)uVar31;
          local_c4 = CONCAT31(CONCAT21((short)(uVar12 >> 0x10),local_c4._1_1_),bVar15);
          if (bVar6 != 0) {
            bVar15 = (byte)*(undefined2 *)((int)param_2 + 0x1a);
            bVar20 = bVar7 & 0xe0 | bVar2 | bVar3 | bVar4 | bVar5 | bVar6 & 1;
          }
          local_c8 = CONCAT22(local_c8._2_2_,CONCAT11(bVar20,(undefined1)local_c8));
          if (bVar6 != 0) {
            local_c8 = CONCAT31(local_c8._1_3_,bVar15);
          }
          if (*(char *)(param_2 + 7) != '\0') {
            local_c8 = CONCAT31((int3)(local_c8 >> 8),*(undefined1 *)((int)param_2 + 0x1d)) | 0x100;
          }
          iVar23 = pp_pm_set_sub_ram_info(uVar33,&local_c8);
          if (iVar23 != 0) goto LAB_00059bdc;
          *(ushort *)(param_1 + 5) = uVar33;
          *(undefined2 *)((int)param_1 + 0x1a) = (undefined2)local_dc;
LAB_0005954c:
          puVar11 = (undefined4 *)kmem_cache_alloc(_DAT_000df0e8,0x20);
          if (puVar11 == (undefined4 *)0x0) {
            printk("ERROR: malloc memory fail!!\n");
LAB_0005a714:
            iVar8 = __printk_ratelimit("operInfoAdd");
            if (iVar8 != 0) {
              printk("ERROR:add flow info to list Fail\n");
              return 0xfffffff4;
            }
            return 0xfffffff4;
          }
          __memzero(puVar11,0x28);
          piVar10 = s_tmFlowInfoListHead;
          if (s_tmFlowInfoListHead[4] == 0) {
            s_tmFlowInfoListHead[4] = (int)puVar11;
            uVar31 = 0;
            cVar19 = l_flowAllAlloc_u;
LAB_000595ec:
            if (cVar19 != '\0') {
LAB_0005a76c:
              piVar32 = s_tmFlowInfoListHead;
              if (g_direction == 0) goto LAB_0005a6cc;
            }
LAB_000595f4:
            if (l_flowAllAlloc_d != '\0') goto LAB_00059604;
          }
          else {
            piVar10 = (int *)kmem_cache_alloc(_DAT_000df0e4,0x20);
            if (piVar10 == (int *)0x0) {
              printk("ERROR:memory alloc Fail!!\n");
              kfree(puVar11);
              goto LAB_0005a714;
            }
            __memzero(piVar10,0x14);
            if (g_direction == 0) {
              uVar31 = *(int *)(s_tmFlowInfoListTail_u[4] + 4) + 1;
              if (0x7fff < uVar31) {
                l_flowAllAlloc_u = '\x01';
                piVar32 = s_tmFlowInfoListHead;
                goto LAB_0005a6cc;
              }
              if (l_flowAllAlloc_u == '\0') {
                *piVar10 = (int)s_tmFlowInfoListTail_u;
                piVar10[4] = (int)puVar11;
                piVar32 = s_tmFlowInfoListTail_u + 1;
                s_tmFlowInfoListTail_u = piVar10;
                *piVar32 = (int)piVar10;
                cVar19 = l_flowAllAlloc_u;
                piVar10[1] = 0;
                goto LAB_000595ec;
              }
              goto LAB_0005a76c;
            }
            uVar31 = *(int *)(s_tmFlowInfoListTail_d[4] + 4) + 1;
            if (uVar31 < 0x8000) {
              if (l_flowAllAlloc_d == '\0') {
                *piVar10 = (int)s_tmFlowInfoListTail_d;
                piVar10[4] = (int)puVar11;
                piVar32 = s_tmFlowInfoListTail_d + 1;
                s_tmFlowInfoListTail_d = piVar10;
                *piVar32 = (int)piVar10;
                piVar10[1] = 0;
                cVar19 = l_flowAllAlloc_u;
                goto LAB_000595ec;
              }
              if (l_flowAllAlloc_u != '\0') goto LAB_0005a76c;
            }
            else {
              l_flowAllAlloc_d = '\x01';
              if (l_flowAllAlloc_u != '\0') goto LAB_000595f4;
            }
LAB_00059604:
            piVar32 = s_tmFlowInfoListHead;
            if (g_direction == 1) {
LAB_0005a6cc:
              if (((char)piVar32[2] != '\0') || (piVar32[4] == 0)) goto LAB_0005a6e4;
              uVar31 = *(uint *)(piVar32[4] + 4);
              __memzero(&local_c8,0x28);
              puVar36 = &local_c8;
              puVar24 = param_1;
              do {
                puVar25 = puVar24;
                puVar17 = puVar36;
                puVar24 = puVar25 + 4;
                uVar30 = puVar25[1];
                uVar35 = puVar25[2];
                uVar37 = puVar25[3];
                *puVar17 = *puVar25;
                puVar17[1] = uVar30;
                puVar17[2] = uVar35;
                puVar17[3] = uVar37;
                puVar36 = puVar17 + 4;
              } while (puVar24 != param_1 + 8);
              uVar30 = puVar25[5];
              puVar17[4] = *puVar24;
              puVar17[5] = uVar30;
              *(undefined1 *)(piVar32 + 2) = 0;
              piVar32[3] = uVar31;
              puVar9 = (uint *)piVar32[4];
              *puVar9 = local_c8;
              puVar9[1] = uVar31;
              puVar9[2] = local_c0;
              puVar9[3] = uStack_bc;
              puVar9[4] = local_b8;
              puVar9[5] = local_b4;
              puVar9[6] = uStack_b0;
              puVar9[7] = local_ac;
              puVar9[8] = local_a8;
              puVar9[9] = uStack_a4;
              param_1[1] = uVar31;
              local_c4 = uVar31;
              kfree(puVar11);
              kfree(piVar10);
              uVar31 = param_1[1];
              goto LAB_00059680;
            }
          }
          __memzero(puVar11,0x28);
          puVar36 = puVar11;
          puVar24 = param_1;
          do {
            puVar25 = puVar24;
            puVar17 = puVar36;
            puVar24 = puVar25 + 4;
            uVar37 = puVar25[1];
            uVar35 = puVar25[2];
            uVar30 = puVar25[3];
            *puVar17 = *puVar25;
            puVar17[1] = uVar37;
            puVar17[2] = uVar35;
            puVar17[3] = uVar30;
            puVar36 = puVar17 + 4;
          } while (puVar24 != param_1 + 8);
          uVar30 = puVar25[5];
          puVar17[4] = *puVar24;
          puVar17[5] = uVar30;
          *(undefined1 *)(piVar10 + 2) = 0;
          puVar11[1] = uVar31;
          piVar10[3] = uVar31;
          uVar31 = puVar11[1];
          param_1[1] = uVar31;
LAB_00059680:
          if (uVar31 != 0xffffffff) {
            __memzero(&local_c8,0xc);
            uVar12 = param_1[4];
            local_c8 = (uVar12 >> 0x10) << 0x12;
            iVar23 = (uVar12 & 0xffff) << 2;
            local_c8._1_3_ = (uint3)(local_c8 >> 8) | (uint3)((uint)iVar23 >> 8);
            sVar1 = (*(ushort *)((int)param_1 + 0x1a) & 0x1ff) << 2;
            local_c4._3_1_ = *(char *)(param_1 + 5) << 3 | (byte)((ushort)sVar1 >> 8);
            local_c8 = CONCAT31(local_c8._1_3_,
                                (byte)iVar23 | (*(byte *)((int)param_1 + 0x17) & 1) << 1 |
                                *(byte *)((int)param_1 + 0x16) & 1);
            local_c4 = CONCAT22(CONCAT11(local_c4._3_1_,
                                         (byte)sVar1 | (*(byte *)((int)param_1 + 0x22) & 1) << 1 |
                                         *(byte *)((int)param_1 + 0x23) & 1),
                                CONCAT11(*(char *)(param_1 + 9) << 5 |
                                         (byte)((param_1[3] & 0xf) << 1) |
                                         *(byte *)((int)param_1 + 0x1e) & 1,
                                         *(char *)((int)param_1 + 0x1f) << 7 |
                                         (byte)(uVar12 >> 0x1e) | (*(byte *)(param_1 + 8) & 1) << 4
                                         | (*(byte *)(param_1 + 7) & 1) << 2 |
                                         (*(byte *)((int)param_1 + 0x21) & 1) << 3 |
                                         (*(byte *)((int)param_1 + 0x1d) >> 1 & 1) << 6 |
                                         (*(byte *)((int)param_1 + 0x1d) & 1) << 5));
            local_c0 = CONCAT31(local_c0._1_3_,
                                (byte)local_c0 & 0xe0 |
                                (byte)(((uint)*(ushort *)(param_1 + 5) << 0x16) >> 0x1b));
            if (uVar31 < 0x400) {
              iVar23 = pp_pm_set_flow_info();
            }
            else {
              iVar23 = pp_pm_set_external_flow_info(g_direction,uVar31,&local_c8);
            }
            if (iVar23 == 0) {
              opcDbNatEntryValidSet(local_dc,1);
              opcDbCmdEntryValidSet(iVar8,1);
              opcDbVlanEntryValidSet(local_e8,1);
              opcDbSubRamEntryValidSet(uVar33,1);
              opcDbFlowEntryValidSet(uVar31,1);
LAB_00059134:
              *param_10 = uVar31;
              return 0;
            }
          }
          printk("ERROR:writeFlowInfoToRam Fail\n");
          return 0xfffffff4;
        }
      }
      else {
        piVar10 = (int *)kmem_cache_alloc(_DAT_000df0e4,0x20);
        if (piVar10 == (int *)0x0) {
          printk("ERROR:memory alloc Fail!!\n");
          kfree(puVar11);
          goto LAB_000598ec;
        }
        __memzero(piVar10,0x14);
        piVar32 = s_tmSubRamInfoListTail;
        uVar31 = *(ushort *)(s_tmSubRamInfoListTail[4] + 2) + 1;
        piVar28 = s_tmSubRamInfoListHead;
        if (uVar31 < 0x400) {
          if (l_subRamAllAlloc == '\0') {
            *piVar10 = (int)s_tmSubRamInfoListTail;
            s_tmSubRamInfoListTail = piVar10;
            piVar10[4] = (int)puVar11;
            piVar32[1] = (int)piVar10;
            cVar19 = l_subRamAllAlloc;
            piVar10[1] = 0;
            goto LAB_00059a68;
          }
        }
        else {
          l_subRamAllAlloc = '\x01';
        }
      }
      do {
        if (((char)piVar28[2] == '\0') && (piVar28[4] != 0)) {
          __memzero(&local_c8,0x24);
          uVar33 = *(ushort *)(piVar28[4] + 2);
          puVar36 = &local_c8;
          puVar24 = param_2;
          do {
            puVar25 = puVar24 + 4;
            uVar30 = puVar24[1];
            uVar35 = puVar24[2];
            puVar17 = puVar36 + 4;
            uVar37 = puVar24[3];
            *puVar36 = *puVar24;
            puVar36[1] = uVar30;
            puVar36[2] = uVar35;
            puVar36[3] = uVar37;
            puVar36 = puVar17;
            puVar24 = puVar25;
          } while (puVar25 != param_2 + 8);
          *puVar17 = *puVar25;
          *(undefined1 *)(piVar28 + 2) = 0;
          local_c8 = CONCAT22(uVar33,(undefined2)local_c8);
          piVar28[3] = (uint)uVar33;
          puVar9 = (uint *)piVar28[4];
          *puVar9 = local_c8;
          puVar9[1] = local_c4;
          puVar9[2] = local_c0;
          puVar9[3] = uStack_bc;
          puVar9[4] = local_b8;
          puVar9[5] = local_b4;
          puVar9[6] = uStack_b0;
          puVar9[7] = local_ac;
          puVar9[8] = local_a8;
          kfree(puVar11);
          kfree(piVar10);
          goto LAB_00059adc;
        }
        piVar32 = piVar28 + 1;
        piVar28 = (int *)*piVar32;
      } while ((int *)*piVar32 != (int *)0x0);
      if (TM_OPC_DEBUG != 0) {
        printk("exceed max subram info ram depth %d\n",0x400);
      }
      kfree(puVar11);
      kfree(piVar10);
LAB_000598ec:
      printk("ERROR:add subram info to list Fail\n");
      return 0xfffffff4;
    }
  }
  iVar23 = s_tmCmdInfoListHead;
  if (*(int *)(s_tmCmdInfoListHead + 0x18) != 0) {
LAB_0005ad50:
    if ((*(char *)(iVar23 + 0x14) != '\0') || (*(uint *)(iVar23 + 0xc) < uVar12)) goto LAB_0005ad68;
    memcpy(auStack_a0,__s2,uVar12 * 0xc);
    iVar8 = *(int *)(iVar23 + 0x10);
    sVar29 = 0;
    do {
      puVar11 = (undefined4 *)((int)__s2 + sVar29);
      uVar30 = puVar11[1];
      uVar35 = puVar11[2];
      puVar36 = (undefined4 *)(*(int *)(iVar23 + 0x18) + sVar29);
      sVar29 = sVar29 + 0xc;
      *puVar36 = *puVar11;
      puVar36[1] = uVar30;
      puVar36[2] = uVar35;
    } while (sVar29 != uVar12 * 0xc);
    kfree(__s2);
    kfree(piVar10);
    goto LAB_0005ac00;
  }
  printk("cmd list error!!\n");
LAB_0005ad74:
  if (TM_OPC_DEBUG != 0) {
    printk("exceed max cmd info ram depth %d\n",0x2000);
  }
  kfree(__s2);
  kfree(piVar10);
LAB_0005a2d8:
  printk("ERROR:add cmd info to list Fail\n");
  return 0xfffffff4;
switchD_0005a264_caseD_0:
  if (uVar31 != 0) {
    *(undefined4 *)((int)__s2 + 0x10) = 5;
    *(undefined2 *)((int)__s2 + 0x14) = *param_6;
    piVar10[7] = (int)piVar10;
    piVar10[0xd] = (int)__s2 + 0xc;
    piVar10[8] = 0;
LAB_0005a40c:
    piVar10[2] = (int)(piVar10 + 7);
    uVar31 = 1;
    pvVar18 = (void *)((int)__s2 + 0xc);
    piVar32 = piVar10 + 7;
  }
  goto LAB_0005a418;
LAB_0005ad68:
  iVar23 = *(int *)(iVar23 + 4);
  if (iVar23 == 0) goto LAB_0005ad74;
  goto LAB_0005ad50;
LAB_0005a6e4:
  piVar28 = piVar32 + 1;
  piVar32 = (int *)*piVar28;
  if ((int *)*piVar28 == (int *)0x0) goto code_r0x0005a6f0;
  goto LAB_0005a6cc;
code_r0x0005a6f0:
  if (TM_OPC_DEBUG != 0) {
    printk("exceed max flow info ram depth %d\n",0x400);
  }
  kfree(puVar11);
  kfree(piVar10);
  goto LAB_0005a714;
}

