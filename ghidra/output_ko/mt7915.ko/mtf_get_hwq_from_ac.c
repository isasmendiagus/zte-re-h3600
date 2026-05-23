// module: mt7915.ko
// function: mtf_get_hwq_from_ac @ 0x19d968
// size: 36 bytes
//

undefined1 mtf_get_hwq_from_ac(uint param_1,uint param_2)

{
  uint uVar1;
  undefined1 uVar2;
  
  uVar1 = param_2;
  if (param_2 < 4) {
    uVar1 = param_1;
  }
  if (uVar1 < 4) {
    uVar2 = (&DAT_0029da20)[param_1 * 4 + param_2];
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

