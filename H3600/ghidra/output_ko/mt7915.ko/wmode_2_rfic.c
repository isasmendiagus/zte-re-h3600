// module: mt7915.ko
// function: wmode_2_rfic @ 0xb8320
// size: 40 bytes
//

byte wmode_2_rfic(uint param_1)

{
  byte bVar1;
  
  bVar1 = (param_1 & 0x4e) != 0;
  if ((param_1 & 0xb1) != 0) {
    bVar1 = bVar1 | 2;
  }
  if ((param_1 & 0x100) != 0) {
    bVar1 = bVar1 | 4;
  }
  return bVar1;
}

