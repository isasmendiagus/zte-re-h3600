// module: mt7915.ko
// function: HeRaMuMetricInfoPrint @ 0x87b64
// size: 504 bytes
//

void HeRaMuMetricInfoPrint(undefined4 param_1,undefined1 *param_2)

{
  int iVar1;
  undefined1 *puVar2;
  
  if (DebugLevel < 1) goto LAB_00087b84;
  printk("============================= Global ===============================\n");
  if (DebugLevel < 1) {
LAB_00087cb0:
    if (0 < DebugLevel) {
      printk("u1PendingReqCnt=0x%02X\n",param_2[4]);
      if (DebugLevel < 1) goto LAB_00087b84;
      printk("u1PollingTime=0x%02X\n",param_2[5]);
      goto LAB_00087cf0;
    }
  }
  else {
    printk("u1CurState=0x%02X\n",*param_2);
    if (DebugLevel < 1) goto LAB_00087b84;
    printk("u1RunningFailCnt=0x%02X\n",param_2[1]);
    if (0 < DebugLevel) {
      printk("u1ErrRptCnt=0x%02X\n",param_2[2]);
      if (DebugLevel < 1) goto LAB_00087b84;
      printk("u1FreeReqCnt=0x%02X\n",param_2[3]);
      goto LAB_00087cb0;
    }
LAB_00087cf0:
    if ((DebugLevel < 1) || (printk("u1NUser=0x%02X\n",param_2[6]), DebugLevel < 1))
    goto LAB_00087b84;
    printk("fgIsLQErr=0x%02X\n",param_2[7]);
  }
  if (0 < DebugLevel) {
    printk("u2LQErr=0x%02X\n\n",*(undefined2 *)(param_2 + 8));
  }
LAB_00087b84:
  iVar1 = 0;
  puVar2 = param_2;
  do {
    if ((0 < DebugLevel) &&
       (printk("============================= User %d ==============================\n",iVar1),
       0 < DebugLevel)) {
      printk("BPSK=0x%02X, QPSK=0x%02X, 16QAM=0x%02X, 64QAM=0x%02X\n",puVar2[0xc],puVar2[0xd],
             puVar2[0xe],puVar2[0xf]);
      if (0 < DebugLevel) {
        printk("u1256QAM=0x%02X, u11024QAM=0x%02X, u1Capacity=0x%02X, InitMCS=0x%02X\n\n",
               param_2[iVar1 * 8 + 0x10],param_2[iVar1 * 8 + 0x11],param_2[iVar1 * 8 + 0x12],
               param_2[iVar1 + 0x2c]);
      }
    }
    iVar1 = iVar1 + 1;
    puVar2 = puVar2 + 8;
  } while (iVar1 != 4);
  return;
}

