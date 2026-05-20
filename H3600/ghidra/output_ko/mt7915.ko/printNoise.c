// module: mt7915.ko
// function: printNoise @ 0x155178
// size: 488 bytes
//

undefined4 printNoise(int *param_1,char *param_2)

{
  short sVar1;
  int iVar2;
  size_t sVar3;
  undefined4 uVar4;
  char *pcVar5;
  char *pcVar6;
  
  iVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar2 == 0) {
    uVar4 = 0;
  }
  else {
    iVar2 = HcGetBandByWdev(iVar2);
    sVar3 = strlen(param_2);
    pcVar6 = "====================";
    sprintf(param_2 + sVar3,"%s%-16s%s\n","===================="," NOISE ","====================");
    sVar3 = strlen(param_2);
    sVar1 = (short)iVar2;
    pcVar5 = "Enable";
    if (*(char *)((int)param_1 + iVar2 + 0xa7c304) == '\0') {
      pcVar5 = "Disable";
    }
    sprintf(param_2 + sVar3,"%-32s= %s\n","MibBucket ",pcVar5,pcVar6);
    sVar3 = strlen(param_2);
    sprintf(param_2 + sVar3,"%-32s= %d\n","Channel Busy Time ",
            param_1[(int)("CmdTxBfAwareCtrl" + sVar1 + 0x10)]);
    sVar3 = strlen(param_2);
    sprintf(param_2 + sVar3,"%-32s= %d\n","Primary Channel Busy Time ",
            param_1[(int)("CmdTxBfAwareCtrl" + sVar1 + 0xe)]);
    sVar3 = strlen(param_2);
    sprintf(param_2 + sVar3,"%-32s= %d\n","OBSS Air Time ",param_1[(int)(&UNK_0029f0c6 + sVar1)]);
    sVar3 = strlen(param_2);
    sprintf(param_2 + sVar3,"%-32s= %d\n","Tx Air Time ",
            param_1[(int)("cmd_txbf_en_dynsnd_intr" + sVar1)]);
    sVar3 = strlen(param_2);
    sprintf(param_2 + sVar3,"%-32s= %d\n","Rx Air Time ",
            param_1[(int)("cmd_txbf_en_dynsnd_intr" + sVar1 + 2)]);
    sVar3 = strlen(param_2);
    sprintf(param_2 + sVar3,"%-32s= %d\n","EDCCA Time ",
            param_1[(int)("cmd_txbf_en_dynsnd_intr" + sVar1 + 4)]);
    sVar3 = strlen(param_2);
    sprintf(param_2 + sVar3,"%-32s= %x\n","PD count ",
            param_1[(int)("cmd_txbf_en_dynsnd_intr" + sVar1 + 6)]);
    sVar3 = strlen(param_2);
    sprintf(param_2 + sVar3,"%-32s= %x\n","MDRDY Count ",
            param_1[(int)("cmd_txbf_en_dynsnd_intr" + sVar1 + 8)]);
    uVar4 = 1;
  }
  return uVar4;
}

