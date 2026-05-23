// module: mt7915.ko
// function: RTMPGetKeyParameterWithOffset @ 0xeef94
// size: 616 bytes
//

undefined4
RTMPGetKeyParameterWithOffset
          (char *param_1,char *param_2,ushort *param_3,size_t param_4,int param_5,byte param_6)

{
  char *pcVar1;
  size_t sVar2;
  char *pcVar3;
  char cVar4;
  byte bVar5;
  int iVar6;
  char *__s;
  char *local_28;
  char *local_24;
  
  local_28 = (char *)0x0;
  local_24 = (char *)0x0;
  if ((-1 < (short)*param_3) && (os_alloc_mem(0,&local_28,0x800), local_28 != (char *)0x0)) {
    os_alloc_mem(0,&local_24,0x800);
    if (local_24 == (char *)0x0) {
      os_free_mem(local_28);
    }
    else {
      if (*param_3 == 0) {
        iVar6 = RTMPFindSection(param_5);
        if (iVar6 == 0) {
          os_free_mem(local_28);
          os_free_mem(local_24);
          return 0;
        }
      }
      else {
        iVar6 = param_5 + (uint)*param_3;
      }
      local_28[0] = '\n';
      local_28[1] = '\0';
      strcat(local_28,param_1);
      pcVar3 = local_28;
      sVar2 = strlen(local_28);
      pcVar1 = local_28;
      (pcVar3 + sVar2)[0] = '=';
      (pcVar3 + sVar2)[1] = '\0';
      iVar6 = rtstrstr(iVar6,local_28);
      if (iVar6 != 0) {
        __s = (char *)(iVar6 + 1);
        pcVar3 = (char *)rtstrstr(__s,&_LC12);
        if (pcVar3 == (char *)0x0) {
          sVar2 = strlen(__s);
          pcVar3 = __s + sVar2;
        }
        if (__s <= pcVar3) {
          *param_3 = (short)pcVar3 - (short)param_5;
          memmove(local_24,__s,(int)pcVar3 - (int)__s);
          local_24[(int)pcVar3 - (int)__s] = '\0';
          strcpy(local_28,local_24);
          pcVar3 = local_28;
          iVar6 = rtstrstr(local_28,&_LC11);
          if (iVar6 == 0) {
            os_free_mem(pcVar3);
            os_free_mem(local_24);
            return 0;
          }
          strcpy(local_24,(char *)(iVar6 + 1));
          cVar4 = *local_24;
          pcVar3 = local_24;
          if (cVar4 != '\0') {
            if (param_6 != 0) {
              param_6 = 1;
            }
            do {
              if (cVar4 == ' ') {
                bVar5 = param_6 & 1;
              }
              else {
                bVar5 = 0;
              }
              if ((bVar5 == 0) && (cVar4 != '\t')) break;
              pcVar3 = pcVar3 + 1;
              cVar4 = *pcVar3;
            } while (cVar4 != '\0');
          }
          sVar2 = strlen(pcVar3);
          if (param_4 != 0) {
            __memzero(param_2,param_4);
          }
          if ((int)param_4 <= (int)sVar2) {
            sVar2 = param_4;
          }
          strncpy(param_2,pcVar3,sVar2);
          os_free_mem(local_28);
          os_free_mem(local_24);
          return 1;
        }
      }
      os_free_mem(pcVar1);
      os_free_mem(local_24);
    }
  }
  return 0;
}

