// module: plat-zxylzb_9128S.ko
// function: isint @ 0x10630
// size: 196 bytes
//

undefined4 isint(byte *param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  
  if (param_1 == (byte *)0x0) {
    return 0;
  }
  uVar1 = (uint)*param_1;
  if (uVar1 == 0x2d) {
    uVar1 = (uint)param_1[1];
    param_1 = param_1 + 1;
  }
  if (uVar1 == 0x30) {
    if ((param_1[1] & 0xdf) == 0x42) {
      uVar1 = (uint)param_1[2];
      param_2 = 2;
      param_1 = param_1 + 2;
    }
    else if ((param_1[1] & 0xdf) == 0x58) {
      uVar1 = (uint)param_1[2];
      param_2 = 0x10;
      param_1 = param_1 + 2;
    }
    else {
      param_2 = 8;
    }
  }
  while( true ) {
    uVar2 = uVar1 - 0x30;
    if (((&_ctype)[uVar1] & 0x44) == 0) {
      return 0;
    }
    if (9 < uVar2) {
      uVar2 = uVar1 - 0x57;
      if ((5 < uVar1 - 0x61) && (uVar2 = 0, uVar1 - 0x41 < 6)) {
        uVar2 = uVar1 - 0x37;
      }
    }
    if (param_2 <= (int)uVar2) break;
    param_1 = param_1 + 1;
    uVar1 = (uint)*param_1;
    if (uVar1 == 0) {
      return 1;
    }
  }
  return 0;
}

