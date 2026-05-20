// module: mt7915.ko
// function: twtPlannerDbgPrintVal @ 0x169da0
// size: 316 bytes
//

void twtPlannerDbgPrintVal(undefined4 param_1,undefined1 *param_2)

{
  if (DebugLevel < 3) {
    return;
  }
  printk("prTWTParams->fgReq = %d\n",*param_2);
  if (DebugLevel < 3) {
LAB_00169e3c:
    if (DebugLevel < 3) goto LAB_00169ebc;
    printk("prTWTParams->tsf_low = %d\n",*(undefined4 *)(param_2 + 0x10));
    if (DebugLevel < 3) {
      return;
    }
    printk("prTWTParams->tsf_high = %d\n",*(undefined4 *)(param_2 + 0x14));
  }
  else {
    printk("prTWTParams->ucSetupCmd = %d\n",param_2[4]);
    if (DebugLevel < 3) {
      return;
    }
    printk("prTWTParams->fgTrigger = %d\n",param_2[1]);
    if (2 < DebugLevel) {
      printk("prTWTParams->fgUnannounced = %d\n",param_2[3]);
      if (DebugLevel < 3) {
        return;
      }
      printk("prTWTParams->ucWakeIntvalExponent = %d\n",param_2[6]);
      goto LAB_00169e3c;
    }
  }
  if (DebugLevel < 3) {
    return;
  }
  printk("prTWTParams->fgProtect = %d\n",param_2[2]);
  if (DebugLevel < 3) {
    return;
  }
  printk("prTWTParams->ucMinWakeDur = %d\n",param_2[5]);
LAB_00169ebc:
  if (DebugLevel < 3) {
    return;
  }
  printk("prTWTParams->u2WakeIntvalMantiss = %d\n",*(undefined2 *)(param_2 + 8));
  return;
}

