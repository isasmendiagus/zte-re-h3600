// module: mt7915.ko
// function: CntlWscIterate @ 0x70f44
// size: 196 bytes
//

void CntlWscIterate(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  bool bVar3;
  
  if (2 < DebugLevel) {
    printk("%s():: wsc_ctrl->WscState = %d (WSC_STATE_START = %d, STATUS_WSC_SCAN_AP = %d)!!\n",
           "CntlWscIterate",*(undefined4 *)(param_2 + 0x12f4),2,0x23);
  }
  if ((1 < *(int *)(param_2 + 0x12f4)) && (*(int *)(param_2 + 0x12f0) != 0x23)) {
    *(undefined4 *)(param_2 + 0x12f0) = 0x27;
    *(undefined4 *)(param_2 + 0x12f4) = 2;
    bVar3 = *(char *)(param_2 + 0x4060) != '\0';
    if (bVar3) {
      iVar2 = param_2 + 0x1331;
      uVar1 = 6;
    }
    else {
      iVar2 = param_2 + 0x130c;
      uVar1 = 0x24;
    }
    cntl_connect_request(param_2,bVar3,uVar1,iVar2);
  }
  uVar1 = HcGetBandByWdev(param_2);
  RTMPSetLED(param_1,8,uVar1);
  return;
}

