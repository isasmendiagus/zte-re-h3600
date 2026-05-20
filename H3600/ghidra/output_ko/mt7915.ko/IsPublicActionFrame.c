// module: mt7915.ko
// function: IsPublicActionFrame @ 0x112a24
// size: 48 bytes
//

byte IsPublicActionFrame(undefined4 param_1,byte *param_2)

{
  byte bVar1;
  byte bVar2;
  
  bVar1 = *param_2;
  bVar2 = bVar1 & 0xc;
  if ((bVar1 & 0xc) != 0) {
    return 0;
  }
  if ((bVar1 & 0xf0) == 0xd0) {
    bVar2 = param_2[0x18] == 4;
  }
  return bVar2;
}

