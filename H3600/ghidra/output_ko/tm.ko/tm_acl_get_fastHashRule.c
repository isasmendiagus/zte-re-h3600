// module: tm.ko
// function: tm_acl_get_fastHashRule @ 0x57218
// size: 1488 bytes
//

undefined4 tm_acl_get_fastHashRule(int param_1,byte *param_2,uint param_3,byte *param_4)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;
  byte bVar7;
  uint uVar8;
  undefined4 uVar9;
  uint uVar10;
  bool bVar11;
  undefined1 local_90 [2];
  byte bStack_8e;
  byte local_8c;
  byte local_8b;
  byte local_8a;
  byte local_89;
  byte local_84;
  byte local_83;
  byte local_82;
  byte local_81;
  undefined2 local_7c;
  undefined2 local_7a;
  undefined1 auStack_78 [3];
  byte local_75;
  byte local_70;
  byte local_6f;
  byte local_6e;
  byte local_6d;
  byte local_6c;
  byte local_6b;
  byte local_6a;
  byte local_69;
  byte local_68;
  byte local_67;
  byte local_66;
  byte local_65;
  byte local_64;
  byte local_63;
  byte local_62;
  byte local_61;
  byte local_50;
  byte local_4f;
  byte local_4e;
  byte local_4d;
  byte local_4c;
  byte local_4b;
  byte local_4a;
  byte local_49;
  byte local_48;
  byte local_47;
  byte local_46;
  byte local_45;
  byte local_44;
  byte local_43;
  byte local_42;
  byte local_41;
  undefined2 local_30;
  undefined2 local_2e;
  
  if (param_4 == (byte *)0x0 || param_2 == (byte *)0x0) {
    return 0;
  }
  __memzero(auStack_78,0x50);
  __memzero(local_90,0x18);
  if (g_pktLenChged < 1) {
    uVar10 = 0;
    if (g_pktLenChged != 0) {
      uVar10 = (uint)(g_pktLenChged * -0x4000000) >> 0x1c | 0x10;
    }
  }
  else {
    uVar10 = (uint)(g_pktLenChged << 0x19) >> 0x1b;
  }
  g_pktLenChged = 0;
  if (g_dsliteSet == '\0') {
    if (g_dsliteDel == '\0') {
      if (g_v6rdSet == '\0') {
        uVar4 = (uint)*(ushort *)(param_2 + 2);
        if (g_v6rdDel != '\0') {
          uVar4 = uVar4 + 0x14;
        }
      }
      else {
        uVar4 = *(ushort *)(param_2 + 2) - 0x14;
      }
    }
    else {
      uVar4 = *(ushort *)(param_2 + 2) + 0x28;
    }
  }
  else {
    uVar4 = *(ushort *)(param_2 + 2) - 0x28;
  }
  param_4[0x12] = param_4[0x12] & 0xf7 | 0x10;
  iVar6 = *(int *)(param_2 + 0x10);
  param_4[0x10] = param_4[0x10] & 0x7f;
  param_4[0x11] = 0;
  param_4[0x12] = param_4[0x12] & 0xf8 | (iVar6 == 0) << 2;
  bVar1 = param_2[5];
  bVar2 = param_2[4];
  param_4[0x10] = param_4[0x10] | 0x40;
  param_4[8] = param_4[8] & 0xf | (byte)((bVar2 & 0xf) << 4);
  param_4[9] = param_4[9] & 0xfc | (byte)(((bVar1 & 1) << 5 | bVar2 & 0x1f) >> 4) | 4;
  uVar8 = *(uint *)(param_2 + 0x10);
  param_4[0xf] = param_4[0xf] & 1;
  param_4[0x10] = param_4[0x10] & 0xc0 | (byte)((uVar8 & 1) << 5);
  bVar11 = (*(uint *)(param_2 + 0x1c) & 4) != 0;
  uVar8 = 0;
  if (bVar11) {
    uVar8 = (uint)param_2[1];
  }
  param_4[0xd] = 0;
  if (bVar11) {
    uVar8 = uVar8 & 7;
  }
  param_4[0xe] = (byte)(uVar8 << 6);
  param_4[0xf] = param_4[0xf] & 0xfe | (byte)(uVar8 >> 2);
  param_4[0xc] = param_4[0xc] & 0x1f;
  param_4[0xb] = param_4[0xb] & 0x7f | *param_2 << 7;
  bVar1 = param_4[6];
  param_4[0xc] = param_4[0xc] & 0xe0 | (byte)(((uint)*param_2 << 0x1a) >> 0x1b);
  bVar2 = param_2[0xb8];
  bVar3 = (byte)((uVar4 & 7) << 5);
  param_4[7] = (byte)(((uVar4 & 0xffff) << 0x15) >> 0x18);
  param_4[10] = 0;
  param_4[6] = bVar1 & 0x1f | bVar3 | 0x10;
  param_4[8] = param_4[8] & 0xf8 | 8 | (byte)(((uVar4 & 0xffff) << 0x12) >> 0x1d);
  param_4[0xb] = param_4[0xb] & 0x80 | (bVar2 & 0x1f) << 2;
  param_4[9] = param_4[9] & 7;
  bVar2 = param_2[0xb1];
  param_4[4] = (byte)((param_3 << 0x11) >> 0x18);
  param_4[5] = ~((byte)~(byte)(((uint)param_4[5] << 0x1a) >> 0x18) >> 2) & 0xc1 |
               (byte)(uVar10 << 1) | 1;
  param_4[6] = bVar1 & 0x11 | bVar3 | 0x10 | (bVar2 & 7) << 1 | 1;
  param_4[3] = (byte)((param_3 & 0x7f) << 1) | 1;
  bVar2 = *param_4;
  bVar1 = param_2[0xb0] << 7;
  bVar7 = bVar2 & 0x7f | bVar1;
  *param_4 = bVar7;
  bVar3 = param_2[0xb0];
  *param_4 = bVar7 | 0x40;
  param_4[1] = param_4[1] & 0xf0 | (byte)(((uint)bVar3 << 0x1b) >> 0x1c);
  bVar3 = (param_2[0xb1] & 7) << 3;
  *param_4 = bVar2 & 0x47 | bVar1 | 0x40 | bVar3 | 4;
  *param_4 = bVar2 & 0x44 | bVar1 | 0x40 | bVar3 | 4 | (byte)*(undefined4 *)(param_2 + 0x18) & 3;
  if (*(int *)(param_2 + 0x10) == 1) {
    switch((uint)*(ushort *)(param_2 + 0xb2)) {
    case 0:
      uVar10 = 1;
      break;
    case 1:
      uVar10 = 2;
      break;
    case 2:
      uVar10 = 3;
      break;
    case 3:
      uVar10 = 4;
      break;
    case 4:
      uVar10 = 5;
      break;
    default:
      printk("ERROR:(%s:%d)","tm_acl_v2.c",0x25fe);
      printk("Invalid target uni port!\n");
      uVar10 = 0;
      break;
    case 6:
      uVar10 = 6;
      break;
    case 7:
      uVar10 = 7;
      break;
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
    case 0x1e:
    case 0x1f:
      uVar10 = *(ushort *)(param_2 + 0xb2) & 0xfff;
    }
    param_4[2] = (byte)(uVar10 >> 4);
    param_4[1] = param_4[1] & 0xf | (byte)((uVar10 & 0xf) << 4);
  }
  else {
    if (*(int *)(param_2 + 0x10) != 0) {
      printk("ERROR:(%s:%d)","tm_acl_v2.c",0x2609);
      printk("Undefined Direct Found \n");
      return 0;
    }
    param_4[1] = param_4[1] & 0xf | param_2[0xb2] << 4;
    param_4[2] = (byte)(((uint)*(ushort *)(param_2 + 0xb2) << 0x14) >> 0x18);
  }
  if (param_1 == 0) {
    memcpy(auStack_78,param_2 + 0x60,0x50);
    *(ushort *)(param_4 + 0x13) = (ushort)local_75 << 8;
    *(ushort *)(param_4 + 0x15) = (ushort)local_6f + (ushort)local_70 * 0x100;
    *(ushort *)(param_4 + 0x1d) = (ushort)local_67 + (ushort)local_68 * 0x100;
    *(ushort *)(param_4 + 0x17) = (ushort)local_6d + (ushort)local_6e * 0x100;
    *(ushort *)(param_4 + 0x19) = (ushort)local_6b + (ushort)local_6c * 0x100;
    *(ushort *)(param_4 + 0x1b) = (ushort)local_69 + (ushort)local_6a * 0x100;
    *(ushort *)(param_4 + 0x1f) = (ushort)local_65 + (ushort)local_66 * 0x100;
    *(ushort *)(param_4 + 0x21) = (ushort)local_63 + (ushort)local_64 * 0x100;
    *(ushort *)(param_4 + 0x23) = (ushort)local_61 + (ushort)local_62 * 0x100;
    *(ushort *)(param_4 + 0x25) = (ushort)local_4f + (ushort)local_50 * 0x100;
    *(ushort *)(param_4 + 0x27) = (ushort)local_4d + (ushort)local_4e * 0x100;
    *(ushort *)(param_4 + 0x2d) = (ushort)local_47 + (ushort)local_48 * 0x100;
    *(ushort *)(param_4 + 0x29) = (ushort)local_4b + (ushort)local_4c * 0x100;
    *(ushort *)(param_4 + 0x2b) = (ushort)local_49 + (ushort)local_4a * 0x100;
    *(ushort *)(param_4 + 0x2f) = (ushort)local_45 + (ushort)local_46 * 0x100;
    *(ushort *)(param_4 + 0x31) = (ushort)local_43 + (ushort)local_44 * 0x100;
    *(ushort *)(param_4 + 0x33) = (ushort)local_41 + (ushort)local_42 * 0x100;
    *(undefined2 *)(param_4 + 0x35) = local_30;
    *(undefined2 *)(param_4 + 0x37) = local_2e;
    return 1;
  }
  uVar5 = *(undefined4 *)(param_2 + 100);
  uVar9 = *(undefined4 *)(param_2 + 0x6c);
  local_84 = (byte)uVar9;
  local_8c = (byte)uVar5;
  local_82 = (byte)((uint)uVar9 >> 0x10);
  local_81 = (byte)((uint)uVar9 >> 0x18);
  local_8a = (byte)((uint)uVar5 >> 0x10);
  local_7c = (undefined2)*(undefined4 *)(param_2 + 0x74);
  local_7a = (undefined2)((uint)*(undefined4 *)(param_2 + 0x74) >> 0x10);
  bStack_8e = (byte)((uint)*(undefined4 *)(param_2 + 0x60) >> 0x10);
  local_83 = (byte)((uint)uVar9 >> 8);
  local_8b = (byte)((uint)uVar5 >> 8);
  local_89 = (byte)((uint)uVar5 >> 0x18);
  *(ushort *)(param_4 + 0x1b) = (ushort)local_81 + (ushort)local_82 * 0x100;
  *(ushort *)(param_4 + 0x19) = (ushort)local_83 + (ushort)local_84 * 0x100;
  *(undefined2 *)(param_4 + 0x1d) = local_7c;
  *(undefined2 *)(param_4 + 0x1f) = local_7a;
  *(ushort *)(param_4 + 0x15) = (ushort)local_8b + (ushort)local_8c * 0x100;
  *(ushort *)(param_4 + 0x17) = (ushort)local_89 + (ushort)local_8a * 0x100;
  *(ushort *)(param_4 + 0x13) = (ushort)bStack_8e;
  return 1;
}

