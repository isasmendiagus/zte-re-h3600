// module: mt7915.ko
// function: RT_CfgSetMacAddress @ 0xb8ac8
// size: 460 bytes
//

undefined4 RT_CfgSetMacAddress(int param_1,char *param_2,int param_3,int param_4)

{
  size_t sVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  undefined4 uVar5;
  
  sVar1 = strlen(param_2);
  if (sVar1 == 0x11) {
    iVar2 = strcmp(param_2,"00:00:00:00:00:00");
    if (iVar2 == 0) {
      uVar5 = 0;
      if (-1 < DebugLevel) {
        printk("%s : invalid mac setting\n","RT_CfgSetMacAddress");
      }
    }
    else {
      if (param_4 != 1) {
        if (param_4 == 0) {
          iVar2 = param_3 * 6 + param_1 + 0x794c1c;
          pcVar4 = param_2;
          do {
            pcVar3 = pcVar4 + 3;
            AtoH(pcVar4,iVar2,1);
            iVar2 = iVar2 + 1;
            pcVar4 = pcVar3;
          } while (pcVar3 != param_2 + 0x12);
        }
        else if (0 < DebugLevel) {
          printk("%s: idx(%d) non-supported opmode(%d)\n","RT_CfgSetMacAddress",param_3,param_4);
          return 1;
        }
        return 1;
      }
      if (param_3 == 0) {
        iVar2 = param_1 + 0x794b5b;
        pcVar4 = param_2;
        do {
          pcVar3 = pcVar4 + 3;
          AtoH(pcVar4,iVar2,1);
          iVar2 = iVar2 + 1;
          pcVar4 = pcVar3;
        } while (pcVar3 != param_2 + 0x12);
        uVar5 = 1;
        *(undefined1 *)(param_1 + 0x794b54) = 1;
      }
      else {
        iVar2 = param_1 + (param_3 + -1) * 6 + 0x794b61;
        pcVar4 = param_2;
        do {
          pcVar3 = pcVar4 + 3;
          AtoH(pcVar4,iVar2,1);
          iVar2 = iVar2 + 1;
          pcVar4 = pcVar3;
        } while (pcVar3 != param_2 + 0x12);
        uVar5 = 1;
        *(undefined1 *)(param_1 + 0x794c1b) = 1;
      }
    }
  }
  else if (DebugLevel < 0) {
    uVar5 = 0;
  }
  else {
    uVar5 = 0;
    printk("%s : invalid length (%d)\n","RT_CfgSetMacAddress",sVar1);
  }
  return uVar5;
}

