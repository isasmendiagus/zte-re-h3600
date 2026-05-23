// module: mt7915.ko
// function: get_reg_table_by_country @ 0x141aac
// size: 136 bytes
//

undefined1 * get_reg_table_by_country(undefined4 param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = GetCountryRegionFromCountryCode();
  if ((param_2 & 0x1c0) != 0) {
    if (5 < uVar1) {
      return reg_class_he_fcc;
    }
    return (&_LANCHOR2)[uVar1];
  }
  if ((param_2 & 0x20) == 0) {
    if (uVar1 < 6) {
      return (&PTR_reg_class_ce_00299dcc)[uVar1];
    }
    return reg_class_fcc;
  }
  if (5 < uVar1) {
    return reg_class_vht_fcc;
  }
  return (&PTR_reg_class_vht_ce_00299db4)[uVar1];
}

