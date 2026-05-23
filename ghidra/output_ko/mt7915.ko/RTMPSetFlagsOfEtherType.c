// module: mt7915.ko
// function: RTMPSetFlagsOfEtherType @ 0xc6dc8
// size: 424 bytes
//

void RTMPSetFlagsOfEtherType(int param_1,int param_2,int param_3,int param_4)

{
  byte bVar1;
  short sVar2;
  ushort uVar3;
  uint uVar4;
  ushort uVar5;
  int iVar6;
  int iVar7;
  int extraout_r12;
  int iVar8;
  bool bVar9;
  int iVar10;
  
  if (param_2 == 0 || param_1 == 0) {
    return;
  }
  if (param_4 == 0 || param_3 == 0) {
    return;
  }
  iVar7 = 0;
  uVar3 = *(ushort *)(param_3 + 8);
  iVar10 = param_4;
  uVar4 = HcGetMaxStaNum();
  bVar9 = uVar3 < uVar4;
  iVar8 = extraout_r12;
  if (bVar9) {
    iVar8 = (uint)*(ushort *)(param_3 + 8) * 0x14c0 + param_1;
    iVar7 = param_3;
  }
  iVar6 = *(int *)(param_2 + 0xcc);
  if (bVar9) {
    iVar7 = iVar8 + 0xa1d20;
  }
  if (iVar6 == 0) {
    printk(&_LC10,0x72c);
    dump_stack();
  }
  sVar2 = CONCAT11(*(undefined1 *)(iVar6 + 0xc),*(undefined1 *)(iVar6 + 0xd));
  if (sVar2 == 0x806) {
    uVar4 = 0;
    *(byte *)(param_2 + 0x4e) = *(byte *)(param_2 + 0x4e) | 2;
  }
  else if (sVar2 == -0x7923) {
    uVar4 = (uint)*(byte *)(iVar6 + 0x14);
  }
  else if (sVar2 == 0x800) {
    if (*(uint *)(param_2 + 100) < 0x23) {
      printk(&_LC55,0x7aa,0x86dd,*(uint *)(param_2 + 100),iVar10);
      dump_stack();
    }
    bVar1 = *(byte *)(param_2 + 0x30);
    *(byte *)(param_2 + 0x30) = bVar1 | 4;
    uVar4 = (uint)*(byte *)(iVar6 + 0x17);
    if (uVar4 == 1) {
      *(undefined1 *)(param_2 + 0x36) = 2;
      *(byte *)(param_2 + 0x4e) = *(byte *)(param_2 + 0x4e) | 1;
    }
    else if (uVar4 == 0x11) {
      uVar5 = *(ushort *)(iVar6 + 0x22) << 8 | *(ushort *)(iVar6 + 0x22) >> 8;
      uVar3 = *(ushort *)(iVar6 + 0x24) << 8 | *(ushort *)(iVar6 + 0x24) >> 8;
      if ((uVar3 == 0x43 && uVar5 == 0x44) || (uVar3 == 0x44 && uVar5 == 0x43)) {
        *(byte *)(param_2 + 0x30) = bVar1 | 5;
      }
    }
  }
  else {
    uVar4 = 0;
  }
  if (*(short *)(param_4 + 0x8d4) == 0x101) {
    *(undefined1 *)(param_2 + 0x2a) = *(undefined1 *)(param_4 + 0x8d6);
  }
  if (iVar7 == 0) {
    return;
  }
  if (*(int *)(iVar7 + 0xccc) == -1) {
    return;
  }
  if ((*(uint *)(iVar7 + 0xcd0) != 0) && (*(uint *)(iVar7 + 0xcd0) != uVar4)) {
    return;
  }
  *(char *)(param_2 + 0x2a) = (char)*(int *)(iVar7 + 0xccc);
  return;
}

