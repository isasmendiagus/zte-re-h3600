// module: mt7915.ko
// function: set_dfs_dedicated_rx_proc @ 0x22e728
// size: 808 bytes
//

undefined4 set_dfs_dedicated_rx_proc(int *param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint local_44;
  int local_40;
  undefined1 local_3c [3];
  undefined1 local_39;
  
  iVar5 = *param_1;
  iVar2 = hc_get_chip_ops(param_1[0x29e5e8]);
  iVar5 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(iVar5 + 0x3c),*(undefined4 *)(iVar5 + 0x38));
  local_44 = 0;
  local_40 = 0;
  if (iVar5 == 0) {
    if (DebugLevel < 0) {
      return 1;
    }
    printk("%s: wdev is Null\n","set_dfs_dedicated_rx_proc");
    return 1;
  }
  iVar3 = wlan_config_get_ch_band();
  HcGetBandByWdev(iVar5);
  os_zero_mem(local_3c,0x14);
  if (param_2 == (char *)0x0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: Arg is Null\n","set_dfs_dedicated_rx_proc");
    return 0;
  }
  iVar4 = sscanf(param_2,"%u:%u",&local_44,&local_40);
  if (iVar4 != 2) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk(
          "Format Error! Please enter in the following format\nch:bw(0: 20MHz, 1: 40MHz, 2: 80MHz)\n"
          );
    if (DebugLevel < 0) {
      return 0;
    }
    printk("Set 0:0 to disable 5th RX\n");
    return 0;
  }
  if ((local_44 == 0) && (local_40 == 0)) {
    if (*(code **)(iVar2 + 0x280) != (code *)0x0) {
      (**(code **)(iVar2 + 0x280))(param_1,8,0);
    }
    if (0 < DebugLevel) {
      printk("%s: disable dedicated rx\n","set_dfs_dedicated_rx_proc");
      return 1;
    }
    return 1;
  }
  if (1 < DebugLevel) {
    printk("%s: ch %d, bw = %d\n","set_dfs_dedicated_rx_proc",local_44);
  }
  cVar1 = (char)local_44;
  *(char *)(param_1 + 0x29e417) = cVar1;
  *(char *)(param_1 + 0x29e2b4) = (char)local_40;
  if (local_40 != 1) {
    if (local_40 == 2) {
      iVar5 = vht80_channel_group(param_1,local_44 & 0xff,iVar5);
      if (iVar5 == 0) {
        cVar1 = (char)local_44;
      }
      else {
        cVar1 = vht_cent_ch_freq(local_44 & 0xff,1,iVar3);
      }
    }
    goto LAB_0022e8b0;
  }
  iVar4 = N_ChannelGroupCheck(param_1,local_44 & 0xff,iVar5);
  if (iVar3 == 1 && iVar4 != 0) {
    if ((((local_44 & 0xffffffe7) != 0x24) && ((local_44 & 0xffffffe7) != 100)) &&
       ((local_44 & 0xfffffff7) != 0x95 && local_44 != 0x84)) goto LAB_0022e9b0;
    goto LAB_0022e9d8;
  }
  iVar4 = N_ChannelGroupCheck(param_1,local_44 & 0xff,iVar5);
  if (iVar3 != 0 || iVar4 == 0) {
    if (local_44 == 0xe) {
      cVar1 = '\r';
    }
    else {
      cVar1 = (char)local_44;
    }
    goto LAB_0022e8b0;
  }
  iVar5 = wlan_operate_get_ext_cha(iVar5);
  if (iVar5 == 1) {
    if (9 < local_44) goto LAB_0022e9b0;
  }
  else if (4 < local_44) {
LAB_0022e9b0:
    cVar1 = (char)local_44 + -2;
    goto LAB_0022e8b0;
  }
LAB_0022e9d8:
  cVar1 = (char)local_44 + '\x02';
LAB_0022e8b0:
  *(char *)((int)param_1 + 0xa7905d) = cVar1;
  if (*(code **)(iVar2 + 0x280) != (code *)0x0) {
    (**(code **)(iVar2 + 0x280))(param_1,6,0);
  }
  local_3c[0] = 1;
  local_39 = 0;
  mt_cmd_set_rdd_ipi_hist(param_1,local_3c);
  return 1;
}

