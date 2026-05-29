// FUN_40e50510 @ 40e50510

undefined4 FUN_40e50510(void)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint *puVar9;
  uint *puVar10;
  int iStack_2c;
  
  piVar2 = piRam40e5070c;
  uVar8 = 7;
  puVar9 = puRam40e50708;
  do {
    uVar4 = *puVar9 & 0xffff;
    if (uVar4 != 0) {
      if (0 < piVar2[1]) {
        FUN_40e2a1b4(uRam40e50710,uVar8,uVar4);
      }
      iVar3 = iRam40e50714;
      puVar10 = (uint *)(iRam40e50714 + (int)puVar9 * 2 + iRam40e50718);
      iStack_2c = 0;
      do {
        iVar6 = *(int *)(uVar8 * 8 + iVar3) + *puVar10 * 0x10;
        uVar5 = *puVar10 + 1;
        *puVar10 = uVar5;
        if (0x3ff < uVar5) {
          *puVar10 = 0;
        }
        FUN_40e215f0(iVar6,iVar6 + 0x10);
        uVar5 = (uint)(*(byte *)(iVar6 + 7) >> 1) | (uint)*(byte *)(iVar6 + 8) << 7;
        if (uVar5 < 0x800) {
          uVar1 = (uint)(*(ushort *)(iVar6 + 0xc) >> 2);
          iVar7 = uVar5 * 0x800 + 0x41000010;
          FUN_40e215f0(iVar7,iVar7 + uVar1);
          if (0 < piVar2[1]) {
            FUN_40e504a0(iVar6);
            FUN_40e2a1b4(uRam40e50720,uVar1,uVar5,*(undefined2 *)(iVar6 + 4),iVar7);
            FUN_40e503e4(iVar7,uVar1);
            piVar2[1] = piVar2[1] + -1;
          }
          *piRam40e5070c = *piRam40e5070c + 1;
          FUN_40e4c3f4(iVar7,uVar1);
          iVar6 = func_0x40e50170(((uint)*(byte *)(iVar6 + 3) << 0x1b) >> 0x1d,0,1,0);
          if (iVar6 < 0) {
            FUN_40e2a1b4(uRam40e50724);
          }
          iVar6 = func_0x40e4fff8(uVar5);
          if (iVar6 < 0) {
            FUN_40e2a1b4(uRam40e50728);
          }
        }
        else {
          FUN_40e2a1b4(uRam40e5071c,uVar5);
          FUN_40e504a0(iVar6);
          func_0x40e50170(uVar8 & 0xff,0,1,0);
        }
        iStack_2c = iStack_2c + 1;
      } while (iStack_2c < (int)uVar4);
      if ((*puVar9 & 0xffff) != 0) {
        FUN_40e45a90(1);
      }
    }
    uVar8 = uVar8 - 1;
    puVar9 = puVar9 + -1;
  } while (uVar8 != 0xffffffff);
  return 0;
}
