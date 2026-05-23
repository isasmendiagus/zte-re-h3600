// compatible: zte,zx279128-dwc3
// function: FUN_c027eedc @ 0xc027eedc
// found via struct field ptr -> 0xc027eedc
// total struct-refs for compat: 2
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_c027eedc(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  undefined4 uVar5;
  
  uVar5 = *(undefined4 *)(param_1 + 0x124);
  iVar1 = FUN_c00126c4(0x9100000,0x100000);
  iVar4 = param_1 + 0x10;
  iVar2 = FUN_c00126c4(0x9300000,0x100000,0);
  uRamf040004c = uRamf040004c | 0x800;
  (*DAT_c06955fc)(0x346dc);
  uRamf040004c = uRamf040004c | 0x4000;
  (*DAT_c06955fc)(0x346dc);
  uRamf040004c = uRamf040004c | 0x200;
  (*DAT_c06955fc)(0x10624c);
  uRamf040004c = uRamf040004c | 0x400;
  (*DAT_c06955fc)(0x346dc);
  FUN_c046918c(s_ZX_VA_TOP_CRM_0x4C_0x_02x_c05b8b54,uRamf040004c);
  *(uint *)(iVar1 + 0xc110) = *(uint *)(iVar1 + 0xc110) & 0x7ffff | 0x100400;
  *(uint *)(iVar1 + 0xc12c) = *(uint *)(iVar1 + 0xc12c) & 0x3fffff | 0xc800000;
  (*DAT_c06955fc)(0x51eb7c);
  *(uint *)(iVar2 + 0x20) = *(uint *)(iVar2 + 0x20) | 0x100000;
  iVar1 = 10;
  (*DAT_c06955fc)(0x51eb7c);
  do {
    (*DAT_c06955fc)(0x66665b0);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  piVar3 = (int *)FUN_c01ed3bc(iVar4,0x14,0x80d0);
  if (piVar3 == (int *)0x0) {
    FUN_c01e7918(iVar4,s_failed_to_alloc_mem_dwc3_core_c05b8b70);
    return -0xc;
  }
  *(int **)(param_1 + 0x68) = piVar3;
  *piVar3 = iVar4;
  _DAT_c06bded8 = FUN_c02c04a4(uVar5,0);
  piVar3[4] = _DAT_c06bded8;
  if ((iVar4 != 0) && (piVar3 = *(int **)(param_1 + 0xf8), piVar3 != (int *)0x0)) {
    _DAT_c06bdee0 = *piVar3;
    _DAT_c06bdee4 = piVar3[1];
    if (_DAT_c06bdee0 != 0 || _DAT_c06bdee4 != 0) goto LAB_c027f07c;
  }
  _DAT_c06bdee0 = -1;
  _DAT_c06bdee4 = 0;
LAB_c027f07c:
  *(undefined4 *)(param_1 + 0xf8) = DAT_c027f0e8;
  iVar1 = FUN_c02be720(uVar5,0,0,iVar4);
  if (iVar1 == 0) {
    return 0;
  }
  FUN_c01e7918(iVar4,s_failed_to_create_dwc3_core_c05b8b90);
  return iVar1;
}

