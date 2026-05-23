// compatible: zxic,tempsensor
// function: FUN_c02c7ab4 @ 0xc02c7ab4
// found via struct field ptr -> 0xc02c7ab4
// total struct-refs for compat: 4
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_c02c7ab4(int param_1)

{
  code *pcVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  
  uVar2 = FUN_c01ed784(param_1,0x200,0);
  DAT_c0691434 = (uint *)FUN_c01973f0(param_1 + 0x10,uVar2);
  FUN_c046ab98(s_zx_tempsensor__zx_bsp_tempsensor_c05c6388,DAT_c0691434,DAT_c0691434);
  _DAT_c06ade98 = 0;
  FUN_c02c7a1c();
  *DAT_c0691434 = *DAT_c0691434 & 0xfffcffff;
  DAT_c0691410 = 0;
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  DAT_c0691434[2] = 0x3fffffff;
  DAT_c0691414 = 0;
  DAT_c0691418 = 0;
  DAT_c069141c = 0;
  if (_DAT_c06adea4 == 0) {
    FUN_c046ab98(s_<_s>__d__creat_proc_files_for_te_c05c63dc,DAT_c02c7c5c,0x270);
    iVar5 = FUN_c00f420c(s_tempsensor_c05c62b8,0x1a4,0,DAT_c02c7c64,0);
    if (iVar5 == 0) {
                    /* WARNING: Does not return */
      pcVar1 = (code *)software_udf(0x12,0xc02c7c14);
      (*pcVar1)();
    }
    _DAT_c06adea4 = 1;
  }
  FUN_c046ab98(s_<_s>__d__temper_sensor_is_runnin_c05c640c,DAT_c02c7c5c,0x275);
  piVar4 = DAT_c02c7c60;
  FUN_c046ab98(s_zx_tempsensor__work_clock__d_c05c6434,DAT_c0691430);
  iVar5 = 0;
  DAT_c069142c = 0;
  do {
    iVar3 = FUN_c01edeec(param_1,iVar5);
    piVar4 = piVar4 + 1;
    *piVar4 = iVar3;
    if (iVar3 < 0) {
      return 0xffffffff;
    }
    FUN_c046ab98(s_zx_tempsensor__selector_d_s_int_n_c05c6454,iVar5,iVar3);
    iVar5 = iVar5 + 1;
    FUN_c004dec8(iVar3,&LAB_c02c6f30,0,0,s_zx_tempersensor_c05c6488,param_1);
  } while (iVar5 != 3);
  return 0;
}

