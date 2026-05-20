// module: mt7915.ko
// function: get_ecc_group_info @ 0x2170b0
// size: 64 bytes
//

undefined4 * get_ecc_group_info(int param_1)

{
  undefined4 *puVar1;
  
  puVar1 = &_LANCHOR0;
  if (_LANCHOR0 != param_1) {
    puVar1 = (undefined4 *)0x0;
  }
  if (DAT_005dff40 == param_1) {
    puVar1 = &DAT_005dff40;
  }
  if (DAT_005dff80 == param_1) {
    puVar1 = &DAT_005dff80;
  }
  return puVar1;
}

