// compatible: snps,has-lpm-erratum
// function: FUN_c027c740 @ 0xc027c740
// found via struct field ptr -> 0xc027c740
// total struct-refs for compat: 1
//

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: ram */

undefined4 FUN_c027c740(undefined4 param_1,uint *param_2,undefined4 param_3)

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
  DAT_c069eff0 = 0x1a4;
  DAT_c069eff2 = 0x16d;
  DAT_c069eff4 = 0x124;
  _DAT_c06bdea8 = 0;
  _DAT_c06bdeac = 0;
  _DAT_c06bdeb0 = 0;
  _DAT_c06bdeb4 = 0;
  _DAT_c06bdeb8 = 0;
  _DAT_c06bdebc = 0;
  local_48 = param_3;
LAB_c027c7ac:
  do {
    pcVar3 = (char *)FUN_c0188578(&local_48,s_find_and_delete__vlan___d_PortNa_c05d87e4 + 0x30);
    if (pcVar3 == (char *)0x0) break;
    if (*pcVar3 != '\0') {
      uVar4 = FUN_c018cf84(pcVar3,&DAT_c04c05ec,auStack_40);
      switch(uVar4) {
      case 0:
        iVar9 = FUN_c018d2b8(auStack_40,&local_44);
        if (iVar9 == 0) {
          _DAT_c06bdea8 = local_44;
          goto LAB_c027c7ac;
        }
        break;
      case 1:
        iVar9 = FUN_c018d2b8(auStack_40,&local_44);
        if (iVar9 == 0) {
          _DAT_c06bdeac = local_44;
          goto LAB_c027c7ac;
        }
        break;
      case 2:
        iVar9 = FUN_c018d2c0(auStack_40,&local_44);
        if (iVar9 == 0) {
          DAT_c069eff0 = (ushort)((uint)(local_44 << 0x17) >> 0x17);
          goto LAB_c027c7ac;
        }
        break;
      case 3:
        iVar9 = FUN_c018d2b8(auStack_40,&local_44);
        if (iVar9 == 0) {
          _DAT_c06bdeb0 = local_44;
          goto LAB_c027c7ac;
        }
        break;
      case 4:
        iVar9 = FUN_c018d2b8(auStack_40,&local_44);
        if (iVar9 == 0) {
          _DAT_c06bdeb4 = local_44;
          goto LAB_c027c7ac;
        }
        break;
      case 5:
        iVar9 = FUN_c018d2c0(auStack_40,&local_44);
        if (iVar9 == 0) {
          DAT_c069eff2 = (ushort)((uint)(local_44 << 0x17) >> 0x17);
          goto LAB_c027c7ac;
        }
        break;
      case 6:
        iVar9 = FUN_c018d2b8(auStack_40,&local_44);
        if (iVar9 == 0) {
          _DAT_c06bdeb8 = local_44;
          goto LAB_c027c7ac;
        }
        break;
      case 7:
        iVar9 = FUN_c018d2b8(auStack_40,&local_44);
        if (iVar9 == 0) {
          _DAT_c06bdebc = local_44;
          goto LAB_c027c7ac;
        }
        break;
      case 8:
        iVar9 = FUN_c018d2c0(auStack_40,&local_44);
        if (iVar9 == 0) {
          DAT_c069eff4 = (ushort)((uint)(local_44 << 0x17) >> 0x17);
          goto LAB_c027c7ac;
        }
        break;
      default:
        FUN_c046918c(&DAT_c05b72a8,pcVar3);
      }
      FUN_c046918c(&DAT_c05b72e4);
      return 0xffffffea;
    }
  } while( true );
  if ((_DAT_c06bdec0 == 0) || (iVar9 = *(int *)(*(int *)(_DAT_c06bdec0 + 4) + 0x40), iVar9 == 0)) {
    return 0;
  }
  FUN_c046e90c(*(int *)(iVar9 + 0x28) + 0x60);
  piVar10 = *(int **)(iVar9 + 0x78);
  uVar5 = DAT_c069eff2;
  iVar1 = _DAT_c06bdeb4;
  iVar2 = _DAT_c06bdebc;
  do {
    while( true ) {
      DAT_c069eff2 = uVar5;
      _DAT_c06bdeb4 = iVar1;
      _DAT_c06bdebc = iVar2;
      if ((int *)(iVar9 + 0x78) == piVar10) {
        FUN_c046e750(*(int *)(iVar9 + 0x28) + 0x60);
        return 0;
      }
      iVar11 = (int)(piVar10 + -0x1c);
      puVar7 = *(ushort **)(iVar11 + 0x28);
      if (puVar7 != (ushort *)0x0) break;
LAB_c027c9e8:
      piVar10 = *(int **)(iVar11 + 0x70);
      uVar5 = DAT_c069eff2;
      iVar1 = _DAT_c06bdeb4;
      iVar2 = _DAT_c06bdebc;
    }
    if ((*puVar7 & 0xf000) != 0x4000) {
      if ((*puVar7 & 0xf000) == 0x8000) {
        uVar6 = (uint)DAT_c069eff4;
        *(int *)(puVar7 + 2) = _DAT_c06bdeb8;
        *(int *)(*(int *)(iVar11 + 0x28) + 8) = iVar2;
        **(ushort **)(iVar11 + 0x28) = ~((ushort)~(ushort)((uVar6 << 0x11) >> 0x10) >> 1);
      }
      else {
        FUN_c046918c(&DAT_c05b7308,*(undefined4 *)(iVar11 + 0x20));
      }
      goto LAB_c027c9e8;
    }
    *(int *)(puVar7 + 2) = _DAT_c06bdeb0;
    *(int *)(*(int *)(iVar11 + 0x28) + 8) = iVar1;
    **(ushort **)(iVar11 + 0x28) = uVar5 | 0x4000;
    FUN_c046e90c(*(int *)(iVar11 + 0x28) + 0x60);
    iVar2 = _DAT_c06bdeac;
    iVar1 = _DAT_c06bdea8;
    piVar10 = (int *)(iVar11 + 0x78);
    piVar8 = (int *)*piVar10;
    if (piVar10 != piVar8) {
      uVar5 = DAT_c069eff0 | 0x8000;
      do {
        if (piVar8[-0x12] != 0) {
          *(int *)(piVar8[-0x12] + 4) = iVar1;
          *(int *)(piVar8[-0x12] + 8) = iVar2;
          *(ushort *)piVar8[-0x12] = uVar5;
        }
        piVar8 = (int *)*piVar8;
      } while (piVar10 != piVar8);
    }
    FUN_c046e750(*(int *)(iVar11 + 0x28) + 0x60);
    piVar10 = *(int **)(iVar11 + 0x70);
    uVar5 = DAT_c069eff2;
    iVar1 = _DAT_c06bdeb4;
    iVar2 = _DAT_c06bdebc;
  } while( true );
}

