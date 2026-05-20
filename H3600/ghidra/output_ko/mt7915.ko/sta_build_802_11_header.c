// module: mt7915.ko
// function: sta_build_802_11_header @ 0x55828
// size: 812 bytes
//

void sta_build_802_11_header(int param_1,int param_2)

{
  undefined2 uVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  char cVar5;
  byte bVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar11 = *(int *)(param_2 + 8);
  uVar9 = (uint)*(byte *)(iVar2 + 2);
  iVar2 = GetStaCfgByWdev(param_1,*(undefined4 *)(iVar11 + 4));
  if (iVar2 == 0) {
    printk(&_LC1,0x136);
    dump_stack();
    return;
  }
  if (iVar11 == 0) {
    printk(&_LC21,0x13e);
    dump_stack();
    return;
  }
  iVar10 = *(int *)(param_2 + 0x58);
  *(undefined1 *)(param_2 + 0x2c) = 0x18;
  iVar8 = iVar10 + uVar9;
  *(int *)(param_2 + 0x5c) = iVar8;
  __memzero(iVar8,0x18);
  *(byte *)(iVar8 + 1) = *(byte *)(iVar8 + 1) & 0xfd;
  bVar6 = *(byte *)(iVar10 + uVar9);
  *(byte *)(iVar10 + uVar9) = bVar6 & 0xf3 | 8;
  if ((*(uint *)(param_2 + 0x18) & 0x10) == 0) {
    cVar5 = '\0';
  }
  else {
    cVar5 = '\b';
  }
  *(byte *)(iVar10 + uVar9) = bVar6 & 3 | 8 | cVar5 << 4;
  if ((*(uint *)(param_2 + 0x18) & 0x10) == 0) {
    *(byte *)(iVar8 + 0x16) = *(byte *)(iVar8 + 0x16) & 0xf | *(char *)(iVar11 + 0x12) << 4;
    *(char *)(iVar8 + 0x17) = (char)(((uint)*(ushort *)(iVar11 + 0x12) << 0x14) >> 0x18);
    *(ushort *)(iVar11 + 0x12) = *(short *)(iVar11 + 0x12) + 1U & 0xfff;
  }
  else {
    iVar7 = iVar11 + (*(byte *)(param_2 + 0x1c) + 8) * 2;
    *(byte *)(iVar8 + 0x16) = *(byte *)(iVar8 + 0x16) & 0xf | *(char *)(iVar7 + 4) << 4;
    *(char *)(iVar8 + 0x17) = (char)(((uint)*(ushort *)(iVar7 + 4) << 0x14) >> 0x18);
    iVar7 = iVar11 + (uint)*(byte *)(param_2 + 0x1c) * 2;
    *(ushort *)(iVar7 + 0x14) = *(short *)(iVar7 + 0x14) + 1U & 0xfff;
  }
  *(byte *)(iVar8 + 0x16) = *(byte *)(iVar8 + 0x16) & 0xf0;
  *(byte *)(iVar8 + 1) =
       *(byte *)(iVar8 + 1) & 0xdf | (byte)(((uint)(*(int *)(param_2 + 0x18) << 0x19) >> 0x1f) << 5)
  ;
  if (*(char *)(iVar2 + 0x4060) == '\x01') {
    *(undefined4 *)(iVar8 + 4) = *(undefined4 *)(iVar11 + 0xb);
    *(undefined2 *)(iVar8 + 8) = *(undefined2 *)(iVar11 + 0xf);
    iVar11 = *(int *)(iVar11 + 4);
    *(undefined4 *)(iVar8 + 10) = *(undefined4 *)(iVar11 + 0x1b);
    *(undefined2 *)(iVar8 + 0xe) = *(undefined2 *)(iVar11 + 0x1f);
    puVar4 = *(undefined4 **)(param_2 + 0x24);
    *(undefined4 *)(iVar8 + 0x10) = *puVar4;
    uVar1 = *(undefined2 *)(puVar4 + 1);
    *(byte *)(iVar8 + 1) = *(byte *)(iVar8 + 1) | 1;
    *(undefined2 *)(iVar8 + 0x14) = uVar1;
  }
  else if ((*(uint *)(param_1 + 0x795124) & 2) != 0) {
    puVar4 = *(undefined4 **)(param_2 + 0x24);
    *(undefined4 *)(iVar8 + 4) = *puVar4;
    *(undefined2 *)(iVar8 + 8) = *(undefined2 *)(puVar4 + 1);
    iVar11 = *(int *)(iVar11 + 4);
    *(undefined4 *)(iVar8 + 10) = *(undefined4 *)(iVar11 + 0x1b);
    *(undefined2 *)(iVar8 + 0xe) = *(undefined2 *)(iVar11 + 0x1f);
    *(undefined4 *)(iVar8 + 0x10) = *(undefined4 *)(iVar2 + 0x212428);
    uVar1 = *(undefined2 *)(iVar2 + 0x21242c);
    *(byte *)(iVar8 + 1) = *(byte *)(iVar8 + 1) & 0xfe;
    *(undefined2 *)(iVar8 + 0x14) = uVar1;
  }
  if ((*(uint *)(param_2 + 100) & 1) == 0) {
    *(byte *)(iVar8 + 1) = *(byte *)(iVar8 + 1) | 0x40;
  }
  if (*(char *)(param_1 + 0x794cc6) == '\0') {
    iVar2 = RtmpPktPmBitCheck(param_1,iVar2);
    *(byte *)(iVar8 + 1) = *(byte *)(iVar8 + 1) & 0xef | (iVar2 == 1) << 4;
  }
  else {
    *(byte *)(iVar8 + 1) = *(byte *)(iVar8 + 1) | 0x10;
  }
  if ((*(uint *)(param_2 + 0x18) & 0x10) == 0) {
    cVar5 = *(char *)(param_2 + 0x2c);
  }
  else {
    iVar2 = *(int *)(param_2 + 0x5c);
    uVar3 = (uint)*(byte *)(param_2 + 0x2c);
    bVar6 = *(byte *)(param_2 + 0x1c) & 0xf |
            *(char *)(param_1 + (uint)*(byte *)(param_2 + 1) + 0x79511c) << 5;
    *(byte *)(iVar2 + uVar3) = bVar6;
    if (*(char *)(param_2 + 5) == '\x04') {
      *(byte *)(iVar2 + uVar3) = ~((byte)~(byte)(((uint)bVar6 << 0x19) >> 0x18) >> 1);
    }
    *(undefined1 *)(iVar2 + uVar3 + 1) = 0;
    cVar5 = *(char *)(param_2 + 0x2c) + '\x02';
    *(char *)(param_2 + 0x2c) = cVar5;
  }
  *(char *)(param_2 + 0x35) = cVar5;
  *(byte *)(param_2 + 0x83) = (byte)(((uint)*(byte *)(iVar10 + uVar9) << 0x1c) >> 0x1e);
  *(byte *)(param_2 + 0x84) = *(byte *)(iVar10 + uVar9) >> 4;
  return;
}

