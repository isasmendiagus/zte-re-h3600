// module: mt7915.ko
// function: printPhyCounter @ 0x15557c
// size: 152 bytes
//

undefined4 printPhyCounter(int *param_1,char *param_2)

{
  int iVar1;
  size_t sVar2;
  undefined4 uVar3;
  
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar1 == 0) {
    uVar3 = 0;
  }
  else {
    HcGetBandByWdev(iVar1);
    sVar2 = strlen(param_2);
    sprintf(param_2 + sVar2,"%s%-16s%s\n","===================="," PHY COUNTER ",
            "====================");
    if ((*(byte *)(param_1 + 0x29f0ba) & 0x20) != 0) {
      printCNNum(param_1,param_2);
      return 1;
    }
    uVar3 = 1;
  }
  return uVar3;
}

