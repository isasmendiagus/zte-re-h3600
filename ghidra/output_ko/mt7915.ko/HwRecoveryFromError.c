// module: mt7915.ko
// function: HwRecoveryFromError @ 0xafa20
// size: 1188 bytes
//

undefined4 HwRecoveryFromError(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  bool bVar5;
  undefined1 auStack_34 [4];
  undefined4 local_30;
  undefined4 local_2c [2];
  
  local_2c[0] = hc_get_ct_cb(*(undefined4 *)(param_1 + 0xa797a0));
  if (param_1 == 0) {
    return 2;
  }
  if (((*(uint *)(param_1 + 0xa3ac14) & 1) != 0) ||
     ((*(int *)(param_1 + 0xa77bb4) == 1 &&
      ((*(uint *)(*(int *)(param_1 + 0xa77bb8) + 0x4e0) & 1) != 0)))) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("Ser():The driver is in ATE mode now\n");
    return 0;
  }
  iVar4 = param_1 + 0xa7bf04;
  uVar3 = *(uint *)(param_1 + 0x285d30);
  uVar1 = ErrRecoveryCurStat(iVar4);
  if (-1 < DebugLevel) {
    printk("Ser                       ,::E  R  , stat=0x%08X\n",uVar1);
  }
  mt_wlan_hook_call(10,param_1,iVar4);
  switch(uVar1) {
  case 0:
  case 5:
    if ((uVar3 & 4) != 0) {
      iVar4 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
      os_zero_mem(param_1 + 0x285d38,0x20);
      AsicGetTsfTime(param_1,auStack_34,&local_30,0);
      *(undefined4 *)(param_1 + 0x285d38) = local_30;
      *(undefined4 *)(param_1 + 0xa7bf04) = 3;
      chip_trigger_int_to_mcu(param_1,1);
      *(undefined1 *)(iVar4 + 0x90) = 1;
      RtmpusecDelay(100000);
      *(undefined1 *)(iVar4 + 0x90) = 0;
      HwRecoveryFromError(param_1);
      AsicGetTsfTime(param_1,auStack_34,&local_30,0);
      *(undefined4 *)(param_1 + 0x285d3c) = local_30;
      goto LAB_000afbc4;
    }
    break;
  case 1:
    if ((uVar3 & 8) != 0) {
      uVar3 = *(uint *)(param_1 + 0xa39f84);
      AsicGetTsfTime(param_1,auStack_34,&local_30,0);
      *(undefined4 *)(param_1 + 0x285d40) = local_30;
      *(uint *)(param_1 + 0xa39f84) = *(uint *)(param_1 + 0xa39f84) & 0xeeffffff;
      tm_exit(param_1);
      qm_exit(param_1);
      hif_reset_task_group(*(undefined4 *)(param_1 + 0xa797a0));
      hif_reset_txrx_mem(*(undefined4 *)(param_1 + 0xa797a0));
      token_deinit(local_2c);
      WfHifInit(param_1);
      qm_init(param_1);
      tm_init(param_1);
      *(uint *)(param_1 + 0xa39f84) = uVar3 & 0x11000000 | *(uint *)(param_1 + 0xa39f84);
      chip_interrupt_enable(param_1);
      hif_dma_enable(*(undefined4 *)(param_1 + 0xa797a0));
      if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7615 ||
          (*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7622) {
        hif_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x4224,0);
      }
      *(undefined4 *)(param_1 + 0xa7bf04) = 2;
      chip_trigger_int_to_mcu(param_1,2);
      AsicGetTsfTime(param_1,auStack_34,&local_30,0);
      *(undefined4 *)(param_1 + 0x285d44) = local_30;
      goto LAB_000afbc4;
    }
    break;
  case 2:
    if ((uVar3 & 0x10) != 0) {
      AsicGetTsfTime(param_1,auStack_34,&local_30,0);
      *(undefined4 *)(param_1 + 0x285d48) = local_30;
      *(undefined4 *)(param_1 + 0xa7bf04) = 4;
      chip_trigger_int_to_mcu(param_1,8);
      *(undefined4 *)(param_1 + 0x285d4c) = local_30;
      goto LAB_000afbc4;
    }
    break;
  case 3:
    *(undefined4 *)(param_1 + 0xa7bf04) = 1;
    goto LAB_000afbc4;
  case 4:
    if ((uVar3 & 0x20) != 0) {
      AsicGetTsfTime(param_1,auStack_34,&local_30,0);
      *(undefined4 *)(param_1 + 0x285d50) = local_30;
      *(undefined4 *)(param_1 + 0xa7bf04) = 0;
      AsicGetTsfTime(param_1,auStack_34,&local_30,0);
      *(undefined4 *)(param_1 + 0x285d54) = local_30;
      SerTimeLogDump(param_1);
      if ((*(uint *)(param_1 + 0x286280) & 0xfffffffb) == 1) {
        hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
        pci_rx_all();
      }
      ba_refresh_bar_all(param_1);
      uVar2 = get_default_wdev(param_1);
      UpdateBeaconHandler(param_1,uVar2,3);
      goto LAB_000afbc4;
    }
    if ((uVar3 & 4) != 0) {
      AsicGetTsfTime(param_1,auStack_34);
      bVar5 = -1 < DebugLevel;
      *(undefined4 *)(param_1 + 0x285d50) = local_30;
      if (bVar5) {
        uVar2 = ErrRecoveryCurStat(iVar4);
        printk("!!! ERROR SER re-entry  CurStat=%u Event=%x!!!\n",uVar2,uVar3);
      }
      AsicGetTsfTime(param_1,auStack_34,&local_30,0);
      *(undefined4 *)(param_1 + 0x285d54) = local_30;
      SerTimeLogDump(param_1);
      *(undefined4 *)(param_1 + 0xa7bf04) = 5;
      HwRecoveryFromError(param_1);
      goto LAB_000afbc4;
    }
  }
  if (DebugLevel < 0) {
    return 0;
  }
  uVar2 = ErrRecoveryCurStat(iVar4);
  printk("!!! SER CurStat=%u Event=%x!!!\n",uVar2,uVar3);
LAB_000afbc4:
  if (DebugLevel < 0) {
    return 0;
  }
  printk("\tEND of stat(%d)\n",uVar1);
  return 0;
}

