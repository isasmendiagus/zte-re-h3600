// compatible: snps,has-lpm-erratum
// function: FUN_c027bae4 @ 0xc027bae4
// found via struct field ptr -> 0xc027bae4
// total struct-refs for compat: 1
//

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: ram */

undefined4 FUN_c027bae4(undefined4 param_1,uint *param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  undefined4 uVar4;
  ushort uVar5;
  uint uVar6;
  ushort *puVar7;
  int *piVar8;
  int iVar9;
  int *piVar10;
  int iVar11;
  undefined4 local_48;
  int local_44;
  undefined1 auStack_40 [28];
  
  if ((*param_2 & 0x400000) != 0) {
    return 0;
  }
  DAT_c068ede4 = 0x1a4;
  DAT_c068ede6 = 0x16d;
  DAT_c068ede8 = 0x124;
  _DAT_c06ad760 = 0;
  _DAT_c06ad764 = 0;
  _DAT_c06ad768 = 0;
  _DAT_c06ad76c = 0;
  _DAT_c06ad770 = 0;
  _DAT_c06ad774 = 0;
  local_48 = param_3;
LAB_c027bb50:
  do {
    pcVar3 = (char *)FUN_c01882b8(&local_48,s_find_and_delete__vlan___d_PortNa_c05da024 + 0x30);
    if (pcVar3 == (char *)0x0) break;
    if (*pcVar3 != '\0') {
      uVar4 = FUN_c018ccc4(pcVar3,&DAT_c04c0d10,auStack_40);
      switch(uVar4) {
      case 0:
        iVar9 = FUN_c018cff8(auStack_40,&local_44);
        if (iVar9 == 0) {
          _DAT_c06ad760 = local_44;
          goto LAB_c027bb50;
        }
        break;
      case 1:
        iVar9 = FUN_c018cff8(auStack_40,&local_44);
        if (iVar9 == 0) {
          _DAT_c06ad764 = local_44;
          goto LAB_c027bb50;
        }
        break;
      case 2:
        iVar9 = FUN_c018d000(auStack_40,&local_44);
        if (iVar9 == 0) {
          DAT_c068ede4 = (ushort)((uint)(local_44 << 0x17) >> 0x17);
          goto LAB_c027bb50;
        }
        break;
      case 3:
        iVar9 = FUN_c018cff8(auStack_40,&local_44);
        if (iVar9 == 0) {
          _DAT_c06ad768 = local_44;
          goto LAB_c027bb50;
        }
        break;
      case 4:
        iVar9 = FUN_c018cff8(auStack_40,&local_44);
        if (iVar9 == 0) {
          _DAT_c06ad76c = local_44;
          goto LAB_c027bb50;
        }
        break;
      case 5:
        iVar9 = FUN_c018d000(auStack_40,&local_44);
        if (iVar9 == 0) {
          DAT_c068ede6 = (ushort)((uint)(local_44 << 0x17) >> 0x17);
          goto LAB_c027bb50;
        }
        break;
      case 6:
        iVar9 = FUN_c018cff8(auStack_40,&local_44);
        if (iVar9 == 0) {
          _DAT_c06ad770 = local_44;
          goto LAB_c027bb50;
        }
        break;
      case 7:
        iVar9 = FUN_c018cff8(auStack_40,&local_44);
        if (iVar9 == 0) {
          _DAT_c06ad774 = local_44;
          goto LAB_c027bb50;
        }
        break;
      case 8:
        iVar9 = FUN_c018d000(auStack_40,&local_44);
        if (iVar9 == 0) {
          DAT_c068ede8 = (ushort)((uint)(local_44 << 0x17) >> 0x17);
          goto LAB_c027bb50;
        }
        break;
      default:
        FUN_c046ab98(&DAT_c05b85d4,pcVar3);
      }
      FUN_c046ab98(&DAT_c05b8610);
      return 0xffffffea;
    }
  } while( true );
  if ((_DAT_c06ad778 == 0) || (iVar9 = *(int *)(*(int *)(_DAT_c06ad778 + 4) + 0x40), iVar9 == 0)) {
    return 0;
  }
  FUN_c046fc7c(*(int *)(iVar9 + 0x28) + 0x60);
  piVar10 = *(int **)(iVar9 + 0x78);
  uVar5 = DAT_c068ede6;
  iVar1 = _DAT_c06ad76c;
  iVar2 = _DAT_c06ad774;
  do {
    while( true ) {
      DAT_c068ede6 = uVar5;
      _DAT_c06ad76c = iVar1;
      _DAT_c06ad774 = iVar2;
      if ((int *)(iVar9 + 0x78) == piVar10) {
        FUN_c046fac0(*(int *)(iVar9 + 0x28) + 0x60);
        return 0;
      }
      iVar11 = (int)(piVar10 + -0x1c);
      puVar7 = *(ushort **)(iVar11 + 0x28);
      if (puVar7 != (ushort *)0x0) break;
LAB_c027bd8c:
      piVar10 = *(int **)(iVar11 + 0x70);
      uVar5 = DAT_c068ede6;
      iVar1 = _DAT_c06ad76c;
      iVar2 = _DAT_c06ad774;
    }
    if ((*puVar7 & 0xf000) != 0x4000) {
      if ((*puVar7 & 0xf000) == 0x8000) {
        uVar6 = (uint)DAT_c068ede8;
        *(int *)(puVar7 + 2) = _DAT_c06ad770;
        *(int *)(*(int *)(iVar11 + 0x28) + 8) = iVar2;
        **(ushort **)(iVar11 + 0x28) = ~((ushort)~(ushort)((uVar6 << 0x11) >> 0x10) >> 1);
      }
      else {
        FUN_c046ab98(&DAT_c05b8634,*(undefined4 *)(iVar11 + 0x20));
      }
      goto LAB_c027bd8c;
    }
    *(int *)(puVar7 + 2) = _DAT_c06ad768;
    *(int *)(*(int *)(iVar11 + 0x28) + 8) = iVar1;
    **(ushort **)(iVar11 + 0x28) = uVar5 | 0x4000;
    FUN_c046fc7c(*(int *)(iVar11 + 0x28) + 0x60);
    iVar2 = _DAT_c06ad764;
    iVar1 = _DAT_c06ad760;
    piVar10 = (int *)(iVar11 + 0x78);
    piVar8 = (int *)*piVar10;
    if (piVar10 != piVar8) {
      uVar5 = DAT_c068ede4 | 0x8000;
      do {
        if (piVar8[-0x12] != 0) {
          *(int *)(piVar8[-0x12] + 4) = iVar1;
          *(int *)(piVar8[-0x12] + 8) = iVar2;
          *(ushort *)piVar8[-0x12] = uVar5;
        }
        piVar8 = (int *)*piVar8;
      } while (piVar10 != piVar8);
    }
    FUN_c046fac0(*(int *)(iVar11 + 0x28) + 0x60);
    piVar10 = *(int **)(iVar11 + 0x70);
    uVar5 = DAT_c068ede6;
    iVar1 = _DAT_c06ad76c;
    iVar2 = _DAT_c06ad774;
  } while( true );
}

