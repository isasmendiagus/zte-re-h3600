// module: mt7915.ko
// function: he_mcs_map @ 0x204cc0
// size: 168 bytes
//

uint he_mcs_map(uint param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  
  if (param_1 < 2) {
    return param_2 & 0xffff | 0xfffc;
  }
  uVar1 = ~(~((param_2 & 0xfff3) << 0x1c) >> 0x1c) | param_2 << 2;
  uVar2 = uVar1 & 0xffff;
  if ((param_1 != 2) && (uVar2 = uVar1 & 0xffcf | param_2 << 4, param_1 != 3)) {
    uVar1 = uVar2 & 0xffffff3f | param_2 << 6;
    uVar2 = uVar1 & 0xffff;
    if ((param_1 != 4) &&
       (((uVar2 = uVar1 & 0xfcff | (param_2 & 0xff) << 8, param_1 != 5 &&
         (uVar2 = uVar2 & 0xfffff3ff | (param_2 & 0x3f) << 10, param_1 != 6)) &&
        (uVar2 = uVar2 & 0xffffcfff | (param_2 & 0xf) << 0xc, param_1 != 7)))) {
      uVar2 = uVar2 & 0x3fff | (param_2 & 3) << 0xe;
    }
  }
  return uVar2;
}

