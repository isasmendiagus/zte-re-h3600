// module: mt7915.ko
// function: printBasicinfo @ 0x153e20
// size: 208 bytes
//

bool printBasicinfo(int *param_1,char *param_2)

{
  int iVar1;
  undefined4 uVar2;
  size_t sVar3;
  undefined4 local_14;
  
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  local_14 = 0;
  if (iVar1 != 0) {
    uVar2 = HcGetBandByWdev(iVar1);
    sVar3 = strlen(param_2);
    sprintf(param_2 + sVar3,"%s%-16s%s\n","===================="," BASIC ","====================");
    sVar3 = strlen(param_2);
    sprintf(param_2 + sVar3,"%-32s= %d\n","Current Band ",uVar2);
    RTMP_GET_TEMPERATURE(param_1,uVar2,&local_14);
    sVar3 = strlen(param_2);
    sprintf(param_2 + sVar3,"%-32s= %d\n","Current Temperature ",local_14);
  }
  return iVar1 != 0;
}

