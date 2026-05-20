// module: mt7915.ko
// function: get_ch_array @ 0x201f9c
// size: 76 bytes
//

undefined1 * get_ch_array(int param_1,uint param_2)

{
  undefined1 *puVar1;
  
  if (param_2 < 2) {
    puVar1 = &_LANCHOR1;
    if (param_1 != 2) {
      puVar1 = &DAT_005dfe60;
    }
    return puVar1;
  }
  if (param_2 == 2) {
    puVar1 = &DAT_005dfe6c;
    if (param_1 != 2) {
      puVar1 = &DAT_005dfe9c;
    }
    return puVar1;
  }
  return (undefined1 *)0x0;
}

