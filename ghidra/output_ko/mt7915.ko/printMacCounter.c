// module: mt7915.ko
// function: printMacCounter @ 0x154d3c
// size: 1084 bytes
//

undefined4 printMacCounter(int *param_1,char *param_2)

{
  int iVar1;
  size_t sVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  char *__format;
  char *pcVar6;
  uint uVar7;
  int iVar8;
  uint local_2c;
  
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar1 == 0) {
    uVar5 = 0;
  }
  else {
    iVar1 = HcGetBandByWdev(iVar1);
    sVar2 = strlen(param_2);
    sprintf(param_2 + sVar2,"%s%-16s%s\n","===================="," MAC COUNTER ",
            "====================");
    uVar7 = param_1[iVar1 * 0x42 + 0x28e700];
    sVar2 = strlen(param_2);
    sprintf(param_2 + sVar2,"%-32s= %d\n","Tx success count ",uVar7);
    iVar3 = hc_get_hif_type(param_1[0x29e5e8]);
    local_2c = uVar7;
    if (iVar3 == 2) {
      if (uVar7 == 0) {
        iVar3 = param_1[iVar1 * 0x42 + 0x28e704];
      }
      else {
        iVar3 = param_1[iVar1 * 0x42 + 0x28e704];
        uVar7 = __aeabi_uidiv(iVar3 * 1000,iVar3 + uVar7);
        local_2c = uVar7 / 10;
        uVar7 = uVar7 % 10;
      }
      sVar2 = strlen(param_2);
      __format = "%-32s= %ld PER=%ld.%1ld%%\n";
      pcVar6 = "Tx fail count ";
    }
    else {
      if (uVar7 == 0) {
        iVar3 = param_1[iVar1 * 0x42 + 0x28e706];
      }
      else {
        iVar3 = param_1[iVar1 * 0x42 + 0x28e706];
        uVar7 = __aeabi_uidiv((iVar3 + param_1[iVar1 * 0x42 + 0x28e704]) * 1000,
                              iVar3 + param_1[iVar1 * 0x42 + 0x28e704] + uVar7);
        local_2c = uVar7 / 10;
        uVar7 = uVar7 % 10;
      }
      sVar2 = strlen(param_2);
      __format = "%-32s= %ld, PER=%ld.%1ld%%\n";
      pcVar6 = "Tx retry count ";
    }
    sprintf(param_2 + sVar2,__format,pcVar6,iVar3,local_2c,uVar7);
    sVar2 = strlen(param_2);
    sprintf(param_2 + sVar2,"%-32s= %x %x\n","Tx BF count(iBF/eBF) ",param_1[0x29f0bc],
            param_1[0x29f0bd]);
    sVar2 = strlen(param_2);
    sprintf(param_2 + sVar2,"%-32s= %ld\n","Tx AGG Range 1 (1)",param_1[0x28e71e]);
    sVar2 = strlen(param_2);
    sprintf(param_2 + sVar2,"%-32s= %ld\n","Tx AGG Range 2 (2~5)",param_1[0x28e720]);
    sVar2 = strlen(param_2);
    sprintf(param_2 + sVar2,"%-32s= %ld\n","Tx AGG Range 3 (6~15)",param_1[0x28e722]);
    sVar2 = strlen(param_2);
    sprintf(param_2 + sVar2,"%-32s= %ld\n","Tx AGG Range 4 (>15)",param_1[0x28e724]);
    sVar2 = strlen(param_2);
    iVar3 = param_1[0x28e728];
    sprintf(param_2 + sVar2,"%-32s= %ld\n","Tx AMPDU success",iVar3);
    iVar8 = param_1[0x28e726];
    if (iVar3 == 0) {
      uVar4 = 0;
      uVar7 = 0;
    }
    else {
      uVar4 = __aeabi_uidiv(iVar8 * 1000,iVar8 + iVar3);
      uVar7 = uVar4 / 10;
      uVar4 = uVar4 % 10;
    }
    sVar2 = strlen(param_2);
    sprintf(param_2 + sVar2,"%-32s= %ld PER=%ld.%1ld%%\n","Tx AMPDU fail count",iVar8,uVar7,uVar4);
    sVar2 = strlen(param_2);
    sprintf(param_2 + sVar2,"%-32s= %d\n","Rx success ",param_1[iVar1 * 0x42 + 0x28e712]);
    if (param_1[iVar1 * 0x42 + 0x28e712] == 0) {
      iVar3 = param_1[iVar1 * 0x42 + 0x28e716];
      uVar4 = 0;
      uVar7 = 0;
    }
    else {
      iVar3 = param_1[iVar1 * 0x42 + 0x28e716];
      uVar4 = __aeabi_uidiv(iVar3 * 1000,iVar3 + param_1[iVar1 * 0x42 + 0x28e712]);
      uVar7 = uVar4 / 10;
      uVar4 = uVar4 % 10;
    }
    sVar2 = strlen(param_2);
    sprintf(param_2 + sVar2,"%-32s= %ld, PER=%ld.%1ld%%\n","Rx with CRC ",iVar3,uVar7,uVar4);
    sVar2 = strlen(param_2);
    sprintf(param_2 + sVar2,"%-32s= %ld\n","Rx drop(out of resource)",param_1[0x28e6fd]);
    sVar2 = strlen(param_2);
    sprintf(param_2 + sVar2,"%-32s= %ld\n","Rx duplicate frame",param_1[iVar1 * 0x42 + 0x28e710]);
    uVar5 = 1;
  }
  return uVar5;
}

