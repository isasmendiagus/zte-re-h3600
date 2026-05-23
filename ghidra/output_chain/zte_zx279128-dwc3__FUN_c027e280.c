// compatible: zte,zx279128-dwc3
// function: FUN_c027e280 @ 0xc027e280
// found via struct field ptr -> 0xc027e280
// total struct-refs for compat: 2
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_c027e280(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  undefined4 uVar5;
  
  uVar5 = *(undefined4 *)(param_1 + 0x124);
  iVar1 = FUN_c00126a4(0x9100000,0x100000);
  iVar4 = param_1 + 0x10;
  iVar2 = FUN_c00126a4(0x9300000,0x100000,0);
  uRamf040004c = uRamf040004c | 0x800;
  (*DAT_c068531c)(0x346dc);
  uRamf040004c = uRamf040004c | 0x4000;
  (*DAT_c068531c)(0x346dc);
  uRamf040004c = uRamf040004c | 0x200;
  (*DAT_c068531c)(0x10624c);
  uRamf040004c = uRamf040004c | 0x400;
  (*DAT_c068531c)(0x346dc);
  FUN_c046ab98(s_ZX_VA_TOP_CRM_0x4C_0x_02x_c05b9e80,uRamf040004c);
  *(uint *)(iVar1 + 0xc110) = *(uint *)(iVar1 + 0xc110) & 0x7ffff | 0x100400;
  *(uint *)(iVar1 + 0xc12c) = *(uint *)(iVar1 + 0xc12c) & 0x3fffff | 0xc800000;
  (*DAT_c068531c)(0x51eb7c);
  *(uint *)(iVar2 + 0x20) = *(uint *)(iVar2 + 0x20) | 0x100000;
  iVar1 = 10;
  (*DAT_c068531c)(0x51eb7c);
  do {
    (*DAT_c068531c)(0x66665b0);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  piVar3 = (int *)FUN_c01ef238(iVar4,0x14,0x80d0);
  if (piVar3 == (int *)0x0) {
    FUN_c01e9794(iVar4,s_failed_to_alloc_mem_dwc3_core_c05b9e9c);
    return -0xc;
  }
  *(int **)(param_1 + 0x68) = piVar3;
  *piVar3 = iVar4;
  _DAT_c06ad790 = FUN_c02bf818(uVar5,0);
  piVar3[4] = _DAT_c06ad790;
  if ((iVar4 != 0) && (piVar3 = *(int **)(param_1 + 0xf8), piVar3 != (int *)0x0)) {
    _DAT_c06ad798 = *piVar3;
    _DAT_c06ad79c = piVar3[1];
    if (_DAT_c06ad798 != 0 || _DAT_c06ad79c != 0) goto LAB_c027e420;
  }
  _DAT_c06ad798 = -1;
  _DAT_c06ad79c = 0;
LAB_c027e420:
  *(undefined4 *)(param_1 + 0xf8) = DAT_c027e48c;
  iVar1 = FUN_c02bda94(uVar5,0,0,iVar4);
  if (iVar1 == 0) {
    return 0;
  }
  FUN_c01e9794(iVar4,s_failed_to_create_dwc3_core_c05b9ebc);
  return iVar1;
}

