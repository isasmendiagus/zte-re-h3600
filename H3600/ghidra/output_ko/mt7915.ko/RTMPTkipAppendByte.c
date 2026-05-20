// module: mt7915.ko
// function: RTMPTkipAppendByte @ 0x117450
// size: 128 bytes
//

void RTMPTkipAppendByte(uint *param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = *param_1;
  uVar2 = uVar1 + 1;
  *param_1 = uVar2;
  uVar1 = param_1[7] | param_2 << ((uVar1 & 0x1f) << 3);
  param_1[7] = uVar1;
  if (uVar2 < 4) {
    return;
  }
  uVar1 = uVar1 ^ param_1[5];
  param_1[7] = 0;
  *param_1 = 0;
  uVar2 = param_1[6] ^ (uVar1 >> 0xf | uVar1 << 0x11);
  uVar1 = uVar2 + uVar1;
  uVar2 = ((uVar1 & 0xff00ffff) >> 8 | (uVar1 & 0xff00ff) << 8) ^ uVar2;
  uVar1 = uVar2 + uVar1;
  uVar2 = uVar2 ^ (uVar1 >> 0x1d | uVar1 * 8);
  uVar1 = uVar2 + uVar1;
  uVar2 = uVar2 ^ (uVar1 >> 2 | uVar1 * 0x40000000);
  param_1[6] = uVar2;
  param_1[5] = uVar2 + uVar1;
  return;
}

