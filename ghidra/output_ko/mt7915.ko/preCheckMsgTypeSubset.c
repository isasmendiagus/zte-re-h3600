// module: mt7915.ko
// function: preCheckMsgTypeSubset @ 0x699a0
// size: 80 bytes
//

byte preCheckMsgTypeSubset(undefined4 param_1,byte *param_2,undefined4 *param_3,undefined4 *param_4)

{
  byte bVar1;
  byte bVar2;
  
  bVar1 = *param_2;
  bVar2 = bVar1 & 0xc;
  if ((bVar1 & 0xc) != 0) {
    return 0;
  }
  if (bVar1 >> 4 == 5) {
    *param_3 = 4;
    *param_4 = 5;
    return 1;
  }
  if (bVar1 >> 4 == 8) {
    *param_3 = 4;
    bVar2 = 1;
    *param_4 = 6;
  }
  return bVar2;
}

