// module: mt7915.ko
// function: rstrtok @ 0xee3c8
// size: 136 bytes
//

char * rstrtok(char *param_1,char *param_2)

{
  size_t sVar1;
  
  if ((param_1 == (char *)0x0) && (param_1 = __rstrtok, __rstrtok == (char *)0x0)) {
    return (char *)0x0;
  }
  sVar1 = strspn(param_1,param_2);
  if (param_1[sVar1] == 0) {
    __rstrtok = (char *)(int)param_1[sVar1];
    return (char *)0x0;
  }
  __rstrtok = strpbrk(param_1 + sVar1,param_2);
  if ((__rstrtok != (char *)0x0) && (*__rstrtok != '\0')) {
    *__rstrtok = '\0';
    __rstrtok = __rstrtok + 1;
  }
  return param_1 + sVar1;
}

