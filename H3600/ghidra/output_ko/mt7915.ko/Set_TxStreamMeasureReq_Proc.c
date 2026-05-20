// module: mt7915.ko
// function: Set_TxStreamMeasureReq_Proc @ 0x21fd10
// size: 916 bytes
//

undefined4 Set_TxStreamMeasureReq_Proc(int *param_1,char *param_2)

{
  short sVar1;
  char *pcVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  char *local_2c;
  undefined2 local_26;
  undefined1 local_24;
  undefined1 local_23;
  undefined1 local_22;
  char local_21;
  char local_20;
  char local_1f;
  undefined1 local_1e;
  undefined1 local_1d;
  undefined1 local_1c;
  undefined1 local_1b;
  undefined1 local_1a;
  undefined1 local_19;
  
  uVar7 = *(uint *)(*param_1 + 0x3c);
  local_2c = param_2;
  __memzero(&local_26,0xe);
  uVar3 = 0;
  uVar6 = 1;
  do {
    pcVar2 = strsep(&local_2c,"-");
    if (pcVar2 == (char *)0x0) {
      if ((uVar3 & 0xfffffff7) == 5) {
        local_22 = uVar3 != 5;
        if (-1 < DebugLevel) {
          uVar3 = (uint)*(byte *)((int)param_1 + uVar6 * 0x14c0 + 0xa1e0d);
          uVar4 = (uint)*(byte *)((int)param_1 + uVar6 * 0x14c0 + 0xa1e0e);
          uVar5 = (uint)*(byte *)((int)param_1 + uVar6 * 0x14c0 + 0xa1e0f);
          uVar9 = (uint)*(byte *)(param_1 + uVar6 * 0x530 + 0x28784);
          uVar8 = (uint)*(byte *)((int)param_1 + uVar6 * 0x14c0 + 0xa1e11);
          printk("%s::Aid=%d, PeerMac=%02x:%02x:%02x:%02x:%02x:%02x\n","Set_TxStreamMeasureReq_Proc"
                 ,uVar6,(char)param_1[uVar6 * 0x530 + 0x28783],uVar3,uVar4,uVar5,uVar9,uVar8);
          if ((((-1 < DebugLevel) &&
               (printk("Duration=%d, Tid=%d, Bin 0 Range=%d\n",local_26,local_24,local_23,uVar3,
                       uVar4,uVar5,uVar9,uVar8), -1 < DebugLevel)) &&
              (printk("ArvCondition=%d, ConsecutiveCondition=%d, DelayCondition=%d\n",local_21,
                      local_20,local_1f,uVar3,uVar4,uVar5,uVar9,uVar8), -1 < DebugLevel)) &&
             ((printk("AvrErrorThreshold=%d, ConsecutiveErrorThreshold=%d\n",local_1e,local_1d,
                      DebugLevel,uVar3,uVar4,uVar5,uVar9,uVar8), -1 < DebugLevel &&
              (printk("DelayThreshold=%d\n",local_1c), -1 < DebugLevel)))) {
            printk("MeasureCnt=%d, TriggerTimeout=%d\n",local_1b,local_1a);
          }
        }
        RRM_EnqueueTxStreamMeasureReq(param_1,uVar6,uVar7 & 0xff,&local_26);
      }
      else if ((-1 < DebugLevel) &&
              (printk("%s: invalid args (%d).\n","Set_TxStreamMeasureReq_Proc",uVar3),
              -1 < DebugLevel)) {
        printk(
              "eg: iwpriv ra0 set txreq=<Aid>-<DurationMandortory>-<Duration>-<TID>-<BinRange>[-<AvrCond>-<ConsecutiveCond>-<DealyCond>-<AvrErrorThreshold>-<ConsecutiveErrorThreshold>-<DelayThreshold>-<MeasureCnt>-<TriggerTimeout>]\n"
              );
      }
      return 1;
    }
    switch(uVar3) {
    case 0:
      uVar6 = os_str_tol(pcVar2,0,10);
      uVar6 = uVar6 & 0xff;
      uVar4 = hc_get_chip_wtbl_max_num(param_1[0x29e5e8]);
      if (uVar4 <= uVar6) {
        if (DebugLevel < 0) {
          return 1;
        }
        printk("%s: unknow sta of Aid(%d)\n","Set_TxStreamMeasureReq_Proc",uVar6);
        return 1;
      }
      break;
    case 1:
      sVar1 = os_str_tol(pcVar2,0,10);
      local_19 = sVar1 != 0;
      break;
    case 2:
      local_26 = os_str_tol(pcVar2,0,10);
      break;
    case 3:
      local_24 = os_str_tol(pcVar2,0,10);
      break;
    case 4:
      local_23 = os_str_tol(pcVar2,0,10);
      break;
    case 5:
      local_21 = os_str_tol(pcVar2,0,10);
      if (local_21 != '\0') {
        local_21 = '\x01';
      }
      break;
    case 6:
      local_20 = os_str_tol(pcVar2,0,10);
      if (local_20 != '\0') {
        local_20 = '\x01';
      }
      break;
    case 7:
      local_1f = os_str_tol(pcVar2,0,10);
      if (local_1f != '\0') {
        local_1f = '\x01';
      }
      break;
    case 8:
      local_1e = os_str_tol(pcVar2,0,10);
      break;
    case 9:
      local_1d = os_str_tol(pcVar2,0,10);
      break;
    case 10:
      local_1c = os_str_tol(pcVar2,0,10);
      break;
    case 0xb:
      local_1b = os_str_tol(pcVar2,0,10);
      break;
    case 0xc:
      local_1a = os_str_tol(pcVar2,0,10);
    }
    uVar3 = uVar3 + 1;
  } while( true );
}

