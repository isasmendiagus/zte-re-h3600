// module: mt7915.ko
// function: DfsDedicatedOutBandSetChannel @ 0x236a54
// size: 624 bytes
//

void DfsDedicatedOutBandSetChannel(int param_1,uint param_2,uint param_3,undefined4 param_4)

{
  int iVar1;
  char *pcVar2;
  undefined4 uVar3;
  
  if (0 < DebugLevel) {
    printk("[%s] SynNum: %d, Channel: %d, Bw: %d\n","DfsDedicatedOutBandSetChannel",param_4,param_2,
           param_3);
  }
  if (*(char *)(param_1 + 0x7953fa) == '\0') {
    if (DebugLevel < 0) {
      return;
    }
    pcVar2 = "[%s] DedicatedZeroWaitSupport is not enabled\n";
    goto LAB_00236b14;
  }
  iVar1 = DfsDedicatedCheckChBwValid(param_1,param_2,param_3,0);
  if ((iVar1 == 0) && (iVar1 = DfsDedicatedCheckChBwValid(param_1,param_2,param_3,1), iVar1 == 0)) {
    if (2 < DebugLevel) {
      printk("%s(): Get new outband DFS channel\n","DfsDedicatedOutBandSetChannel");
    }
    DfsDedicatedOutBandRDDRunning(param_1);
    param_2 = (uint)*(byte *)(param_1 + 0x7953fb);
    if (param_2 == 0) {
      if (DebugLevel < 1) {
        return;
      }
      pcVar2 = "\x1b[1;33m [%s] No valid OutBand Channel. Fail. \x1b[m \n";
      goto LAB_00236b14;
    }
    param_3 = (uint)*(byte *)(param_1 + 0x7953fc);
    iVar1 = RadarChannelCheck(param_1,param_2);
    if (iVar1 != 0) {
LAB_00236b3c:
      *(char *)(param_1 + 0x7953fb) = (char)param_2;
      *(char *)(param_1 + 0x7953fc) = (char)param_3;
LAB_00236b44:
      if (*(int *)(param_1 + 0xa79184) == 2) {
        if (0 < DebugLevel) {
          printk("Dediated Running: OutBand set Channel to %d\n",param_2);
        }
LAB_00236c3c:
        uVar3 = 8;
        goto LAB_00236b88;
      }
      if (*(int *)(param_1 + 0xa79184) != 0) {
        if (DebugLevel < 1) {
          return;
        }
        printk("Wrong state. OutBand Set Channel Fail\n");
        return;
      }
      if (0 < DebugLevel) {
        printk("Dedicated Start: OutBand set Channel to %d\n",param_2);
      }
      goto LAB_00236b6c;
    }
  }
  else {
    iVar1 = RadarChannelCheck(param_1,param_2);
    if (iVar1 != 0) {
      if (param_2 != 0) goto LAB_00236b3c;
      if (0 < DebugLevel) {
        printk("Pick OutBand Ch by internal Alogorithm\n");
        goto LAB_00236b44;
      }
      if (*(int *)(param_1 + 0xa79184) == 2) goto LAB_00236c3c;
      if (*(int *)(param_1 + 0xa79184) != 0) {
        return;
      }
LAB_00236b6c:
      uVar3 = 0xc;
LAB_00236b88:
      MlmeEnqueue(param_1,0x2b,uVar3,0,0,0);
      RtmpOsMlmeUp(param_1 + 0x286298);
      return;
    }
  }
  if (DebugLevel < 1) {
    return;
  }
  pcVar2 = "\x1b[1;33m [%s] Not a DFS Channel. No need for Radar Detection. \x1b[m \n";
LAB_00236b14:
  printk(pcVar2,"DfsDedicatedOutBandSetChannel");
  return;
}

