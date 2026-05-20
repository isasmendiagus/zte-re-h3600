// module: mt7915.ko
// function: RTMPIoctlQueryBaTable @ 0x3b888
// size: 852 bytes
//

void RTMPIoctlQueryBaTable(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  ushort *puVar3;
  uint extraout_r1;
  int iVar4;
  undefined1 *puVar5;
  undefined1 *puVar6;
  undefined1 uVar7;
  int iVar8;
  uint uVar9;
  short sVar10;
  uint uVar11;
  uint uVar12;
  undefined8 uVar13;
  undefined1 auStack_38 [4];
  int local_34;
  int local_30;
  int local_2c;
  
  iVar1 = vmalloc(0xc02);
  if (iVar1 == 0) {
    return;
  }
  RTMPZeroMemory(iVar1,0xc02);
  uVar12 = 0;
  uVar11 = 0;
  sVar10 = *(short *)(param_1 + 0x285920);
  local_34 = param_1 + 0x1c0;
  while( true ) {
    uVar2 = HcGetMaxStaNum(param_1);
    if (sVar10 == 0 || uVar2 <= (uVar12 & 0xffff)) break;
    iVar8 = (uVar12 & 0xffff) * 0x14c0;
    iVar4 = param_1 + iVar8;
    if (((*(int *)(iVar4 + 0xa1d20) == 0x20001) && (*(int *)(iVar4 + 0xa1e1c) == 2)) &&
       (*(short *)(iVar4 + 0xa29e0) != 0 && uVar11 < 0x20)) {
      local_30 = uVar11 * 0x30;
      local_2c = iVar8;
      memmove((void *)(iVar1 + local_30),(void *)(param_1 + iVar8 + 0xa1e0c),6);
      puVar3 = (ushort *)(param_1 + local_2c + 0xa2a02);
      puVar5 = (undefined1 *)(iVar1 + local_30 + 8);
      do {
        puVar3 = puVar3 + 1;
        puVar6 = puVar5 + 1;
        uVar7 = 0;
        if (*puVar3 != 0) {
          uVar7 = (undefined1)*(undefined2 *)(local_34 + (uint)*puVar3 * 0x48 + 0x1b004);
        }
        *puVar5 = uVar7;
        puVar5 = puVar6;
      } while (puVar6 != (undefined1 *)(iVar1 + local_30 + 0x10));
      sVar10 = sVar10 + -1;
      uVar11 = uVar11 + 1 & 0xffff;
      *(char *)(iVar1 + 0xc00) = *(char *)(iVar1 + 0xc00) + '\x01';
    }
    uVar12 = uVar12 + 1;
  }
  uVar12 = 0;
  local_34 = param_1 + 0x1c0;
  sVar10 = *(short *)(param_1 + 0x285920);
  uVar11 = uVar12;
  while( true ) {
    uVar2 = HcGetMaxStaNum(param_1);
    if (sVar10 == 0 || uVar2 <= (uVar11 & 0xffff)) break;
    iVar8 = (uVar11 & 0xffff) * 0x14c0;
    iVar4 = param_1 + iVar8;
    if (((*(int *)(iVar4 + 0xa1d20) == 0x20001) && (*(int *)(iVar4 + 0xa1e1c) == 2)) &&
       (*(short *)(iVar4 + 0xa29de) != 0 && uVar12 < 0x20)) {
      local_30 = uVar12 * 0x30;
      local_2c = iVar8;
      memmove((void *)(iVar1 + local_30 + 0x600),(void *)(param_1 + iVar8 + 0xa1e0c),6);
      *(char *)(iVar1 + local_30 + 0x606) = (char)*(undefined2 *)(iVar4 + 0xa29de);
      puVar3 = (ushort *)(param_1 + local_2c + 0xa29f2);
      puVar5 = (undefined1 *)(iVar1 + local_30 + 0x608);
      do {
        puVar3 = puVar3 + 1;
        puVar6 = puVar5 + 1;
        uVar7 = 0;
        if (*puVar3 != 0) {
          uVar7 = (undefined1)*(undefined2 *)(local_34 + (uint)*puVar3 * 0x60 + 0x14);
        }
        *puVar5 = uVar7;
        puVar5 = puVar6;
      } while (puVar6 != (undefined1 *)(iVar1 + local_30 + 0x610));
      sVar10 = sVar10 + -1;
      uVar12 = uVar12 + 1 & 0xffff;
      *(char *)(iVar1 + 0xc01) = *(char *)(iVar1 + 0xc01) + '\x01';
    }
    uVar11 = uVar11 + 1;
  }
  uVar12 = *(uint *)(param_2 + 0x10);
  *(undefined2 *)(param_2 + 0x14) = 0xc02;
  uVar9 = *(uint *)(((uint)auStack_38 & 0xffffe000) + 8);
  uVar2 = uVar12 + 0xc02;
  uVar11 = uVar2;
  if (uVar12 < 0xfffff3fe) {
    uVar11 = uVar2 - (uVar9 + 1);
  }
  if (uVar12 < 0xfffff3fe && uVar2 <= uVar9) {
    uVar9 = 0;
  }
  if (uVar9 == 0) {
    uVar13 = __copy_to_user(uVar12,iVar1);
    uVar11 = (uint)((ulonglong)uVar13 >> 0x20);
    if ((int)uVar13 == 0) {
      vfree(iVar1);
      return;
    }
  }
  if (2 < DebugLevel) {
    printk("%s: copy_to_user() fail\n","RTMPIoctlQueryBaTable");
    uVar11 = extraout_r1;
  }
  vfree(iVar1,uVar11);
  return;
}

