// compatible: zte,zx279128-smp
// function: FUN_c0014b3c @ 0xc0014b3c
// found via struct field ptr -> 0xc0014b3c
// total struct-refs for compat: 2
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_c0014b3c(int param_1,int param_2,int param_3)

{
  uint uVar1;
  undefined4 *puVar2;
  uint *puVar3;
  
  if ((*(uint *)(param_1 + 0x100) & 1) != 0) {
    return;
  }
  _DAT_c06ae8c0 = param_2;
  if (DAT_c066b2c4 == (code *)0x0) {
    if (*(code **)(_DAT_c06ae8ec + 0x1c) != (code *)0x0) {
      (**(code **)(_DAT_c06ae8ec + 0x1c))();
    }
    if (*(int *)(param_1 + 0x104) != _DAT_c06ae8c0) {
      if (DAT_c066b2c0 == (code *)0x0) {
        *(int *)(param_1 + 0x104) = _DAT_c06ae8c0;
      }
      else {
        (*DAT_c066b2c0)(_DAT_c06ae8c0,0x104);
      }
    }
  }
  else {
    (*DAT_c066b2c4)(&DAT_c06ae8bc);
  }
  if (param_3 != 0) {
    puVar2 = (undefined4 *)(param_1 + 0x900);
    do {
      *puVar2 = 0;
      puVar2[1] = 0;
      puVar2 = puVar2 + 2;
    } while (puVar2 != (undefined4 *)(param_1 + (param_3 + 0x120) * 8));
  }
  disableIRQinterrupts();
  FUN_c0014af0(param_1 + 0x77c);
  puVar3 = (uint *)(param_1 + DAT_c0674ad0);
  *puVar3 = 0;
  uVar1 = *puVar3;
  while ((uVar1 & 1) != 0) {
    uVar1 = *puVar3;
  }
  if (*(int *)(param_1 + 0x100) == 1) {
    return;
  }
  if (DAT_c066b2c0 == (code *)0x0) {
    *(undefined4 *)(param_1 + 0x100) = 1;
    return;
  }
                    /* WARNING: Could not recover jumptable at 0xc0014c14. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*DAT_c066b2c0)(1,0x100);
  return;
}

