// compatible: rohm,dh2228fv
// function: FUN_c0252b88 @ 0xc0252b88
// found via struct field ptr -> 0xc0252b88
// total struct-refs for compat: 2
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_c0252b88(uint param_1)

{
  undefined4 *puVar1;
  int iVar2;
  uint *puVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  
  if ((((*(int *)(param_1 + 0x114) != 0) &&
       (iVar2 = FUN_c02bd864(&DAT_c04be984,param_1), iVar2 == 0)) &&
      (FUN_c01e7918(param_1,s_buggy_DT__spidev_listed_directly_c05b3b68),
      *(int *)(param_1 + 0x114) != 0)) && (iVar2 = FUN_c02bd864(&DAT_c04be984,param_1), iVar2 == 0))
  {
    FUN_c001a140(s_drivers_spi_spidev_c_c05b3bb0,0x2db);
  }
  puVar3 = (uint *)FUN_c00a3238(_DAT_c06b705c,0x80d0);
  if (puVar3 == (uint *)0x0) {
    uVar5 = 0xfffffff4;
  }
  else {
    puVar3[1] = 0;
    puVar3[2] = param_1;
    puVar6 = puVar3 + 3;
    FUN_c00460f8(puVar3 + 5,s__spidev_>buf_lock_c05b3b90,&DAT_c06bd968);
    puVar3[3] = (uint)puVar6;
    puVar3[4] = (uint)puVar6;
    FUN_c046e90c(&DAT_c069e05c);
    uVar4 = FUN_c01808b4(0xc06bd964,0x20);
    if (uVar4 < 0x20) {
      *puVar3 = uVar4 | 0x9900000;
      uVar5 = FUN_c01e86a4(_DAT_c06bd960,param_1,uVar4 | 0x9900000,puVar3,s_spidev_d__d_c05b3ba4,
                           (int)*(short *)(*(int *)(param_1 + 0x158) + 0x160),
                           *(undefined1 *)(param_1 + 0x160));
      if ((uVar5 < 0xfffff001) || (uVar5 == 0)) {
        FUN_c0181c70(uVar4,DAT_c0252d40);
        uVar5 = (uint)DAT_c069e074;
        puVar1 = (undefined4 *)((int)DAT_c069e074 + 4);
        DAT_c069e074 = puVar6;
        *puVar1 = puVar6;
        puVar3[4] = (uint)&DAT_c069e074;
        puVar3[3] = uVar5;
        FUN_c046e750(&DAT_c069e05c);
        puVar3[0xe] = *(uint *)(param_1 + 0x15c);
        *(uint **)(param_1 + 0x58) = puVar3;
        return 0;
      }
    }
    else {
      uVar5 = 0xffffffed;
    }
    FUN_c046e750(&DAT_c069e05c);
    puVar3[0xe] = *(uint *)(param_1 + 0x15c);
    FUN_c00a3824(puVar3);
  }
  return uVar5;
}

