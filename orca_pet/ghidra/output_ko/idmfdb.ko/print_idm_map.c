// module: idmfdb.ko
// function: print_idm_map @ 0x10a38
// size: 252 bytes
//

int print_idm_map(undefined4 param_1,char *param_2,size_t param_3)

{
  byte *pbVar1;
  byte *pbVar2;
  byte *pbVar3;
  int iVar4;
  int iVar5;
  byte *pbVar6;
  int iVar7;
  byte bVar8;
  
  if ((int)param_3 < 1) {
    iVar7 = 0;
  }
  else {
    iVar7 = snprintf(param_2,param_3,"wlan_dev_map:\n");
    if (iVar7 < (int)param_3) {
      iVar4 = snprintf(param_2 + iVar7,param_3 - iVar7,"fdb_list:\n");
      iVar7 = iVar7 + iVar4;
    }
  }
  iVar4 = 0;
  pbVar6 = &fdb_list;
  do {
    while( true ) {
      if (iVar7 < (int)param_3) {
        bVar8 = *pbVar6 & 1;
      }
      else {
        bVar8 = 0;
      }
      if (bVar8 == 0) break;
      pbVar1 = pbVar6 + 1;
      pbVar2 = pbVar6 + 3;
      pbVar3 = pbVar6 + 0x14;
      pbVar6 = pbVar6 + 0x128;
      iVar5 = snprintf(param_2 + iVar7,param_3 - iVar7,"%d: idm:%d ssid:%d dev:%s\n",iVar4,
                       (uint)*pbVar1,(uint)*pbVar2,*(undefined4 *)pbVar3);
      iVar4 = iVar4 + 1;
      iVar7 = iVar7 + iVar5;
      if (pbVar6 == &__this_module) goto LAB_00010b08;
    }
    pbVar6 = pbVar6 + 0x128;
    iVar4 = iVar4 + 1;
  } while (pbVar6 != &__this_module);
LAB_00010b08:
  if (iVar7 < (int)param_3) {
    iVar4 = snprintf(param_2 + iVar7,param_3 - iVar7,"\n");
    iVar7 = iVar4 + iVar7;
  }
  return iVar7;
}

