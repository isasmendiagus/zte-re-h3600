// module: mt7915.ko
// function: mt_wifi_init @ 0x13d440
// size: 1172 bytes
//

undefined4 mt_wifi_init(int *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  char cVar7;
  int *piVar2;
  
  if (param_1 == (int *)0x0) {
    return 0;
  }
  if (2 < DebugLevel) {
    printk(&_LC7,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  }
  if (*(char *)((int)param_1 + 0x286285) == '\x01') {
    piVar2 = param_1 + 0xadc92;
  }
  else {
    if (*(char *)((int)param_1 + 0x286285) != '\0') {
      if (DebugLevel < 0) {
        return 0;
      }
      printk("[mt_wifi_init] wdev == NULL\n");
      return 0;
    }
    piVar2 = param_1 + 0xdb6d6;
  }
  uVar1 = HcGetBandByWdev(piVar2);
  iVar3 = hc_get_channel_ctrl(param_1[0x29e5e8],uVar1);
  iVar4 = hc_get_channel_ctrl(param_1[0x29e5e8],1);
  uVar5 = hc_get_chip_cap(param_1[0x29e5e8]);
  asic_show_mac_info(param_1);
  param_1[0x28e7e1] = 0;
  wifi_sys_reset(param_1 + 0x29efb5);
  iVar6 = RtmpMgmtTaskInit(param_1);
  if (iVar6 == 0) {
    iVar6 = HwCtrlInit(param_1);
    if (iVar6 == 0) {
      iVar6 = rtmp_cfg_init(param_1,param_3);
      if (iVar6 == 1) {
        iVar6 = MeasureReqTabInit(param_1);
        if (iVar6 == 0) {
          iVar6 = TpcReqTabInit(param_1);
          if (iVar6 == 0) {
            InitTxSTypeTable(param_1);
            iVar6 = hc_get_hif_type(param_1[0x29e5e8]);
            if (iVar6 == 2) {
              InitTxSCommonCallBack(param_1);
            }
            qm_init(param_1);
            iVar6 = tm_init(param_1);
            if (iVar6 == 0) {
              iVar6 = WfInit(param_1);
              if (iVar6 == 0) {
                iVar6 = MlmeInit(param_1);
                if (iVar6 == 0) {
                  tr_ctl_init(param_1);
                  param_1[0x28e7e1] = param_1[0x28e7e1] | 2;
                  NICInitializeAsic(param_1);
                  tx_pwr_comp_init(param_1);
                  iVar6 = DebugLevel;
                  param_1[0x1e5449] = param_1[0x1e5449] & 0xffdfffff;
                  if (2 < iVar6) {
                    printk("NDIS_STATUS_MEDIA_DISCONNECT Event B!\n");
                  }
                  SCS_init(param_1);
                  RTMPIoctlRvRDebug_Init(param_1);
                  AsicSetMacTxRx(param_1,3,1);
                  mdvt_init(param_1);
                  cVar7 = *(char *)((int)param_1 + 0x286285);
                  if (cVar7 == '\x01') {
                    rtmp_ap_init(param_1);
                    cVar7 = *(char *)((int)param_1 + 0x286285);
                  }
                  if (cVar7 == '\0') {
                    rtmp_sta_init(param_1,param_1 + 0xdb6d6);
                  }
                  rtmp_ate_init(param_1);
                  chip_interrupt_enable(param_1);
                  RTMPEnableRxTx(param_1);
                  iVar6 = DebugLevel;
                  param_1[0x28e7e1] = param_1[0x28e7e1] | 0x10000000;
                  if (2 < iVar6) {
                    printk(&_LC14,uVar1,*(undefined1 *)(iVar3 + 0x49c),
                           *(undefined1 *)(iVar4 + 0x49c));
                  }
                  UAPSD_Init(param_1);
                  AutoChSelInit(param_1);
                  iVar3 = DebugLevel;
                  *(undefined1 *)(param_1 + 0x29f0c1) = 1;
                  *(undefined1 *)((int)param_1 + 0xa7c305) = 1;
                  *(undefined1 *)((int)param_1 + 0xa7c349) = 1;
                  if (0 < iVar3) {
                    printk("<==== mt_wifi_init, Status=%x\n",0);
                  }
                  TxBfModuleEnCtrl(param_1);
                  mt_Trigger_Sounding_Packet(param_1,1,0,4,0,0);
                  AsicTxBfHwEnStatusUpdate
                            (param_1,(char)param_1[0x1e5667],
                             ((uint)*(byte *)((int)param_1 + 0x794ccd) << 0x1d) >> 0x1f);
                  param_1[0x29e274] = 0;
                  *(undefined1 *)(param_1 + 0x29e275) = 1;
                  *(undefined1 *)((int)param_1 + 0x7959a6) = 0;
                  if ((char)param_1[0x1e5418] != '\0') {
                    MtCmdSetUseVhtRateFor2G(param_1);
                    return 1;
                  }
                  return 1;
                }
                if (-1 < DebugLevel) {
                  printk("MlmeInit failed, Status[=0x%08x]\n");
                }
                MlmeHalt(param_1);
                RTMP_AllTimerListRelease(param_1);
              }
              else if (-1 < DebugLevel) {
                printk("WfInit faild!!, ret=%d, cap=%p\n",iVar6,uVar5);
              }
              goto LAB_0013d520;
            }
          }
          else if (-1 < DebugLevel) {
            printk("TpcReqTabInit failed, Status[=0x%08x]\n");
          }
        }
        else if (-1 < DebugLevel) {
          printk("MeasureReqTabInit failed, Status[=0x%08x]\n");
        }
      }
      UserCfgExit(param_1);
    }
    HwCtrlExit(param_1);
  }
  param_1[0x28e7e1] = param_1[0x28e7e1] & 0xfffffffd;
  RtmpMgmtTaskExit(param_1);
LAB_0013d520:
  MeasureReqTabExit(param_1);
  TpcReqTabExit(param_1);
  UserCfgExit(param_1);
  HwCtrlExit(param_1);
  param_1[0x28e7e1] = param_1[0x28e7e1] & 0xfffffffd;
  RtmpMgmtTaskExit(param_1);
  if (DebugLevel < 0) {
    return 0;
  }
  printk("!!! mt_wifi_init  fail !!!\n");
  return 0;
}

