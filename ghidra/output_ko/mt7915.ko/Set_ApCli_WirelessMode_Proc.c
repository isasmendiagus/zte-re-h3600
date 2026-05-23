// module: mt7915.ko
// function: Set_ApCli_WirelessMode_Proc @ 0x305d0
// size: 968 bytes
//

undefined4 Set_ApCli_WirelessMode_Proc(int *param_1,undefined4 param_2)

{
  undefined1 uVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  undefined2 local_34;
  
  iVar7 = *param_1;
  uVar1 = os_str_tol(param_2,0,10);
  if (*(int *)(iVar7 + 0x38) == 0x400) {
    iVar8 = *(int *)(iVar7 + 0x3c);
    uVar2 = cfgmode_2_wmode(uVar1);
    iVar3 = RtmpOSNetDevIsUp(param_1[*(int *)(iVar7 + 0x3c) * 0x84dec + 0xdb6d6]);
    if (iVar3 == 1) {
      if ((uVar2 & 0xb1) == 0) {
        uVar4 = 1;
      }
      else {
        uVar4 = 2;
      }
      uVar1 = HcGetChannelByRf(param_1,uVar4);
      piVar9 = param_1 + iVar8 * 0x84dec + 0xdb6d6;
      *(undefined1 *)((int)param_1 + iVar8 * 0x2137b0 + 0x36db72) = uVar1;
      iVar3 = wdev_do_linkdown(piVar9);
      if ((iVar3 != 1) && (-1 < DebugLevel)) {
        printk("(%s) linkdown fail!\n","Set_ApCli_WirelessMode_Proc");
      }
      os_msec_delay(100);
      iVar3 = wdev_do_close(piVar9);
      if ((iVar3 != 1) && (2 < DebugLevel)) {
        printk("%s() close fail!!!\n","Set_ApCli_WirelessMode_Proc");
      }
      os_msec_delay(100);
      local_34 = (undefined2)uVar2;
      *(undefined2 *)(param_1 + iVar8 * 0x84dec + 0xdb6dc) = local_34;
      HcAcquireRadioForWdev(param_1,piVar9);
      uVar4 = HcGetBandByWdev(piVar9);
      uVar4 = hc_get_channel_ctrl(param_1[0x29e5e8],uVar4);
      hc_set_ChCtrlChListStat(uVar4,0);
      BuildChannelList(param_1,piVar9);
      RTMPSetPhyMode(param_1,piVar9,uVar2);
      RTMPUpdateRateInfo((short)param_1[iVar8 * 0x84dec + 0xdb6dc],
                         &DAT_0036e636 + (int)(param_1 + iVar8 * 0x84dec));
      if (*(char *)((int)param_1 + 0x79504d) == '\x01') {
        if (*(byte *)((int)param_1 + 0x2b7242) != 0) {
          if ((short)param_1[0xadc98] == (short)param_1[iVar8 * 0x84dec + 0xdb6dc]) {
            uVar5 = 0;
          }
          else {
            uVar5 = 0;
            piVar6 = param_1 + 0xaf2a5;
            do {
              uVar5 = uVar5 + 1;
              if (uVar5 == *(byte *)((int)param_1 + 0x2b7242)) goto LAB_000307d4;
              iVar3 = *piVar6;
              piVar6 = piVar6 + 0x160d;
            } while ((short)iVar3 != (short)param_1[iVar8 * 0x84dec + 0xdb6dc]);
          }
          update_att_from_wdev(piVar9,param_1 + uVar5 * 0x160d + 0xadc92);
        }
      }
      else {
        *(short *)(param_1 + iVar8 * 0x84dec + 0xdb6dc) = (short)param_1[0xadc98];
        update_att_from_wdev(piVar9,param_1 + 0xadc92);
      }
LAB_000307d4:
      os_msec_delay(100);
      if (param_1[iVar8 * 0x84dec + 0xdb6e1] == 0) {
        param_1[iVar8 * 0x84dec + 0xdb6e1] = 1;
      }
      if (param_1[iVar8 * 0x84dec + 0xdb733] == 0) {
        param_1[iVar8 * 0x84dec + 0xdb733] = 1;
        param_1[iVar8 * 0x84dec + 0xdb76b] = param_1[iVar8 * 0x84dec + 0xdb76b] | 1;
      }
      iVar3 = wdev_do_open(piVar9);
      if ((iVar3 != 1) && (2 < DebugLevel)) {
        printk("%s() open fail!!!\n","Set_ApCli_WirelessMode_Proc");
      }
      os_msec_delay(100);
      if ((2 < DebugLevel) &&
         (printk("I/F(apcli%d) Set_ApCli_WirelessMode_Proc = %d\n",*(undefined4 *)(iVar7 + 0x3c),
                 uVar2), 2 < DebugLevel)) {
        printk("SupRate[0]=%x\n",*(undefined1 *)((int)param_1 + iVar8 * 0x2137b0 + 0x36e637));
      }
      return 1;
    }
  }
  return 0;
}

