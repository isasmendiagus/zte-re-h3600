// module: mt7915.ko
// function: RTMPGetKeyParameter @ 0xeecb0
// size: 416 bytes
//

undefined4
RTMPGetKeyParameter(char *param_1,char *param_2,size_t param_3,undefined4 param_4,char param_5)

{
  char cVar1;
  int iVar2;
  size_t sVar3;
  char *pcVar4;
  char *pcVar5;
  char *pcVar6;
  char *local_24 [2];
  
  os_alloc_mem(0,local_24,0x1000);
  if (local_24[0] == (char *)0x0) {
    return 0;
  }
  __memzero(local_24[0],0x1000);
  pcVar6 = local_24[0];
  iVar2 = RTMPFindSection(param_4);
  if (iVar2 != 0) {
    *pcVar6 = '\n';
    strcpy(pcVar6 + 1,param_1);
    sVar3 = strlen(pcVar6);
    (pcVar6 + sVar3)[0] = '=';
    (pcVar6 + sVar3)[1] = '\0';
    iVar2 = rtstrstr(iVar2,pcVar6);
    if (iVar2 != 0) {
      pcVar5 = (char *)(iVar2 + 1);
      pcVar4 = (char *)rtstrstr(pcVar5,&_LC12);
      if (pcVar4 == (char *)0x0) {
        sVar3 = strlen(pcVar5);
        pcVar4 = pcVar5 + sVar3;
      }
      if (pcVar5 <= pcVar4) {
        pcVar6 = pcVar6 + 0x800;
        memmove(pcVar6,pcVar5,(int)pcVar4 - (int)pcVar5);
        pcVar6[(int)pcVar4 - (int)pcVar5] = '\0';
        pcVar6 = (char *)rtstrstr(pcVar6,&_LC11);
        if (pcVar6 != (char *)0x0) {
          pcVar4 = pcVar6 + 1;
          pcVar5 = pcVar4;
          cVar1 = *pcVar6;
          while (cVar1 != '\0') {
            while( true ) {
              pcVar5 = pcVar4;
              pcVar4 = pcVar5 + 1;
              cVar1 = param_5;
              if (*pcVar5 == ' ') break;
              if (*pcVar5 != '\t') goto LAB_000eeddc;
            }
          }
LAB_000eeddc:
          sVar3 = strlen(pcVar6);
          if (param_3 != 0) {
            __memzero(param_2,param_3);
          }
          if ((int)param_3 <= (int)sVar3) {
            sVar3 = param_3;
          }
          strncpy(param_2,pcVar5,sVar3);
          os_free_mem(local_24[0]);
          return 1;
        }
      }
    }
  }
  os_free_mem(local_24[0]);
  return 0;
}

