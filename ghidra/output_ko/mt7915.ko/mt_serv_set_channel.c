// module: mt7915.ko
// function: mt_serv_set_channel @ 0x250814
// size: 948 bytes
//

undefined4 mt_serv_set_channel(int *param_1)

{
  uint uVar1;
  uint uVar2;
  char cVar3;
  byte bVar4;
  undefined2 uVar5;
  uint uVar6;
  byte bVar7;
  uint uVar8;
  int iVar9;
  int *piVar10;
  uint uVar11;
  int iVar12;
  uint uVar13;
  int iVar14;
  byte abStack_38 [20];
  
  uVar11 = (uint)*(byte *)(param_1 + 0x133);
  iVar14 = *param_1;
  abStack_38[2] = 0xfe;
  abStack_38[3] = 2;
  bVar7 = *(byte *)(iVar14 + 0x55);
  abStack_38[4] = 0xfa;
  abStack_38[5] = 0xfe;
  abStack_38[6] = 2;
  abStack_38[7] = 6;
  if (*(char *)(iVar14 + 0x34) != '\0') {
    bVar7 = bVar7 >> 1;
  }
  uVar13 = (uint)bVar7;
  iVar12 = param_1[0x7c4];
  abStack_38[8] = 0xf2;
  abStack_38[9] = 0xf6;
  abStack_38[10] = 0xfa;
  abStack_38[0xb] = 0xfe;
  abStack_38[0xc] = 2;
  abStack_38[0xd] = 6;
  abStack_38[0xe] = 10;
  abStack_38[0xf] = 0xe;
  if (uVar13 == 0) {
    param_1[uVar11 * 0x346 + 0x44a] = 0;
    *(byte *)((int)param_1 + uVar11 * 0xd18 + 0x113f) = bVar7;
    uVar5 = 0;
  }
  else {
    uVar6 = 0;
    uVar8 = 0;
    do {
      uVar1 = 1 << (uVar8 & 0xff);
      uVar8 = uVar8 + 1;
      if ((uVar1 & param_1[uVar11 * 0x346 + 0x44a]) != 0) {
        uVar6 = uVar1 & 0xff | uVar6;
      }
    } while (uVar8 != uVar13);
    param_1[uVar11 * 0x346 + 0x44a] = uVar6;
    uVar8 = uVar13;
    do {
      uVar1 = uVar8 - 1;
      if ((uVar6 >> (uVar1 & 0xff) & 1) != 0) goto LAB_002508f8;
      uVar8 = uVar1;
    } while (uVar1 != 0);
    uVar8 = 1;
LAB_002508f8:
    if (uVar8 < uVar13) {
      bVar7 = (byte)uVar8;
    }
    uVar6 = 0;
    uVar8 = 0;
    *(byte *)((int)param_1 + uVar11 * 0xd18 + 0x113f) = bVar7;
    do {
      uVar1 = uVar8 & 0xff;
      uVar2 = uVar8 & 0xff;
      uVar8 = uVar8 + 1;
      if (((int)(uint)*(ushort *)((int)param_1 + uVar11 * 0xd18 + 0x112e) >> uVar2 & 1U) != 0) {
        uVar6 = uVar6 | 1 << uVar1 & 0xffU;
      }
      uVar5 = (undefined2)uVar6;
    } while (uVar8 != uVar13);
  }
  *(undefined2 *)((int)param_1 + uVar11 * 0xd18 + 0x112e) = uVar5;
  *(char *)(param_1 + uVar11 * 0x346 + 0x450) = (char)uVar5;
  cVar3 = *(char *)((int)param_1 + uVar11 * 0xd18 + 0x1143);
  bVar7 = *(byte *)((int)param_1 + uVar11 * 0xd18 + 0x1133);
  uVar6 = (uint)bVar7;
  bVar4 = *(byte *)(param_1 + uVar11 * 0x346 + 0x44c);
  uVar13 = (uint)bVar4;
  switch(*(undefined1 *)((int)param_1 + uVar11 * 0xd18 + 0x1136)) {
  case 0:
    uVar8 = (uint)*(byte *)((int)param_1 + uVar11 * 0xd18 + 0x1137);
    *(byte *)((int)param_1 + uVar11 * 0xd18 + 0x1132) = bVar4;
    if (*(byte *)((int)param_1 + uVar11 * 0xd18 + 0x1136) < uVar8) {
      if (uVar8 == 2) {
        if (3 < uVar6) goto LAB_00250b88;
        uVar8 = (uint)(char)abStack_38[uVar6 + 4];
        uVar6 = (uint)abStack_38[uVar6 + 4];
      }
      else if ((uVar8 < 2) || (1 < uVar8 - 5)) {
        if (1 < uVar6) goto LAB_00250b88;
        uVar8 = (uint)(char)abStack_38[uVar6 + 2];
        uVar6 = (uint)abStack_38[uVar6 + 2];
      }
      else {
        if (7 < uVar6) goto LAB_00250b88;
        uVar8 = (uint)(char)abStack_38[uVar6 + 8];
        uVar6 = (uint)abStack_38[uVar6 + 8];
      }
    }
    else {
      uVar8 = 0;
      uVar6 = uVar8;
    }
    goto LAB_002509d8;
  case 1:
    if (1 < uVar6) goto LAB_00250b88;
    piVar10 = param_1 + uVar11 * 0x346;
    uVar6 = (uint)abStack_38[uVar6 + 2];
    break;
  case 2:
    if (3 < uVar6) goto LAB_00250b88;
    piVar10 = param_1 + uVar11 * 0x346;
LAB_00250aa0:
    uVar6 = (uint)abStack_38[uVar6 + 4];
    break;
  default:
    printk("%s: set channel fail, ","mt_serv_set_channel",param_1 + uVar11 * 0x346 + 0x138);
    printk("bw=%d is invalid\n",*(undefined1 *)((int)param_1 + uVar11 * 0xd18 + 0x1136));
    return 0x605;
  case 5:
    if (7 < uVar6) goto LAB_00250b88;
    piVar10 = param_1 + uVar11 * 0x346;
    uVar6 = (uint)abStack_38[uVar6 + 8];
    break;
  case 6:
    if (7 < uVar6) goto LAB_00250b88;
    if (cVar3 == '\0') {
      printk("%s: set channel fail, ","mt_serv_set_channel",param_1 + uVar11 * 0x346 + 0x138);
      printk("second control channel is 0 for bw 80+80\n");
      return 0x605;
    }
    piVar10 = param_1 + uVar11 * 0x346;
    if (uVar6 < 4) goto LAB_00250aa0;
    uVar6 = (uint)abStack_38[uVar6];
  }
  uVar8 = (uint)(char)uVar6;
  *(byte *)((int)piVar10 + 0x1132) = bVar4 + (char)uVar6;
LAB_002509d8:
  iVar9 = uVar13 + uVar8;
  uVar13 = uVar13 - uVar8;
  if ((0 < iVar9) && (0 < (int)uVar13)) {
    *(byte *)((int)param_1 + uVar11 * 0xd18 + 0x1133) = bVar7;
    *(char *)(param_1 + uVar11 * 0x346 + 0x44d) = (char)uVar6;
    *(byte *)(param_1 + uVar11 * 0x346 + 0x44c) = bVar4;
    *(char *)((int)param_1 + uVar11 * 0xd18 + 0x1143) = cVar3;
    iVar14 = (**(code **)(iVar12 + 0x78))(iVar14,uVar11);
    if (iVar14 == 0) {
      return 0;
    }
  }
LAB_00250b88:
  printk("%s: set channel fail, ","mt_serv_set_channel");
  printk("control channel: %d|%d\n",*(undefined1 *)((int)param_1 + uVar11 * 0xd18 + 0x1132),uVar13);
  return 0x605;
}

