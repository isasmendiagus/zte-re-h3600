// compatible: zte,ZX279127-spifc
// function: FUN_c023b770 @ 0xc023b770
// found via struct field ptr -> 0xc023b770
// total struct-refs for compat: 2
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_c023b770(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  
  if (_DAT_c069ea90 != 3) {
    FUN_c046ab98(s_spi_bootsel_______d_c05aefe4,_DAT_c069ea90,param_3,&DAT_c069ea90,param_4);
    return 0xfffffffa;
  }
  iVar5 = param_1 + 0x10;
  iVar1 = FUN_c02bcbd8(&DAT_c04ba5ac,iVar5);
  if (iVar1 == 0) {
    FUN_c046ab98(&DAT_c05aeffc);
    return 0xfffffff4;
  }
  *(undefined4 *)(param_1 + 0x170) = *(undefined4 *)(iVar1 + 0xc0);
  puVar2 = (undefined4 *)FUN_c01ef238(iVar5,0x638,0x80d0);
  if (puVar2 == (undefined4 *)0x0) {
    return 0xfffffff4;
  }
  *puVar2 = 3;
  puVar2[0x17d] = iVar5;
  iVar1 = FUN_c01edeec(param_1,0);
  puVar2[1] = iVar1;
  if (iVar1 < 0) {
    FUN_c01e9794(iVar5,s_no_irq_defined_c05af024);
    return puVar2[1];
  }
  uVar3 = FUN_c01ed7e8(param_1,0x200,s_spifc_reg_c05af034);
  FUN_c046ab98(&DAT_c05af040,uVar3);
  uVar3 = FUN_c01973f0(iVar5,uVar3);
  puVar2[0x174] = uVar3;
  FUN_c046ab98(&DAT_c05af054);
  if (0xfffff000 < (uint)puVar2[0x174]) {
    return puVar2[0x174];
  }
  uVar4 = FUN_c02c0fa8(iVar5,0);
  puVar2[0x18c] = uVar4;
  if (uVar4 < 0xfffff001) {
    iVar1 = FUN_c02c29fc();
    if ((iVar1 == 0) && (iVar1 = FUN_c02c2404(uVar4), iVar1 != 0)) {
      FUN_c02c30a8(uVar4);
    }
    uVar4 = FUN_c023d9fc(puVar2);
    FUN_c046ab98(s_ret__d_c05af080,uVar4);
    if (uVar4 == 0) {
      *(undefined4 **)(param_1 + 0x68) = puVar2;
      return 0;
    }
    uVar3 = puVar2[0x18c];
    FUN_c02c30d4(uVar3);
    FUN_c02c30a8(uVar3);
    FUN_c046ab98(s_ret__d_c05af080,uVar4);
    return uVar4;
  }
  FUN_c01e9794(iVar5,s_no_clk_available_c05af06c);
  return puVar2[0x18c];
}

