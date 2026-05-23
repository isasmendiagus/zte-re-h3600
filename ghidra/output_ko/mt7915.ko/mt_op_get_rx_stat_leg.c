// module: mt7915.ko
// function: mt_op_get_rx_stat_leg @ 0x257b7c
// size: 704 bytes
//

undefined4 mt_op_get_rx_stat_leg(int param_1,uint *param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint *puVar3;
  byte bVar4;
  byte bVar5;
  int iVar6;
  uint *puVar7;
  byte bVar8;
  uint *puVar9;
  undefined1 auStack_7c [2];
  ushort local_7a;
  ushort local_78;
  ushort local_76;
  ushort local_74;
  uint local_70;
  ushort local_6c;
  ushort local_6a;
  ushort local_68;
  ushort local_66;
  ushort local_64;
  ushort local_62;
  ushort local_60;
  ushort local_5e;
  ushort local_5c;
  ushort local_5a;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    uVar2 = 0x503;
  }
  else {
    if (*(char *)(param_1 + 0x34) == '\0') {
      iVar6 = 0xa7bf40;
      bVar8 = 1;
      param_2[0x1a] = *(uint *)(iVar1 + 0xa7bfe4);
      param_2[0x1b] = *(uint *)(iVar1 + 0xa7bfe8);
      param_2[0x1c] = *(uint *)(iVar1 + 0xa7bfec);
      param_2[0x1d] = *(uint *)(iVar1 + 0xa7bff0);
      param_2[0x1e] = *(uint *)(iVar1 + 0xa7bff4);
      param_2[0x1f] = *(uint *)(iVar1 + 0xa7bff8);
      param_2[0x20] = *(uint *)(iVar1 + 0xa7bffc);
      param_2[0x21] = *(uint *)(iVar1 + 0xa7c000);
      param_2[0x11] = *(uint *)(iVar1 + 0xa7bfd4);
      param_2[0x12] = *(uint *)(iVar1 + 0xa7bfd8);
      param_2[0x2d] = *(uint *)(iVar1 + 0xa7bfdc);
      param_2[0x2e] = *(uint *)(iVar1 + 0xa7bfe0);
      param_2[0x14] = *(uint *)(iVar1 + 0xa7bf84);
      param_2[0x15] = *(uint *)(iVar1 + 0xa7bf88);
      param_2[0x2f] = *(uint *)(iVar1 + 0xa7bf8c);
      param_2[0x30] = *(uint *)(iVar1 + 0xa7bf90);
    }
    else {
      iVar6 = 0xa7c0a8;
      bVar8 = 2;
      param_2[0x1a] = *(uint *)(iVar1 + 0xa7bfe4);
      param_2[0x1b] = *(uint *)(iVar1 + 0xa7bfe8);
      param_2[0x1e] = *(uint *)(iVar1 + 0xa7bff4);
      param_2[0x1f] = *(uint *)(iVar1 + 0xa7bff8);
      param_2[0x11] = *(uint *)(iVar1 + 0xa7bfd4);
      param_2[0x12] = *(uint *)(iVar1 + 0xa7bfd8);
      param_2[0x14] = *(uint *)(iVar1 + 0xa7bf84);
      param_2[0x15] = *(uint *)(iVar1 + 0xa7bf88);
      param_2[0x1c] = *(uint *)(iVar1 + 0xa7c14c);
      param_2[0x1d] = *(uint *)(iVar1 + 0xa7c150);
      param_2[0x20] = *(uint *)(iVar1 + 0xa7c15c);
      param_2[0x21] = *(uint *)(iVar1 + 0xa7c160);
      param_2[0x2d] = *(uint *)(iVar1 + 0xa7c13c);
      param_2[0x2e] = *(uint *)(iVar1 + 0xa7c140);
      param_2[0x2f] = *(uint *)(iVar1 + 0xa7c0ec);
      param_2[0x30] = *(uint *)(iVar1 + 0xa7c0f0);
    }
    puVar7 = (uint *)(iVar1 + iVar6);
    bVar5 = 0;
    do {
      chip_get_rx_stat(iVar1,bVar5,auStack_7c);
      bVar4 = bVar5 + 1;
      if (bVar5 == 1) {
        param_2[0x18] = (uint)local_7a;
        param_2[0x36] = (uint)local_78;
        param_2[0x35] = (uint)local_74;
        param_2[0x19] = local_70;
        param_2[0x37] = (uint)local_68;
        param_2[0x38] = (uint)local_66;
        param_2[0x39] = (uint)local_64;
        param_2[0x3a] = (uint)local_62;
        param_2[0x3b] = (uint)local_60;
        param_2[0x3c] = (uint)local_5e;
        param_2[0x3d] = (uint)local_5c;
        param_2[0x3e] = (uint)local_5a;
        break;
      }
      param_2[0x45] = (uint)local_76;
      *param_2 = (uint)local_7a;
      param_2[0x17] = (uint)local_78;
      param_2[0x16] = (uint)local_74;
      param_2[1] = local_70;
      param_2[4] = (uint)local_68;
      param_2[5] = (uint)local_66;
      param_2[6] = (uint)local_64;
      param_2[7] = (uint)local_62;
      param_2[8] = (uint)local_60;
      param_2[9] = (uint)local_5e;
      param_2[0xe] = (uint)local_5c;
      param_2[0xf] = (uint)local_5a;
      param_2[2] = (uint)local_6c;
      param_2[3] = (uint)local_6a;
      bVar5 = bVar4;
    } while (bVar4 < bVar8);
    puVar9 = puVar7 + 0x14;
    puVar3 = puVar7 + 0x34;
    param_2[0x13] = puVar7[1];
    iVar1 = 0;
    do {
      puVar7 = puVar7 + 1;
      iVar6 = iVar1 + 1;
      param_2[iVar1 + 0x4e] = *puVar7;
      puVar9 = puVar9 + 1;
      param_2[iVar1 + 0x5e] = *puVar9;
      puVar3 = puVar3 + 1;
      param_2[iVar1 + 0x6e] = *puVar3;
      iVar1 = iVar6;
    } while (iVar6 != 0x10);
    uVar2 = 0;
  }
  return uVar2;
}

