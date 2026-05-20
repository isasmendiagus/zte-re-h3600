// module: idmfdb.ko
// function: print_idm_flood_status @ 0x10a5c
// size: 332 bytes
//

int print_idm_flood_status(undefined4 param_1,char *param_2,size_t param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  
  if ((int)param_3 < 1) {
    iVar2 = 0;
  }
  else {
    iVar2 = snprintf(param_2,param_3,"idm_flood_status:\n");
  }
  iVar3 = 0;
  do {
    if (iVar2 < (int)param_3) {
      iVar1 = snprintf(param_2 + iVar2,param_3 - iVar2,"idm%d:\n",iVar3);
      iVar2 = iVar2 + iVar1;
      if (iVar2 < (int)param_3) {
        iVar1 = snprintf(param_2 + iVar2,param_3 - iVar2,"  UNICAST   %10lld\n");
        iVar2 = iVar2 + iVar1;
        if (iVar2 < (int)param_3) {
          iVar1 = snprintf(param_2 + iVar2,param_3 - iVar2,"  MULTICAST %10lld\n");
          iVar2 = iVar2 + iVar1;
          if (iVar2 < (int)param_3) {
            iVar1 = snprintf(param_2 + iVar2,param_3 - iVar2,"  BROADCAST %10lld\n");
            iVar2 = iVar2 + iVar1;
            if (iVar2 < (int)param_3) {
              iVar1 = snprintf(param_2 + iVar2,param_3 - iVar2,"  DROP      %10lld\n");
              iVar2 = iVar2 + iVar1;
            }
          }
        }
      }
    }
    bVar4 = iVar3 != 1;
    iVar3 = 1;
  } while (bVar4);
  if (iVar2 < (int)param_3) {
    iVar3 = snprintf(param_2 + iVar2,param_3 - iVar2,"\n");
    return iVar2 + iVar3;
  }
  return iVar2;
}

