// module: mt7915.ko
// function: GetChannelFlag @ 0x141024
// size: 76 bytes
//

char GetChannelFlag(char *param_1,uint param_2)

{
  uint uVar1;
  char *pcVar2;
  
  if (*param_1 == '\0') {
    return '\0';
  }
  uVar1 = (uint)(byte)param_1[1];
  pcVar2 = param_1;
  if (uVar1 <= param_2) {
    do {
      param_1 = pcVar2 + 3;
      param_2 = param_2 - uVar1 & 0xff;
      if (*param_1 == '\0') {
        return '\0';
      }
      uVar1 = (uint)(byte)pcVar2[4];
      pcVar2 = param_1;
    } while (uVar1 <= param_2);
  }
  return param_1[2];
}

