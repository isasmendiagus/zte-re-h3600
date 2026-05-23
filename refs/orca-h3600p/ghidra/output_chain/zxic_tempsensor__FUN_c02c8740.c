// compatible: zxic,tempsensor
// function: FUN_c02c8740 @ 0xc02c8740
// found via struct field ptr -> 0xc02c8740
// total struct-refs for compat: 4
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_c02c8740(int param_1)

{
  code *pcVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  
  uVar2 = FUN_c01eb908(param_1,0x200,0);
  DAT_c06a1654 = (uint *)FUN_c01979a4(param_1 + 0x10,uVar2);
  FUN_c046918c(s_zx_tempsensor__zx_bsp_tempsensor_c05c505c,DAT_c06a1654,DAT_c06a1654);
  _DAT_c06be5e0 = 0;
  FUN_c02c86a8();
  *DAT_c06a1654 = *DAT_c06a1654 & 0xfffcffff;
  DAT_c06a1630 = 0;
  DataSynchronizationBarrier(0xe);
  if (DAT_c066b2b8 != (code *)0x0) {
    (*DAT_c066b2b8)();
  }
  DAT_c06a1654[2] = 0x3fffffff;
  DAT_c06a1634 = 0;
  DAT_c06a1638 = 0;
  DAT_c06a163c = 0;
  if (_DAT_c06be5ec == 0) {
    FUN_c046918c(s_<_s>__d__creat_proc_files_for_te_c05c50b0,DAT_c02c88e8,0x270);
    iVar5 = FUN_c00f4490(s_tempsensor_c05c4f8c,0x1a4,0,DAT_c02c88f0,0);
    if (iVar5 == 0) {
                    /* WARNING: Does not return */
      pcVar1 = (code *)software_udf(0x12,0xc02c88a0);
      (*pcVar1)();
    }
    _DAT_c06be5ec = 1;
  }
  FUN_c046918c(s_<_s>__d__temper_sensor_is_runnin_c05c50e0,DAT_c02c88e8,0x275);
  piVar4 = DAT_c02c88ec;
  FUN_c046918c(s_zx_tempsensor__work_clock__d_c05c5108,DAT_c06a1650);
  iVar5 = 0;
  DAT_c06a164c = 0;
  do {
    iVar3 = FUN_c01ec070(param_1,iVar5);
    piVar4 = piVar4 + 1;
    *piVar4 = iVar3;
    if (iVar3 < 0) {
      return 0xffffffff;
    }
    FUN_c046918c(s_zx_tempsensor__selector_d_s_int_n_c05c5128,iVar5,iVar3);
    iVar5 = iVar5 + 1;
    FUN_c004e110(iVar3,&LAB_c02c7bbc,0,0,s_zx_tempersensor_c05c515c,param_1);
  } while (iVar5 != 3);
  return 0;
}

