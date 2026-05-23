// module: mt7915.ko
// function: RTMPTkipGetUInt32 @ 0x1173b0
// size: 36 bytes
//

uint RTMPTkipGetUInt32(byte *param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = 0;
  uVar1 = 0;
  do {
    uVar1 = uVar1 | (uint)*param_1 << (uVar2 & 0xff);
    uVar2 = uVar2 + 8;
    param_1 = param_1 + 1;
  } while (uVar2 != 0x20);
  return uVar1;
}

