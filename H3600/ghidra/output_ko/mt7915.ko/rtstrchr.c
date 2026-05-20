// module: mt7915.ko
// function: rtstrchr @ 0x1428c0
// size: 60 bytes
//

char * rtstrchr(char *param_1,char param_2)

{
  char cVar1;
  
  cVar1 = *param_1;
  if (cVar1 == param_2) {
    return param_1;
  }
  do {
    if (cVar1 == '\0') {
      return (char *)0x0;
    }
    param_1 = param_1 + 1;
    cVar1 = *param_1;
  } while (cVar1 != param_2);
  return param_1;
}

