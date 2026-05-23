// module: mt7915.ko
// function: dumpBndStrgInfo @ 0x34ea0
// size: 860 bytes
//

void dumpBndStrgInfo(int param_1,int param_2)

{
  if (DebugLevel < param_2) {
    return;
  }
  printk("\n======================================\n");
  if (DebugLevel < param_2) {
LAB_00034f3c:
    if (param_2 <= DebugLevel) {
      printk("b5GInfReady=%d\n",*(undefined1 *)(param_1 + 0x1021));
      if (DebugLevel < param_2) {
        return;
      }
      printk("RssiDiff=%d\n",(int)*(char *)(param_1 + 0x1022));
      goto LAB_00034f80;
    }
LAB_00034fc4:
    if (param_2 <= DebugLevel) {
      printk("AgeTime=%d\n",*(undefined4 *)(param_1 + 0x1028));
      if (DebugLevel < param_2) {
        return;
      }
      printk("HoldTime=%d\n",*(undefined4 *)(param_1 + 0x102c));
      goto LAB_00035008;
    }
LAB_0003504c:
    if (param_2 <= DebugLevel) {
      printk("ucChanUtilization_2G=%d\n",*(undefined1 *)(param_1 + 0x108c));
      if (DebugLevel < param_2) {
        return;
      }
      printk("ucChanUtilization_5G=%d\n",*(undefined1 *)(param_1 + 0x108d));
      goto LAB_00035090;
    }
LAB_000350d4:
    if (param_2 <= DebugLevel) {
      printk("ConditionCheck=%d\n",*(undefined4 *)(param_1 + 0x10));
      if (DebugLevel < param_2) {
        return;
      }
      printk("FrameCheck=%d\n",*(undefined4 *)(param_1 + 0xc));
      goto LAB_00035114;
    }
LAB_00035158:
    if (DebugLevel < param_2) goto LAB_000351e0;
    printk("LoadingPara.Method=%d\n",*(undefined1 *)(param_1 + 0x1078));
    if (DebugLevel < param_2) {
      return;
    }
    printk("LoadingPara.OneSecondeLoading=%d\n",*(undefined4 *)(param_1 + 0x107c));
  }
  else {
    printk("Drv bnstrg info:\n");
    if (DebugLevel < param_2) {
      return;
    }
    printk("bInitialized=%d\n",*(undefined1 *)(param_1 + 4));
    if (param_2 <= DebugLevel) {
      printk("bEnabled=%d\n",*(undefined1 *)(param_1 + 5));
      if (DebugLevel < param_2) {
        return;
      }
      printk("b2GInfReady=%d\n",*(undefined1 *)(param_1 + 0x1020));
      goto LAB_00034f3c;
    }
LAB_00034f80:
    if (param_2 <= DebugLevel) {
      printk("RssiHigh=%d\n",(int)*(char *)(param_1 + 0x1024));
      if (DebugLevel < param_2) {
        return;
      }
      printk("RssiLow=%d\n",(int)*(char *)(param_1 + 0x1023));
      goto LAB_00034fc4;
    }
LAB_00035008:
    if (param_2 <= DebugLevel) {
      printk("CheckTime_5G=%d\n",*(undefined4 *)(param_1 + 0x1030));
      if (DebugLevel < param_2) {
        return;
      }
      printk("ucChanUtilThreshold=%d\n",*(undefined1 *)(param_1 + 0x1025));
      goto LAB_0003504c;
    }
LAB_00035090:
    if (param_2 <= DebugLevel) {
      printk("ulBandSwitchLoadThreshhold=%d\n",*(undefined4 *)(param_1 + 0x1090));
      if (DebugLevel < param_2) {
        return;
      }
      printk("ulSteeringDetectInterval=%d\n",*(undefined4 *)(param_1 + 0x1088));
      goto LAB_000350d4;
    }
LAB_00035114:
    if (param_2 <= DebugLevel) {
      printk("Band=%d\n",*(undefined1 *)(param_1 + 0x106e));
      if (DebugLevel < param_2) {
        return;
      }
      printk("AutoOnOffThrd=%d\n",*(undefined4 *)(param_1 + 0x1070));
      goto LAB_00035158;
    }
  }
  if (DebugLevel < param_2) {
    return;
  }
  printk("LoadingPara.TXRXCOUNT=%d\n",*(undefined4 *)(param_1 + 0x1080));
  if (DebugLevel < param_2) {
    return;
  }
  printk("LoadingPara.KickOff_STA_Method=%d\n",*(undefined1 *)(param_1 + 0x1084));
LAB_000351e0:
  if (DebugLevel < param_2) {
    return;
  }
  printk("======================================\n");
  return;
}

