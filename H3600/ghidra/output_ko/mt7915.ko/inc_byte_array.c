// module: mt7915.ko
// function: inc_byte_array @ 0x572c0
// size: 80 bytes
//

void inc_byte_array(char *param_1,int param_2)

{
  char cVar1;
  char *pcVar2;
  
  param_2 = param_2 + -1;
  if (param_2 < 0) {
    return;
  }
  cVar1 = param_1[param_2];
  pcVar2 = param_1 + param_2;
  param_1[param_2] = cVar1 + '\x01';
  if ((char)(cVar1 + '\x01') != '\0') {
    return;
  }
  do {
    if (pcVar2 == param_1) {
      return;
    }
    pcVar2 = pcVar2 + -1;
    cVar1 = *pcVar2;
    *pcVar2 = cVar1 + '\x01';
  } while ((char)(cVar1 + '\x01') == '\0');
  return;
}

