// module: mt7915.ko
// function: GetChannel_2GHZ @ 0x140fd0
// size: 84 bytes
//

uint GetChannel_2GHZ(byte *param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = (uint)*param_1;
  if (uVar1 == 0) {
    return 0;
  }
  uVar2 = (uint)param_1[1];
  if (uVar2 <= param_2) {
    do {
      uVar1 = (uint)param_1[3];
      param_2 = param_2 - uVar2 & 0xff;
      if (uVar1 == 0) {
        return 0;
      }
      uVar2 = (uint)param_1[4];
      param_1 = param_1 + 3;
    } while (uVar2 <= param_2);
  }
  return uVar1 + param_2 & 0xff;
}

