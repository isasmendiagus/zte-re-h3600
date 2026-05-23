// compatible: rohm,dh2228fv
// function: FUN_c0252a50 @ 0xc0252a50
// found via struct field ptr -> 0xc0252a50
// total struct-refs for compat: 2
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_c0252a50(int param_1)

{
  undefined4 uVar1;
  uint uVar2;
  uint *puVar3;
  uint *puVar4;
  
  puVar4 = *(uint **)(param_1 + 0x58);
  FUN_c046ff38(puVar4 + 1);
  puVar4[2] = 0;
  FUN_c046ffb8(puVar4 + 1);
  FUN_c046e90c(&DAT_c069e05c);
  uVar1 = _DAT_c06bd960;
  puVar3 = (uint *)puVar4[4];
  uVar2 = puVar4[3];
  *(uint **)(uVar2 + 4) = puVar3;
  *puVar3 = uVar2;
  puVar4[3] = 0x100;
  puVar4[4] = 0x200;
  FUN_c01e74fc(uVar1,*puVar4);
  FUN_c017f4b0(*puVar4 & 0xfffff,0xc06bd964);
  if (puVar4[0xb] == 0) {
    FUN_c00a3824(puVar4);
  }
  FUN_c046e750(&DAT_c069e05c);
  return 0;
}

