// compatible: rohm,dh2228fv
// function: FUN_c0251df8 @ 0xc0251df8
// found via struct field ptr -> 0xc0251df8
// total struct-refs for compat: 2
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_c0251df8(int param_1)

{
  undefined4 uVar1;
  uint uVar2;
  uint *puVar3;
  uint *puVar4;
  
  puVar4 = *(uint **)(param_1 + 0x58);
  FUN_c04712a8(puVar4 + 1);
  puVar4[2] = 0;
  FUN_c0471328(puVar4 + 1);
  FUN_c046fc7c(&DAT_c068de50);
  uVar1 = _DAT_c06ad218;
  puVar3 = (uint *)puVar4[4];
  uVar2 = puVar4[3];
  *(uint **)(uVar2 + 4) = puVar3;
  *puVar3 = uVar2;
  puVar4[3] = 0x100;
  puVar4[4] = 0x200;
  FUN_c01e9378(uVar1,*puVar4);
  FUN_c017f208(*puVar4 & 0xfffff,0xc06ad21c);
  if (puVar4[0xb] == 0) {
    FUN_c00a35dc(puVar4);
  }
  FUN_c046fac0(&DAT_c068de50);
  return 0;
}

