// module: tm.ko
// function: aclBuildExtRuleAndHashEntriesByParseCondition @ 0x55d80
// size: 5120 bytes
//

undefined4 aclBuildExtRuleAndHashEntriesByParseCondition(int param_1,byte *param_2,int param_3)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  ushort uVar4;
  ushort uVar5;
  ushort uVar6;
  undefined2 uVar7;
  undefined2 uVar8;
  ushort uVar9;
  int iVar10;
  char *pcVar11;
  undefined1 *puVar12;
  byte bVar13;
  char *pcVar14;
  int iVar15;
  uint uVar16;
  short sVar17;
  bool bVar18;
  char local_1d8 [2];
  short local_1d6;
  short local_1d4;
  undefined2 local_1d2;
  undefined2 local_1d0;
  undefined1 local_1cc;
  short local_1ca;
  short local_1c8;
  undefined2 local_1c6;
  undefined2 local_1c4;
  undefined1 local_1c0;
  short local_1be;
  short local_1bc;
  undefined2 local_1ba;
  undefined2 local_1b8;
  undefined1 local_1b4;
  short local_1b2;
  short local_1b0;
  undefined2 local_1ae;
  undefined2 local_1ac;
  undefined1 local_1a8;
  short local_1a6;
  short local_1a4;
  undefined2 local_1a2;
  undefined2 local_1a0;
  undefined1 local_19c;
  short local_19a;
  short local_198;
  undefined2 local_196;
  undefined2 local_194;
  undefined1 local_190;
  undefined2 local_18e;
  undefined2 local_18c;
  undefined2 local_18a;
  undefined2 local_188;
  undefined1 local_184;
  undefined2 local_182;
  short local_180;
  undefined2 local_17e;
  undefined2 local_17c;
  undefined1 local_178;
  undefined2 local_176;
  undefined2 local_174;
  undefined2 local_172;
  undefined2 local_170;
  undefined1 local_16c;
  undefined2 local_16a;
  short local_168;
  undefined2 local_166;
  undefined2 local_164;
  undefined1 local_160;
  undefined2 local_15e;
  undefined2 local_15c;
  undefined2 local_15a;
  undefined2 local_158;
  undefined1 local_154;
  ushort local_152;
  ushort local_150;
  undefined2 local_14e;
  undefined2 local_14c;
  undefined1 local_148;
  undefined2 local_146;
  undefined2 local_144;
  undefined2 local_142;
  undefined2 local_140;
  undefined1 local_130;
  undefined2 local_12e;
  short local_12c;
  undefined2 local_12a;
  undefined2 local_128;
  undefined1 local_124;
  undefined2 local_122;
  ushort local_120;
  undefined2 local_11e;
  undefined2 local_11c;
  undefined1 local_10c;
  short local_10a;
  short local_108;
  undefined2 local_106;
  undefined2 local_104;
  undefined1 local_100;
  short local_fe;
  short local_fc;
  undefined2 local_fa;
  undefined2 local_f8;
  undefined1 local_f4;
  short local_f2;
  short local_f0;
  undefined2 local_ee;
  undefined2 local_ec;
  undefined1 local_e8;
  short local_e6;
  short local_e4;
  undefined2 local_e2;
  undefined2 local_e0;
  undefined1 local_dc;
  undefined2 local_da;
  undefined2 local_d8;
  undefined2 local_d6;
  undefined2 local_d4;
  undefined1 local_d0;
  undefined2 local_ce;
  undefined2 local_cc;
  undefined2 local_ca;
  undefined2 local_c8;
  undefined1 local_c4 [96];
  undefined1 local_64;
  undefined2 local_62;
  undefined2 local_60;
  undefined2 local_5e;
  undefined2 local_5c;
  undefined1 local_58;
  undefined2 local_56;
  undefined2 local_54;
  undefined2 local_52;
  undefined2 local_50;
  char acStack_28 [4];
  
  pcVar14 = local_1d8;
  if (param_2 == (byte *)0x0 || (param_1 == 0 || param_3 == 0)) {
    printk("ERROR:(%s:%d)","tm_acl_v2.c",0x484);
    printk("aclBuildExtRuleAndHashEntriesByParseCondition params is NULL\n");
    return 0xfffffff4;
  }
  __memzero(local_1d8,0x1b0);
  uVar16 = *(uint *)(param_1 + 0x1c);
  if ((uVar16 & 1) != 0) {
    local_1d0 = 0;
    local_1d2 = 0;
    local_1c4 = 0;
    local_1b8 = 0;
    local_1d8[0] = '\x01';
    local_1cc = 1;
    local_1d6 = (ushort)*(byte *)(param_1 + 0x2f) + (ushort)*(byte *)(param_1 + 0x2e) * 0x100;
    local_1c0 = 1;
    local_1d4 = (ushort)*(byte *)(param_1 + 0x29) + (ushort)*(byte *)(param_1 + 0x28) * 0x100;
    local_1ca = (ushort)*(byte *)(param_1 + 0x31) + (ushort)*(byte *)(param_1 + 0x30) * 0x100;
    local_1c8 = (ushort)*(byte *)(param_1 + 0x2b) + (ushort)*(byte *)(param_1 + 0x2a) * 0x100;
    local_1be = (ushort)*(byte *)(param_1 + 0x33) + (ushort)*(byte *)(param_1 + 0x32) * 0x100;
    local_1bc = (ushort)*(byte *)(param_1 + 0x2d) + (ushort)*(byte *)(param_1 + 0x2c) * 0x100;
    local_1c6 = 2;
    local_1ba = 4;
  }
  if ((uVar16 & 2) != 0) {
    local_1b2 = (ushort)*(byte *)(param_1 + 0x3b) + (ushort)*(byte *)(param_1 + 0x3a) * 0x100;
    local_1b0 = (ushort)*(byte *)(param_1 + 0x35) + (ushort)*(byte *)(param_1 + 0x34) * 0x100;
    local_1b4 = 1;
    local_1a8 = 1;
    local_19c = 1;
    local_1a6 = (ushort)*(byte *)(param_1 + 0x3d) + (ushort)*(byte *)(param_1 + 0x3c) * 0x100;
    local_1a4 = (ushort)*(byte *)(param_1 + 0x37) + (ushort)*(byte *)(param_1 + 0x36) * 0x100;
    local_19a = (ushort)*(byte *)(param_1 + 0x3f) + (ushort)*(byte *)(param_1 + 0x3e) * 0x100;
    local_198 = (ushort)*(byte *)(param_1 + 0x39) + (ushort)*(byte *)(param_1 + 0x38) * 0x100;
    local_1ac = 0;
    local_1a0 = 0;
    local_194 = 0;
    local_1ae = 6;
    local_1a2 = 8;
    local_196 = 10;
  }
  if ((uVar16 & 8) != 0) {
    local_18e = 0xffff;
    local_190 = 1;
    local_18c = *(undefined2 *)(param_1 + 0x40);
    local_188 = 0;
    local_18a = 0xc;
  }
  if ((uVar16 & 0x10) != 0) {
    local_184 = 1;
    local_182 = *(undefined2 *)(param_1 + 0x46);
    local_180 = (*(byte *)(param_1 + 0x44) & 1) * 0x1000 +
                (ushort)*(byte *)(param_1 + 0x45) * 0x2000 +
                (ushort)(((uint)*(ushort *)(param_1 + 0x42) << 0x14) >> 0x14);
    local_17c = 0;
    local_17e = 0xe;
  }
  if ((uVar16 & 0x20) != 0) {
    local_176 = 0xffff;
    local_178 = 1;
    local_174 = *(undefined2 *)(param_1 + 0x48);
    local_170 = 0;
    local_172 = 0x10;
  }
  if ((uVar16 & 0x40) != 0) {
    local_16c = 1;
    local_16a = *(undefined2 *)(param_1 + 0x4e);
    local_168 = (*(byte *)(param_1 + 0x4c) & 1) * 0x1000 +
                (ushort)*(byte *)(param_1 + 0x4d) * 0x2000 +
                (ushort)(((uint)*(ushort *)(param_1 + 0x4a) << 0x14) >> 0x14);
    local_164 = 0;
    local_166 = 0x12;
  }
  if ((uVar16 & 0x80) != 0) {
    local_160 = 1;
    local_158 = 1;
    local_15c = *(undefined2 *)(param_1 + 0x52);
    local_15e = 0xffff;
    local_15a = 0;
  }
  if (*(int *)(param_1 + 0x5c) == 1) {
    if ((*(uint *)(param_1 + 0x1c) & 0x900) == 0x900) {
      local_154 = 1;
      local_152 = 0xf0fc;
      local_14c = 2;
      local_150 = (ushort)*(byte *)(param_1 + 99) * 0x1000 + (ushort)*(byte *)(param_1 + 0x60) * 4;
      local_14e = 0;
    }
    else if ((uVar16 & 0x800) == 0) {
      if ((uVar16 & 0x100) != 0) {
        local_154 = 1;
        local_14e = 0;
        local_152 = 0xf000;
        local_150 = (ushort)*(byte *)(param_1 + 99) << 0xc;
        local_14c = 2;
      }
    }
    else {
      local_154 = 1;
      local_152 = 0xfc;
      local_14c = 2;
      local_150 = (ushort)*(byte *)(param_1 + 0x60) << 2;
      local_14e = 0;
    }
    if ((uVar16 & 0x1000) != 0) {
      local_122 = 0xff;
      local_124 = 1;
      local_120 = (ushort)*(byte *)(param_1 + 0x62);
      local_11c = 2;
      local_11e = 8;
    }
    if ((uVar16 & 0x200) != 0) {
      local_10a = (ushort)*(byte *)(param_1 + 0x69) + (ushort)*(byte *)(param_1 + 0x68) * 0x100;
      local_10c = 1;
      local_108 = (ushort)*(byte *)(param_1 + 0x65) + (ushort)*(byte *)(param_1 + 100) * 0x100;
      local_fe = (ushort)*(byte *)(param_1 + 0x6b) + (ushort)*(byte *)(param_1 + 0x6a) * 0x100;
      local_fc = (ushort)*(byte *)(param_1 + 0x67) + (ushort)*(byte *)(param_1 + 0x66) * 0x100;
      local_100 = 1;
      local_104 = 2;
      local_f8 = 2;
      local_106 = 0xc;
      local_fa = 0xe;
    }
    if ((uVar16 & 0x400) != 0) {
      local_f2 = (ushort)*(byte *)(param_1 + 0x71) + (ushort)*(byte *)(param_1 + 0x70) * 0x100;
      local_f4 = 1;
      local_f0 = (ushort)*(byte *)(param_1 + 0x6d) + (ushort)*(byte *)(param_1 + 0x6c) * 0x100;
      local_e6 = (ushort)*(byte *)(param_1 + 0x73) + (ushort)*(byte *)(param_1 + 0x72) * 0x100;
      local_e4 = (ushort)*(byte *)(param_1 + 0x6f) + (ushort)*(byte *)(param_1 + 0x6e) * 0x100;
      local_e8 = 1;
      local_ec = 2;
      local_e0 = 2;
      local_ee = 0x10;
      local_e2 = 0x12;
    }
    if ((uVar16 & 0x100000) != 0) {
      local_dc = 1;
      local_da = 0xffff;
      local_d8 = *(undefined2 *)(param_1 + 0x74);
      local_d4 = 2;
      local_d6 = 0x14;
    }
    if ((uVar16 & 0x200000) != 0) {
      local_d0 = 1;
      local_ce = 0xffff;
      local_cc = *(undefined2 *)(param_1 + 0x76);
      local_c8 = 2;
      local_ca = 0x16;
    }
  }
  else if (*(int *)(param_1 + 0x5c) == 2) {
    if ((*(uint *)(param_1 + 0x1c) & 0x30000) == 0x30000) {
      local_154 = 1;
      local_152 = 0xfff0;
      local_14c = 3;
      local_150 = (ushort)*(byte *)(param_1 + 0x60) * 0x1000 +
                  (ushort)*(byte *)(param_1 + 0x61) * 0x10;
      local_14e = 0;
    }
    else if ((uVar16 & 0x20000) == 0) {
      if ((uVar16 & 0x10000) != 0) {
        local_14e = 0;
        local_154 = 1;
        local_152 = 0xff0;
        local_150 = (ushort)*(byte *)(param_1 + 0x61) << 4;
        local_14c = 3;
      }
    }
    else {
      local_152 = 0xf000;
      local_154 = 1;
      local_14c = 3;
      local_150 = (ushort)*(byte *)(param_1 + 0x60) << 0xc;
      local_14e = 0;
    }
    if ((uVar16 & 0x8000) != 0) {
      local_144 = (short)*(int *)(param_1 + 100);
      local_150 = (ushort)((uint)(*(int *)(param_1 + 100) << 0xc) >> 0x1c) | local_150;
      local_152 = local_152 | 0xf;
      local_154 = 1;
      local_148 = 1;
      local_14c = 3;
      local_140 = 3;
      local_14e = 0;
      local_146 = 0xffff;
      local_142 = 2;
    }
    if ((uVar16 & 0x40000) != 0) {
      local_12e = 0xff00;
      local_130 = 1;
      local_128 = 3;
      local_12c = (ushort)*(byte *)(param_1 + 99) << 8;
      local_12a = 6;
    }
    if ((uVar16 & 0x2000) != 0) {
      pcVar11 = local_1d8;
      iVar10 = param_1;
      sVar17 = 8;
      do {
        bVar13 = *(byte *)(iVar10 + 0x78);
        iVar15 = iVar10 + 2;
        bVar1 = *(byte *)(iVar10 + 0x79);
        bVar2 = *(byte *)(iVar10 + 0x68);
        bVar3 = *(byte *)(iVar10 + 0x69);
        *(short *)(pcVar11 + 0xba) = sVar17;
        pcVar11[0xb4] = 1;
        *(undefined2 *)(pcVar11 + 0xbc) = 3;
        *(ushort *)(pcVar11 + 0xb6) = (ushort)bVar1 + (ushort)bVar13 * 0x100;
        *(ushort *)(pcVar11 + 0xb8) = (ushort)bVar3 + (ushort)bVar2 * 0x100;
        pcVar11 = pcVar11 + 0xc;
        iVar10 = iVar15;
        sVar17 = sVar17 + 2;
      } while (iVar15 != param_1 + 0x10);
    }
    if ((uVar16 & 0x4000) != 0) {
      puVar12 = local_c4;
      iVar10 = param_1;
      sVar17 = 0x18;
      do {
        bVar13 = *(byte *)(iVar10 + 0x98);
        iVar15 = iVar10 + 2;
        bVar1 = *(byte *)(iVar10 + 0x99);
        bVar2 = *(byte *)(iVar10 + 0x88);
        bVar3 = *(byte *)(iVar10 + 0x89);
        *(short *)(puVar12 + 6) = sVar17;
        *puVar12 = 1;
        *(undefined2 *)(puVar12 + 8) = 3;
        *(ushort *)(puVar12 + 2) = (ushort)bVar1 + (ushort)bVar13 * 0x100;
        *(ushort *)(puVar12 + 4) = (ushort)bVar3 + (ushort)bVar2 * 0x100;
        puVar12 = puVar12 + 0xc;
        iVar10 = iVar15;
        sVar17 = sVar17 + 2;
      } while (iVar15 != param_1 + 0x10);
    }
    if ((uVar16 & 0x80000) != 0) {
      printk("second next header not support!!!\n");
      printk("ERROR:(%s:%d)","tm_acl_v2.c",0x48e);
      printk("getMachEthHead fail\n");
      return 0xfffffff4;
    }
    if ((uVar16 & 0x100000) != 0) {
      local_64 = 1;
      local_60 = *(undefined2 *)(param_1 + 0xa8);
      local_5e = 0;
      local_62 = 0xffff;
      local_5c = 5;
    }
    if ((uVar16 & 0x200000) != 0) {
      local_58 = 1;
      local_56 = 0xffff;
      local_54 = *(undefined2 *)(param_1 + 0xaa);
      local_50 = 5;
      local_52 = 2;
    }
  }
  bVar18 = (uVar16 & 0x1000000) != 0;
  if (bVar18) {
    param_2[0x3b] = param_2[0x3b] | 4;
    param_2[0x3c] = param_2[0x3c] & 0xf8;
    *param_2 = *param_2 & 0x80;
    uVar4 = *(ushort *)(param_1 + 0x5a);
    param_2[0x12] = (byte)(((uint)uVar4 << 0x14) >> 0x18);
    param_2[0x13] = param_2[0x13] & 0xf0 | (byte)(uVar4 >> 0xc);
    param_2[0x11] = param_2[0x11] & 0xf | (byte)((uVar4 & 0xf) << 4);
    *(undefined2 *)(param_3 + 0x13) = *(undefined2 *)(param_1 + 0x56);
  }
  uVar16 = (uint)bVar18;
  do {
    while (*pcVar14 == '\x01') {
      if (0x13 < uVar16) {
        printk("ERROR:(%s:%d)","tm_acl_v2.c",0x4a2);
        printk("condition exceeded!! Only 2*10*2Bytes match data supported\n");
        return 0xfffffff4;
      }
      if ((param_2[0x3b] & 4) == 0) {
        switch(uVar16) {
        case 1:
          goto switchD_000560dc_caseD_1;
        case 2:
          goto switchD_000560dc_caseD_2;
        case 3:
          goto switchD_000560dc_caseD_3;
        case 4:
          goto switchD_000560dc_caseD_4;
        case 5:
          goto switchD_000560dc_caseD_5;
        case 6:
          goto switchD_000560dc_caseD_6;
        case 7:
          goto switchD_000560dc_caseD_7;
        case 8:
          goto switchD_000560dc_caseD_8;
        case 9:
          goto switchD_000560dc_caseD_9;
        case 10:
          goto switchD_000560dc_caseD_a;
        case 0xb:
          goto switchD_000560dc_caseD_b;
        case 0xc:
          goto switchD_000560dc_caseD_c;
        case 0xd:
          goto switchD_000560dc_caseD_d;
        case 0xe:
          goto switchD_000560dc_caseD_e;
        case 0xf:
          goto switchD_000560dc_caseD_f;
        case 0x10:
          goto switchD_000560dc_caseD_10;
        case 0x11:
          goto switchD_000560dc_caseD_11;
        case 0x12:
          goto switchD_000560dc_caseD_12;
        case 0x13:
          goto switchD_000560dc_caseD_13;
        default:
          uVar4 = *(ushort *)(pcVar14 + 2);
          uVar7 = *(undefined2 *)(pcVar14 + 8);
          uVar8 = *(undefined2 *)(pcVar14 + 6);
          param_2[0x13] = param_2[0x13] & 0xf0 | (byte)(uVar4 >> 0xc);
          uVar9 = *(ushort *)(pcVar14 + 4);
          param_2[0x3c] = param_2[0x3c] & 0xf8 | (byte)uVar7 & 7;
          *param_2 = *param_2 & 0x80 | (byte)uVar8 & 0x7f;
          param_2[0x12] = (byte)(((uint)uVar4 << 0x14) >> 0x18);
          param_2[0x11] = param_2[0x11] & 0xf | (byte)((uVar4 & 0xf) << 4);
          *(ushort *)(param_3 + 0x13) = uVar4 & uVar9;
        }
      }
      else {
        switch(uVar16) {
        case 1:
switchD_000560dc_caseD_1:
          bVar13 = pcVar14[6];
          uVar4 = *(ushort *)(pcVar14 + 8);
          param_2[1] = param_2[1] & 0xc0 | (byte)(((uint)bVar13 << 0x19) >> 0x1a);
          uVar9 = *(ushort *)(pcVar14 + 2);
          param_2[0x15] = param_2[0x15] & 0xf0 | (byte)(uVar9 >> 0xc);
          uVar5 = *(ushort *)(pcVar14 + 4);
          *param_2 = *param_2 & 0x7f | (byte)((bVar13 & 1) << 7);
          param_2[0x3c] = param_2[0x3c] & 199 | (byte)((uVar4 & 7) << 3);
          param_2[0x14] = (byte)(((uint)uVar9 << 0x14) >> 0x18);
          param_2[0x13] = param_2[0x13] & 0xf | (byte)((uVar9 & 0xf) << 4);
          *(ushort *)(param_3 + 0x15) = uVar5 & uVar9;
          break;
        case 2:
switchD_000560dc_caseD_2:
          bVar13 = pcVar14[8];
          param_2[0x3d] = param_2[0x3d] & 0xfe | (byte)(((uint)bVar13 << 0x1d) >> 0x1f);
          bVar1 = pcVar14[6];
          param_2[2] = param_2[2] & 0xe0 | (byte)(((uint)bVar1 << 0x19) >> 0x1b);
          uVar4 = *(ushort *)(pcVar14 + 2);
          param_2[0x17] = param_2[0x17] & 0xf0 | (byte)(uVar4 >> 0xc);
          uVar9 = *(ushort *)(pcVar14 + 4);
          param_2[0x3c] = param_2[0x3c] & 0x3f | (byte)((bVar13 & 3) << 6);
          param_2[1] = param_2[1] & 0x3f | (byte)((bVar1 & 3) << 6);
          param_2[0x16] = (byte)(((uint)uVar4 << 0x14) >> 0x18);
          param_2[0x15] = param_2[0x15] & 0xf | (byte)((uVar4 & 0xf) << 4);
          *(ushort *)(param_3 + 0x17) = uVar9 & uVar4;
          break;
        case 3:
switchD_000560dc_caseD_3:
          bVar13 = pcVar14[6];
          uVar4 = *(ushort *)(pcVar14 + 8);
          param_2[3] = param_2[3] & 0xf0 | (byte)(((uint)bVar13 << 0x19) >> 0x1c);
          uVar9 = *(ushort *)(pcVar14 + 2);
          param_2[0x19] = param_2[0x19] & 0xf0 | (byte)(uVar9 >> 0xc);
          uVar5 = *(ushort *)(pcVar14 + 4);
          param_2[2] = param_2[2] & 0x1f | (byte)((bVar13 & 7) << 5);
          param_2[0x3d] = param_2[0x3d] & 0xf1 | (byte)((uVar4 & 7) << 1);
          param_2[0x18] = (byte)(((uint)uVar9 << 0x14) >> 0x18);
          param_2[0x17] = param_2[0x17] & 0xf | (byte)((uVar9 & 0xf) << 4);
          *(ushort *)(param_3 + 0x19) = uVar5 & uVar9;
          break;
        case 4:
switchD_000560dc_caseD_4:
          bVar13 = pcVar14[6];
          uVar4 = *(ushort *)(pcVar14 + 8);
          param_2[4] = param_2[4] & 0xf8 | (byte)(((uint)bVar13 << 0x19) >> 0x1d);
          uVar9 = *(ushort *)(pcVar14 + 2);
          param_2[0x1b] = param_2[0x1b] & 0xf0 | (byte)(uVar9 >> 0xc);
          uVar5 = *(ushort *)(pcVar14 + 4);
          param_2[3] = param_2[3] & 0xf | (byte)((bVar13 & 0xf) << 4);
          param_2[0x3d] = param_2[0x3d] & 0x8f | (byte)((uVar4 & 7) << 4);
          param_2[0x1a] = (byte)(((uint)uVar9 << 0x14) >> 0x18);
          param_2[0x19] = param_2[0x19] & 0xf | (byte)((uVar9 & 0xf) << 4);
          *(ushort *)(param_3 + 0x1b) = uVar5 & uVar9;
          break;
        case 5:
switchD_000560dc_caseD_5:
          bVar13 = pcVar14[8];
          param_2[0x3e] = param_2[0x3e] & 0xfc | (byte)(((uint)bVar13 << 0x1d) >> 0x1e);
          bVar1 = pcVar14[6];
          param_2[5] = param_2[5] & 0xfc | (byte)(((uint)bVar1 << 0x19) >> 0x1e);
          uVar4 = *(ushort *)(pcVar14 + 2);
          param_2[0x1d] = param_2[0x1d] & 0xf0 | (byte)(uVar4 >> 0xc);
          uVar9 = *(ushort *)(pcVar14 + 4);
          param_2[0x3d] = param_2[0x3d] & 0x7f | (byte)((bVar13 & 1) << 7);
          param_2[4] = param_2[4] & 7 | (byte)((bVar1 & 0x1f) << 3);
          param_2[0x1c] = (byte)(((uint)uVar4 << 0x14) >> 0x18);
          param_2[0x1b] = param_2[0x1b] & 0xf | (byte)((uVar4 & 0xf) << 4);
          *(ushort *)(param_3 + 0x1d) = uVar9 & uVar4;
          break;
        case 6:
switchD_000560dc_caseD_6:
          bVar13 = pcVar14[6];
          uVar4 = *(ushort *)(pcVar14 + 8);
          param_2[6] = param_2[6] & 0xfe | (byte)(((uint)bVar13 << 0x19) >> 0x1f);
          uVar9 = *(ushort *)(pcVar14 + 2);
          param_2[0x1f] = param_2[0x1f] & 0xf0 | (byte)(uVar9 >> 0xc);
          uVar5 = *(ushort *)(pcVar14 + 4);
          param_2[5] = param_2[5] & 3 | (byte)((bVar13 & 0x3f) << 2);
          param_2[0x3e] = param_2[0x3e] & 0xe3 | (byte)((uVar4 & 7) << 2);
          param_2[0x1e] = (byte)(((uint)uVar9 << 0x14) >> 0x18);
          param_2[0x1d] = param_2[0x1d] & 0xf | (byte)((uVar9 & 0xf) << 4);
          *(ushort *)(param_3 + 0x1f) = uVar5 & uVar9;
          break;
        case 7:
switchD_000560dc_caseD_7:
          uVar4 = *(ushort *)(pcVar14 + 2);
          uVar9 = *(ushort *)(pcVar14 + 8);
          uVar5 = *(ushort *)(pcVar14 + 6);
          param_2[0x21] = param_2[0x21] & 0xf0 | (byte)(uVar4 >> 0xc);
          uVar6 = *(ushort *)(pcVar14 + 4);
          param_2[0x3e] = param_2[0x3e] & 0x1f | (byte)((uVar9 & 7) << 5);
          param_2[6] = param_2[6] & 1 | (byte)((uVar5 & 0x7f) << 1);
          param_2[0x20] = (byte)(((uint)uVar4 << 0x14) >> 0x18);
          param_2[0x1f] = param_2[0x1f] & 0xf | (byte)((uVar4 & 0xf) << 4);
          *(ushort *)(param_3 + 0x21) = uVar4 & uVar6;
          break;
        case 8:
switchD_000560dc_caseD_8:
          uVar4 = *(ushort *)(pcVar14 + 2);
          uVar7 = *(undefined2 *)(pcVar14 + 8);
          uVar8 = *(undefined2 *)(pcVar14 + 6);
          param_2[0x23] = param_2[0x23] & 0xf0 | (byte)(uVar4 >> 0xc);
          uVar9 = *(ushort *)(pcVar14 + 4);
          param_2[0x3f] = param_2[0x3f] & 0xf8 | (byte)uVar7 & 7;
          param_2[7] = param_2[7] & 0x80 | (byte)uVar8 & 0x7f;
          param_2[0x22] = (byte)(((uint)uVar4 << 0x14) >> 0x18);
          param_2[0x21] = param_2[0x21] & 0xf | (byte)((uVar4 & 0xf) << 4);
          *(ushort *)(param_3 + 0x23) = uVar4 & uVar9;
          break;
        case 9:
switchD_000560dc_caseD_9:
          bVar13 = pcVar14[6];
          uVar4 = *(ushort *)(pcVar14 + 8);
          param_2[8] = param_2[8] & 0xc0 | (byte)(((uint)bVar13 << 0x19) >> 0x1a);
          uVar9 = *(ushort *)(pcVar14 + 2);
          param_2[0x25] = param_2[0x25] & 0xf0 | (byte)(uVar9 >> 0xc);
          uVar5 = *(ushort *)(pcVar14 + 4);
          param_2[7] = param_2[7] & 0x7f | (byte)((bVar13 & 1) << 7);
          param_2[0x3f] = param_2[0x3f] & 199 | (byte)((uVar4 & 7) << 3);
          param_2[0x24] = (byte)(((uint)uVar9 << 0x14) >> 0x18);
          param_2[0x23] = param_2[0x23] & 0xf | (byte)((uVar9 & 0xf) << 4);
          *(ushort *)(param_3 + 0x25) = uVar5 & uVar9;
          break;
        case 10:
switchD_000560dc_caseD_a:
          bVar13 = pcVar14[8];
          param_2[0x40] = param_2[0x40] & 0xfe | (byte)(((uint)bVar13 << 0x1d) >> 0x1f);
          bVar1 = pcVar14[6];
          param_2[9] = param_2[9] & 0xe0 | (byte)(((uint)bVar1 << 0x19) >> 0x1b);
          uVar4 = *(ushort *)(pcVar14 + 2);
          param_2[0x27] = param_2[0x27] & 0xf0 | (byte)(uVar4 >> 0xc);
          uVar9 = *(ushort *)(pcVar14 + 4);
          param_2[0x3f] = param_2[0x3f] & 0x3f | (byte)((bVar13 & 3) << 6);
          param_2[8] = param_2[8] & 0x3f | (byte)((bVar1 & 3) << 6);
          param_2[0x26] = (byte)(((uint)uVar4 << 0x14) >> 0x18);
          param_2[0x25] = param_2[0x25] & 0xf | (byte)((uVar4 & 0xf) << 4);
          *(ushort *)(param_3 + 0x27) = uVar9 & uVar4;
          break;
        case 0xb:
switchD_000560dc_caseD_b:
          bVar13 = pcVar14[6];
          uVar4 = *(ushort *)(pcVar14 + 8);
          param_2[10] = param_2[10] & 0xf0 | (byte)(((uint)bVar13 << 0x19) >> 0x1c);
          uVar9 = *(ushort *)(pcVar14 + 2);
          param_2[0x29] = param_2[0x29] & 0xf0 | (byte)(uVar9 >> 0xc);
          uVar5 = *(ushort *)(pcVar14 + 4);
          param_2[9] = param_2[9] & 0x1f | (byte)((bVar13 & 7) << 5);
          param_2[0x40] = param_2[0x40] & 0xf1 | (byte)((uVar4 & 7) << 1);
          param_2[0x28] = (byte)(((uint)uVar9 << 0x14) >> 0x18);
          param_2[0x27] = param_2[0x27] & 0xf | (byte)((uVar9 & 0xf) << 4);
          *(ushort *)(param_3 + 0x29) = uVar5 & uVar9;
          break;
        case 0xc:
switchD_000560dc_caseD_c:
          bVar13 = pcVar14[6];
          uVar4 = *(ushort *)(pcVar14 + 8);
          param_2[0xb] = param_2[0xb] & 0xf8 | (byte)(((uint)bVar13 << 0x19) >> 0x1d);
          uVar9 = *(ushort *)(pcVar14 + 2);
          param_2[0x2b] = param_2[0x2b] & 0xf0 | (byte)(uVar9 >> 0xc);
          uVar5 = *(ushort *)(pcVar14 + 4);
          param_2[10] = param_2[10] & 0xf | (byte)((bVar13 & 0xf) << 4);
          param_2[0x40] = param_2[0x40] & 0x8f | (byte)((uVar4 & 7) << 4);
          param_2[0x2a] = (byte)(((uint)uVar9 << 0x14) >> 0x18);
          param_2[0x29] = param_2[0x29] & 0xf | (byte)((uVar9 & 0xf) << 4);
          *(ushort *)(param_3 + 0x2b) = uVar5 & uVar9;
          break;
        case 0xd:
switchD_000560dc_caseD_d:
          bVar13 = pcVar14[8];
          param_2[0x41] = param_2[0x41] & 0xfc | (byte)(((uint)bVar13 << 0x1d) >> 0x1e);
          bVar1 = pcVar14[6];
          param_2[0xc] = param_2[0xc] & 0xfc | (byte)(((uint)bVar1 << 0x19) >> 0x1e);
          uVar4 = *(ushort *)(pcVar14 + 2);
          param_2[0x2d] = param_2[0x2d] & 0xf0 | (byte)(uVar4 >> 0xc);
          uVar9 = *(ushort *)(pcVar14 + 4);
          param_2[0x40] = param_2[0x40] & 0x7f | (byte)((bVar13 & 1) << 7);
          param_2[0xb] = param_2[0xb] & 7 | (byte)((bVar1 & 0x1f) << 3);
          param_2[0x2c] = (byte)(((uint)uVar4 << 0x14) >> 0x18);
          param_2[0x2b] = param_2[0x2b] & 0xf | (byte)((uVar4 & 0xf) << 4);
          *(ushort *)(param_3 + 0x2d) = uVar9 & uVar4;
          break;
        case 0xe:
switchD_000560dc_caseD_e:
          bVar13 = pcVar14[6];
          uVar4 = *(ushort *)(pcVar14 + 8);
          param_2[0xd] = param_2[0xd] & 0xfe | (byte)(((uint)bVar13 << 0x19) >> 0x1f);
          uVar9 = *(ushort *)(pcVar14 + 2);
          param_2[0x2f] = param_2[0x2f] & 0xf0 | (byte)(uVar9 >> 0xc);
          uVar5 = *(ushort *)(pcVar14 + 4);
          param_2[0xc] = param_2[0xc] & 3 | (byte)((bVar13 & 0x3f) << 2);
          param_2[0x41] = param_2[0x41] & 0xe3 | (byte)((uVar4 & 7) << 2);
          param_2[0x2e] = (byte)(((uint)uVar9 << 0x14) >> 0x18);
          param_2[0x2d] = param_2[0x2d] & 0xf | (byte)((uVar9 & 0xf) << 4);
          *(ushort *)(param_3 + 0x2f) = uVar5 & uVar9;
          break;
        case 0xf:
switchD_000560dc_caseD_f:
          uVar4 = *(ushort *)(pcVar14 + 2);
          uVar9 = *(ushort *)(pcVar14 + 8);
          uVar5 = *(ushort *)(pcVar14 + 6);
          param_2[0x31] = param_2[0x31] & 0xf0 | (byte)(uVar4 >> 0xc);
          uVar6 = *(ushort *)(pcVar14 + 4);
          param_2[0x41] = param_2[0x41] & 0x1f | (byte)((uVar9 & 7) << 5);
          param_2[0xd] = param_2[0xd] & 1 | (byte)((uVar5 & 0x7f) << 1);
          param_2[0x30] = (byte)(((uint)uVar4 << 0x14) >> 0x18);
          param_2[0x2f] = param_2[0x2f] & 0xf | (byte)((uVar4 & 0xf) << 4);
          *(ushort *)(param_3 + 0x31) = uVar4 & uVar6;
          break;
        case 0x10:
switchD_000560dc_caseD_10:
          uVar4 = *(ushort *)(pcVar14 + 2);
          uVar7 = *(undefined2 *)(pcVar14 + 8);
          uVar8 = *(undefined2 *)(pcVar14 + 6);
          param_2[0x33] = param_2[0x33] & 0xf0 | (byte)(uVar4 >> 0xc);
          uVar9 = *(ushort *)(pcVar14 + 4);
          param_2[0x42] = param_2[0x42] & 0xf8 | (byte)uVar7 & 7;
          param_2[0xe] = param_2[0xe] & 0x80 | (byte)uVar8 & 0x7f;
          param_2[0x32] = (byte)(((uint)uVar4 << 0x14) >> 0x18);
          param_2[0x31] = param_2[0x31] & 0xf | (byte)((uVar4 & 0xf) << 4);
          *(ushort *)(param_3 + 0x33) = uVar4 & uVar9;
          break;
        case 0x11:
switchD_000560dc_caseD_11:
          bVar13 = pcVar14[6];
          uVar4 = *(ushort *)(pcVar14 + 8);
          param_2[0xf] = param_2[0xf] & 0xc0 | (byte)(((uint)bVar13 << 0x19) >> 0x1a);
          uVar9 = *(ushort *)(pcVar14 + 2);
          param_2[0x35] = param_2[0x35] & 0xf0 | (byte)(uVar9 >> 0xc);
          uVar5 = *(ushort *)(pcVar14 + 4);
          param_2[0xe] = param_2[0xe] & 0x7f | (byte)((bVar13 & 1) << 7);
          param_2[0x42] = param_2[0x42] & 199 | (byte)((uVar4 & 7) << 3);
          param_2[0x34] = (byte)(((uint)uVar9 << 0x14) >> 0x18);
          param_2[0x33] = param_2[0x33] & 0xf | (byte)((uVar9 & 0xf) << 4);
          *(ushort *)(param_3 + 0x35) = uVar5 & uVar9;
          break;
        case 0x12:
switchD_000560dc_caseD_12:
          bVar13 = pcVar14[8];
          param_2[0x43] = param_2[0x43] & 0xfe | (byte)(((uint)bVar13 << 0x1d) >> 0x1f);
          bVar1 = pcVar14[6];
          param_2[0x10] = param_2[0x10] & 0xe0 | (byte)(((uint)bVar1 << 0x19) >> 0x1b);
          uVar4 = *(ushort *)(pcVar14 + 2);
          param_2[0x37] = param_2[0x37] & 0xf0 | (byte)(uVar4 >> 0xc);
          uVar9 = *(ushort *)(pcVar14 + 4);
          param_2[0x42] = param_2[0x42] & 0x3f | (byte)((bVar13 & 3) << 6);
          param_2[0xf] = param_2[0xf] & 0x3f | (byte)((bVar1 & 3) << 6);
          param_2[0x36] = (byte)(((uint)uVar4 << 0x14) >> 0x18);
          param_2[0x35] = param_2[0x35] & 0xf | (byte)((uVar4 & 0xf) << 4);
          *(ushort *)(param_3 + 0x37) = uVar9 & uVar4;
          break;
        case 0x13:
switchD_000560dc_caseD_13:
          bVar13 = pcVar14[6];
          uVar4 = *(ushort *)(pcVar14 + 8);
          param_2[0x11] = param_2[0x11] & 0xf0 | (byte)(((uint)bVar13 << 0x19) >> 0x1c);
          uVar9 = *(ushort *)(pcVar14 + 2);
          param_2[0x39] = param_2[0x39] & 0xf0 | (byte)(uVar9 >> 0xc);
          uVar5 = *(ushort *)(pcVar14 + 4);
          param_2[0x10] = param_2[0x10] & 0x1f | (byte)((bVar13 & 7) << 5);
          param_2[0x43] = param_2[0x43] & 0xf1 | (byte)((uVar4 & 7) << 1);
          param_2[0x38] = (byte)(((uint)uVar9 << 0x14) >> 0x18);
          param_2[0x37] = param_2[0x37] & 0xf | (byte)((uVar9 & 0xf) << 4);
          *(ushort *)(param_3 + 0x39) = uVar5 & uVar9;
        }
      }
      uVar16 = uVar16 + 1;
      pcVar14 = pcVar14 + 0xc;
      if (pcVar14 == acStack_28) goto LAB_000561b8;
    }
    pcVar14 = pcVar14 + 0xc;
  } while (pcVar14 != acStack_28);
LAB_000561b8:
  *(byte *)(param_3 + 0x10) = *(byte *)(param_3 + 0x10) | 0x40;
  bVar2 = g_qosEn;
  bVar13 = param_2[0x3a];
  bVar1 = (byte)((*(uint *)(param_1 + 0x14) & 3) << 1);
  param_2[0x3a] = bVar13 & 0xf9 | bVar1;
  iVar10 = *(int *)(param_1 + 0x1c);
  param_2[0x3a] = bVar13 & 1 | bVar1 | (bVar2 & 1) << 3 | (byte)((uVar16 & 0xf) << 4);
  param_2[0x39] = param_2[0x39] & 0xbf | (byte)(((uint)(iVar10 << 0x1d) >> 0x1f) << 6);
  param_2[0x3b] = param_2[0x3b] & 0xe6 | (byte)((uVar16 << 0x1b) >> 0x1f);
  if (*(int *)(param_1 + 0x10) == 0) {
    if ((*(uint *)(param_1 + 0x1c) & 0x400000) != 0) {
LAB_000562d8:
      param_2[0x39] = param_2[0x39] | 0x20;
      if (*(int *)(param_1 + 0x10) == 1) {
        uVar16 = *(uint *)(param_1 + 0x1c);
        goto LAB_000562f4;
      }
    }
  }
  else if (*(int *)(param_1 + 0x10) == 1) {
    uVar16 = *(uint *)(param_1 + 0x1c);
    if ((uVar16 & 0x800000) != 0) goto LAB_000562d8;
LAB_000562f4:
    bVar18 = (uVar16 & 0x400000) != 0;
    bVar13 = 0;
    if (bVar18) {
      bVar13 = g_multiEn;
    }
    if (bVar18) {
      bVar13 = bVar13 == 0;
    }
    param_2[0x39] = param_2[0x39] & 0xef | (bVar13 & 1) << 4;
    goto LAB_00056244;
  }
  param_2[0x39] = param_2[0x39] & 0xef;
LAB_00056244:
  if (macMode == 1) {
    param_2[0x39] = param_2[0x39] & 0xef;
  }
  return 0;
}

