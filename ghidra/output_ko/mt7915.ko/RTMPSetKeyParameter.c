// module: mt7915.ko
// function: RTMPSetKeyParameter @ 0xeee88
// size: 268 bytes
//

undefined4
RTMPSetKeyParameter(char *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  size_t sVar2;
  char *pcVar3;
  size_t __n;
  char *__s;
  char local_228 [516];
  
  local_228[0] = '\0';
  local_228[1] = '\0';
  local_228[2] = '\0';
  local_228[3] = '\0';
  memset(local_228 + 4,0,0x1fc);
  iVar1 = RTMPFindSection(param_4);
  if (iVar1 == 0) {
    return 0;
  }
  local_228[0] = 10;
  strcpy(local_228 + 1,param_1);
  sVar2 = strlen(local_228);
  (local_228 + sVar2)[0] = '=';
  (local_228 + sVar2)[1] = '\0';
  iVar1 = rtstrstr(iVar1,local_228);
  if (iVar1 != 0) {
    __s = (char *)(iVar1 + 1);
    sVar2 = strlen(__s);
    pcVar3 = (char *)rtstrstr(__s,&_LC12);
    if (pcVar3 == (char *)0x0) {
      pcVar3 = __s + sVar2;
    }
    if (pcVar3 < __s) {
      return 0;
    }
    __n = strlen(pcVar3 + 1);
    os_move_mem(__s,pcVar3 + 1,__n);
    os_zero_mem(__s + __n,sVar2 - __n);
  }
  RTMPAddKeyParameter(param_1,param_2,param_3,param_4);
  return 1;
}

