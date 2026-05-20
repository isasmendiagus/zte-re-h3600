// FUN_c0017040 @ c0017040

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_c0017040(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 in_r3;
  uint uVar3;
  
  uVar2 = FUN_c0016b20();
  DAT_c069ea8c = (byte)uVar2;
  FUN_c046ab98(s_product_vid____d_c0585dc0,uVar2);
  uVar3 = (uint)DAT_c069ea8c;
  if (0x21 < uVar3) {
    FUN_c046ab98(s_<_s>__d__invalid_vid____use_defa_c0585dd4,DAT_c00170fc,0x8d0,uVar3,in_r3);
    uVar3 = 0;
    DAT_c069ea8c = 0;
  }
  _DAT_c069ea88 = &DAT_c0676bbc + uVar3 * 0x128;
  if ((uVar3 != (&DAT_c0676bdc)[uVar3 * 0x4a]) ||
     (iVar1 = uVar3 * 0x4a, uVar3 = 0, (&DAT_c0676be0)[iVar1] == 0)) {
    FUN_c046ab98(s_<_s>__d__invalid_current_board___c0585e10,DAT_c00170fc,0x8d8,uVar3,in_r3);
    _DAT_c069ea88 = &DAT_c0676bbc;
    DAT_c069ea8c = 0;
  }
  if (_DAT_c069ea88 != (undefined *)0x0) {
    _DAT_c07de868 = _DAT_c069ea88;
    return 0;
  }
  FUN_c046ab98(s_CspSeBoardInfo_input_param_error_c05d67ac);
  return 0xffffffff;
}

