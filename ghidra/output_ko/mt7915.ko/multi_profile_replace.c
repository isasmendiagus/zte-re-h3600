// module: mt7915.ko
// function: multi_profile_replace @ 0x164e10
// size: 68 bytes
//

void multi_profile_replace(char *param_1,char *param_2,char *param_3)

{
  size_t __n;
  char *__dest;
  
  while (__dest = strstr(param_3,param_1), __dest != (char *)0x0) {
    __n = strlen(param_2);
    strncpy(__dest,param_2,__n);
  }
  return;
}

