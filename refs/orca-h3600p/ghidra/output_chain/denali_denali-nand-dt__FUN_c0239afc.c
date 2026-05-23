// compatible: denali,denali-nand-dt
// function: FUN_c0239afc @ 0xc0239afc
// found via struct field ptr -> 0xc0239afc
// total struct-refs for compat: 2
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_c0239afc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  
  if (_DAT_c06ae9b0 != 3) {
    FUN_c046918c(s_spi_bootsel_______d_c05ad780,_DAT_c06ae9b0,param_3,&DAT_c06ae9b0,param_4);
    return 0xfffffffa;
  }
  iVar5 = param_1 + 0x10;
  iVar1 = FUN_c02bd864(&DAT_c04b9914,iVar5);
  if (iVar1 == 0) {
    FUN_c046918c(&DAT_c05ad700);
    return 0xfffffff4;
  }
  *(undefined4 *)(param_1 + 0x170) = *(undefined4 *)(iVar1 + 0xc0);
  puVar2 = (undefined4 *)FUN_c01ed3bc(iVar5,0x638,0x80d0);
  if (puVar2 == (undefined4 *)0x0) {
    return 0xfffffff4;
  }
  *puVar2 = 3;
  puVar2[0x17d] = iVar5;
  iVar1 = FUN_c01ec070(param_1,0);
  puVar2[1] = iVar1;
  if (iVar1 < 0) {
    FUN_c01e7918(iVar5,s_no_irq_defined_c05ad728);
    return puVar2[1];
  }
  uVar3 = FUN_c01eb96c(param_1,0x200,s_spifc_reg_c05ad798);
  FUN_c046918c(&DAT_c05ad7a4,uVar3);
  uVar3 = FUN_c01979a4(iVar5,uVar3);
  puVar2[0x174] = uVar3;
  FUN_c046918c(&DAT_c05ad7b8);
  if (0xfffff000 < (uint)puVar2[0x174]) {
    return puVar2[0x174];
  }
  uVar4 = FUN_c02c1c34(iVar5,0);
  puVar2[0x18c] = uVar4;
  if (uVar4 < 0xfffff001) {
    iVar1 = FUN_c02c3688();
    if ((iVar1 == 0) && (iVar1 = FUN_c02c3090(uVar4), iVar1 != 0)) {
      FUN_c02c3d34(uVar4);
    }
    uVar4 = FUN_c023e650(puVar2);
    FUN_c046918c(s_ret__d_c05ad7d0,uVar4);
    if (uVar4 == 0) {
      *(undefined4 **)(param_1 + 0x68) = puVar2;
      return 0;
    }
    uVar3 = puVar2[0x18c];
    FUN_c02c3d60(uVar3);
    FUN_c02c3d34(uVar3);
    FUN_c046918c(s_ret__d_c05ad7d0,uVar4);
    return uVar4;
  }
  FUN_c01e7918(iVar5,s_no_clk_available_c05ad75c);
  return puVar2[0x18c];
}

