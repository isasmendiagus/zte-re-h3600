// module: mt7915.ko
// function: get_channel_set_num @ 0x141a70
// size: 60 bytes
//

char get_channel_set_num(char *param_1)

{
  char cVar1;
  
  if (param_1 == (char *)0x0) {
    return '\0';
  }
  if (*param_1 == '\0') {
    return '\0';
  }
  cVar1 = '\0';
  do {
    param_1 = param_1 + 1;
    cVar1 = cVar1 + '\x01';
  } while (*param_1 != '\0');
  return cVar1;
}

