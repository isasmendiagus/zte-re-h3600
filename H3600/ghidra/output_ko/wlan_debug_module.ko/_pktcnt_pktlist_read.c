// module: wlan_debug_module.ko
// function: _pktcnt_pktlist_read @ 0x12dd0
// size: 1596 bytes
//

undefined4 _pktcnt_pktlist_read(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  undefined4 uVar8;
  undefined1 *puVar9;
  uint uVar10;
  undefined1 *puVar11;
  bool bVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  uint *local_b8;
  int local_b0;
  undefined1 *local_ac;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  uint local_84;
  uint local_80;
  uint local_7c;
  uint local_78;
  uint local_74;
  uint local_70;
  uint local_6c;
  uint local_68;
  uint local_64;
  uint local_60;
  uint local_5c;
  ushort local_58;
  undefined1 auStack_56 [50];
  
  iVar1 = *(int *)(param_1 + 0x50);
  local_b0 = 1;
  iVar7 = iVar1 * 0x3e98;
  local_ac = &g_pktlist + iVar7;
  seq_printf(param_1,"[%d][%s] : %u\n",iVar1,iVar1 * 0xc4 + 0x661b8,
             *(undefined4 *)(&g_pktlist + iVar7));
  local_b8 = (uint *)(&DAT_0001bb88 + iVar7);
  do {
    if (local_b0 == 1) {
      seq_printf(param_1,"%s[%u] SrcMac->DstMac, SrcIP[SrcPort]->DstIP[DstPort] : %u\n",&_LC65,
                 *local_b8,local_b8[2]);
      if (*local_b8 != 0) goto LAB_00012e78;
    }
    else {
      seq_printf(param_1,"%s[%u] SrcMac->DstMac, SrcIP[SrcPort]->DstIP[DstPort] : %u\n",&_LC60,
                 *local_b8,local_b8[2]);
      if (*local_b8 != 0) {
LAB_00012e78:
        uVar10 = 1;
        puVar9 = local_ac;
        puVar11 = local_ac;
        do {
          uVar4 = (uint)(byte)puVar9[0x2c];
          if (uVar4 == 0) {
            local_58 = (ushort)(byte)puVar9[0x2c];
            local_84 = uVar4;
            local_80 = uVar4;
            local_7c = uVar4;
            local_78 = uVar4;
            local_74 = uVar4;
            local_70 = uVar4;
            local_6c = uVar4;
            local_68 = uVar4;
            local_64 = uVar4;
            local_60 = uVar4;
            local_5c = uVar4;
            memset(auStack_56,0,0x2e);
            local_a4 = *(undefined4 *)(puVar9 + 8);
            local_a0 = *(undefined4 *)(puVar9 + 0xc);
            local_9c = *(undefined4 *)(puVar9 + 0x10);
            local_98 = *(undefined4 *)(puVar9 + 0x14);
            local_94 = *(undefined4 *)(puVar9 + 0x18);
            local_90 = *(undefined4 *)(puVar9 + 0x1c);
            local_8c = *(undefined4 *)(puVar9 + 0x20);
            local_88 = *(undefined4 *)(puVar9 + 0x24);
            IPv6ToStr(&local_a4,&local_84,0x2e);
            IPv6ToStr(&local_94,auStack_56,0x2e);
            iVar1 = *(int *)(puVar9 + 0x28);
            if (iVar1 == -1) {
              uVar2 = *(undefined4 *)(puVar9 + 0x48);
              uVar5 = *(undefined4 *)(puVar9 + 0x4c);
              uVar8 = *(undefined4 *)(puVar9 + 0x40);
              uVar13 = _64div32(uVar2,uVar5,uVar8);
              uVar3 = *(undefined4 *)(puVar9 + 0x50);
              uVar6 = *(undefined4 *)(puVar9 + 0x54);
              uVar14 = _64div32(uVar3,uVar6,uVar8);
              seq_printf(param_1,
                         "[%d] %02X:%02X:%02X:%02X:%02X:%02X->%02X:%02X:%02X:%02X:%02X:%02X, %s[%d]->%s[%d] : %u, %llu(%llu), %llu(%llu)\n"
                         ,uVar10,puVar11[0x32],puVar11[0x33],puVar11[0x34],puVar11[0x35],
                         puVar11[0x36],puVar11[0x37],puVar11[0x38],puVar11[0x39],puVar11[0x3a],
                         puVar11[0x3b],puVar11[0x3c],puVar11[0x3d],&local_84,
                         *(undefined2 *)(puVar9 + 0x2e),auStack_56,*(undefined2 *)(puVar9 + 0x30),
                         uVar8,uVar2,uVar5,uVar13,uVar3,uVar6,uVar14);
            }
            else {
              uVar2 = *(undefined4 *)(puVar9 + 0x48);
              uVar5 = *(undefined4 *)(puVar9 + 0x4c);
              uVar8 = *(undefined4 *)(puVar9 + 0x40);
              uVar13 = _64div32(uVar2,uVar5,uVar8);
              uVar3 = *(undefined4 *)(puVar9 + 0x50);
              uVar6 = *(undefined4 *)(puVar9 + 0x54);
              uVar14 = _64div32(uVar3,uVar6,uVar8);
              seq_printf(param_1,
                         "[%d] %02X:%02X:%02X:%02X:%02X:%02X->%02X:%02X:%02X:%02X:%02X:%02X, %s[%d]->%s[%d] : %u, %llu(%llu), %llu(%llu), VID=%d\n"
                         ,uVar10,puVar11[0x32],puVar11[0x33],puVar11[0x34],puVar11[0x35],
                         puVar11[0x36],puVar11[0x37],puVar11[0x38],puVar11[0x39],puVar11[0x3a],
                         puVar11[0x3b],puVar11[0x3c],puVar11[0x3d],&local_84,
                         *(undefined2 *)(puVar9 + 0x2e),auStack_56,*(undefined2 *)(puVar9 + 0x30),
                         uVar8,uVar2,uVar5,uVar13,uVar3,uVar6,uVar14,iVar1);
            }
          }
          else {
            iVar1 = *(int *)(puVar9 + 0x28);
            uVar5 = *(undefined4 *)(puVar9 + 0x40);
            uVar2 = *(undefined4 *)(puVar9 + 0x48);
            uVar3 = *(undefined4 *)(puVar9 + 0x4c);
            if (iVar1 == -1) {
              uVar13 = _64div32(uVar2,uVar3,uVar5);
              uVar6 = *(undefined4 *)(puVar9 + 0x50);
              uVar8 = *(undefined4 *)(puVar9 + 0x54);
              uVar14 = _64div32(uVar6,uVar8,uVar5);
              seq_printf(param_1,
                         "[%d] %02X:%02X:%02X:%02X:%02X:%02X->%02X:%02X:%02X:%02X:%02X:%02X, %d.%d.%d.%d[%d]->%d.%d.%d.%d[%d] : %u, %llu(%llu), %llu(%llu)\n"
                         ,uVar10,puVar11[0x32],puVar11[0x33],puVar11[0x34],puVar11[0x35],
                         puVar11[0x36],puVar11[0x37],puVar11[0x38],puVar11[0x39],puVar11[0x3a],
                         puVar11[0x3b],puVar11[0x3c],puVar11[0x3d],puVar11[8],puVar11[9],puVar11[10]
                         ,puVar11[0xb],*(undefined2 *)(puVar9 + 0x2e),puVar11[0x18],puVar11[0x19],
                         puVar11[0x1a],puVar11[0x1b],*(undefined2 *)(puVar9 + 0x30),uVar5,uVar2,
                         uVar3,uVar13,uVar6,uVar8,uVar14);
            }
            else {
              uVar13 = _64div32(uVar2,uVar3,uVar5);
              uVar6 = *(undefined4 *)(puVar9 + 0x50);
              uVar8 = *(undefined4 *)(puVar9 + 0x54);
              uVar14 = _64div32(uVar6,uVar8,uVar5);
              seq_printf(param_1,
                         "[%d] %02X:%02X:%02X:%02X:%02X:%02X->%02X:%02X:%02X:%02X:%02X:%02X, %d.%d.%d.%d[%d]->%d.%d.%d.%d[%d] : %u, %llu(%llu), %llu(%llu), VID=%d\n"
                         ,uVar10,puVar11[0x32],puVar11[0x33],puVar11[0x34],puVar11[0x35],
                         puVar11[0x36],puVar11[0x37],puVar11[0x38],puVar11[0x39],puVar11[0x3a],
                         puVar11[0x3b],puVar11[0x3c],puVar11[0x3d],puVar11[8],puVar11[9],puVar11[10]
                         ,puVar11[0xb],*(undefined2 *)(puVar9 + 0x2e),puVar11[0x18],puVar11[0x19],
                         puVar11[0x1a],puVar11[0x1b],*(undefined2 *)(puVar9 + 0x30),uVar5,uVar2,
                         uVar3,uVar13,uVar6,uVar8,uVar14,iVar1);
            }
          }
          puVar9 = puVar9 + 0x50;
          puVar11 = puVar11 + 0x50;
          bVar12 = uVar10 < *local_b8;
          uVar10 = uVar10 + 1;
        } while (bVar12);
      }
      if (local_b0 == 2) {
        return 0;
      }
    }
    local_b0 = local_b0 + 1;
    local_b8 = local_b8 + 1;
    local_ac = local_ac + 8000;
  } while( true );
}

