// module: tm.ko
// function: cla_set_external_hash_table @ 0x164e0
// size: 152 bytes
//

undefined4 cla_set_external_hash_table(uint param_1,int param_2,int param_3)

{
  int iVar1;
  undefined1 *puVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  iVar4 = param_2 * 2 + 0x13;
  if (iVar4 < 0) {
    iVar4 = param_2 * 2 + 0x1a;
  }
  iVar4 = iVar4 >> 3;
  iVar6 = iVar4 + 1;
  *(byte *)(param_3 + 0x10) = *(byte *)(param_3 + 0x10) & 0xbf;
  if (0 < iVar6) {
    iVar4 = iVar4 << 3;
  }
  iVar1 = ((param_1 & 0xffff) + 0x3c40800) * 0x40;
  if (0 < iVar6) {
    iVar6 = -1;
    do {
      iVar7 = iVar6 + 8;
      puVar2 = (undefined1 *)(iVar1 + 1 + iVar6);
      iVar5 = iVar7;
      do {
        if (iVar5 < 0x3c) {
          *puVar2 = *(undefined1 *)(param_3 + iVar5);
        }
        iVar5 = iVar5 + -1;
        puVar2 = puVar2 + 1;
      } while (iVar5 != iVar6);
      iVar6 = iVar7;
    } while (iVar7 != iVar4 + 7);
  }
  bVar3 = *(byte *)(param_3 + 0x10) | 0x40;
  *(byte *)(param_3 + 0x10) = bVar3;
  *(byte *)(iVar1 + 0x17) = bVar3;
  return 0;
}

