// module: mt7915.ko
// function: set_ate_show_rx_stat @ 0x263de0
// size: 1684 bytes
//

undefined4 set_ate_show_rx_stat(int param_1,int param_2)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  uint uVar6;
  undefined4 *puVar7;
  int iVar8;
  uint local_64 [11];
  uint local_38;
  undefined2 uStack_36;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  local_64[7] = 0;
  local_64[8] = 0;
  local_64[9] = 0;
  local_64[10] = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_64[0] = 0;
  local_64[1] = 0;
  local_64[2] = 0;
  local_64[3] = 0;
  local_64[4] = 0;
  local_64[5] = 0;
  local_64[6] = 0;
  if (param_2 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: invalid argument (no argument)\n","set_ate_show_rx_stat");
    }
    return 0;
  }
  uVar1 = simple_strtol(param_2,0,10);
  uVar1 = uVar1 & 0xff;
  if (1 < uVar1) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: invalid band index(%d).\n","set_ate_show_rx_stat",uVar1);
    return 0;
  }
  if ((0 < DebugLevel) &&
     (printk("%s: band_idx: %d\n","set_ate_show_rx_stat",uVar1), 0 < DebugLevel)) {
    printk("rcpi: ");
  }
  iVar3 = uVar1 * 0x168;
  puVar5 = (undefined4 *)(param_1 + iVar3 + 0xa7bfd4);
  puVar7 = (undefined4 *)(param_1 + iVar3 + 0xa7bfe4);
  iVar4 = DebugLevel;
  do {
    if (0 < iVar4) {
      printk(&_LC162,*puVar5);
      iVar4 = DebugLevel;
    }
    puVar5 = puVar5 + 1;
  } while (puVar5 != puVar7);
  if ((0 < iVar4) && (printk(&_LC74), iVar4 = DebugLevel, 0 < DebugLevel)) {
    printk("rssi: ");
    iVar4 = DebugLevel;
  }
  puVar5 = (undefined4 *)(param_1 + iVar3 + 0xa7bf84);
  do {
    if (0 < iVar4) {
      printk(&_LC162,*puVar5);
      iVar4 = DebugLevel;
    }
    puVar5 = puVar5 + 1;
  } while (puVar5 != (undefined4 *)(param_1 + iVar3 + 0xa7bf94));
  if ((0 < iVar4) && (printk(&_LC74), iVar4 = DebugLevel, 0 < DebugLevel)) {
    printk("fagc rssi ib: ");
    iVar4 = DebugLevel;
  }
  puVar5 = (undefined4 *)(param_1 + iVar3 + 0xa7bff4);
  do {
    if (0 < iVar4) {
      printk(&_LC162,*puVar7);
      iVar4 = DebugLevel;
    }
    puVar7 = puVar7 + 1;
  } while (puVar7 != puVar5);
  if ((0 < iVar4) && (printk(&_LC74), iVar4 = DebugLevel, 0 < DebugLevel)) {
    printk("fagc rssi wb: ");
    iVar4 = DebugLevel;
  }
  do {
    if (0 < iVar4) {
      printk(&_LC162,*puVar5);
      iVar4 = DebugLevel;
    }
    puVar5 = puVar5 + 1;
  } while (puVar5 != (undefined4 *)(param_1 + iVar3 + 0xa7c004));
  if (0 < iVar4) {
    printk(&_LC74);
  }
  chip_get_rx_stat_band(param_1,uVar1,0,local_64 + 7);
  iVar8 = param_1 + uVar1 * 0x18;
  chip_get_rx_stat_comm(param_1,uVar1,0,local_64);
  uVar6 = local_64[7] & 0xffff;
  iVar3 = local_64[8] + *(int *)(iVar8 + 0xa7bf10);
  *(int *)(iVar8 + 0xa7bf10) = iVar3;
  *(uint *)(iVar8 + 0xa7bf18) = uVar6 + *(int *)(iVar8 + 0xa7bf18);
  *(uint *)(iVar8 + 0xa7bf1c) = (local_64[9] & 0xffff) + *(int *)(iVar8 + 0xa7bf1c);
  *(uint *)(iVar8 + 0xa7bf20) = (local_64[0] & 0xffff) + *(int *)(iVar8 + 0xa7bf20);
  iVar4 = (local_64[9] >> 0x10) + *(int *)(iVar8 + 0xa7bf14);
  *(int *)(iVar8 + 0xa7bf14) = iVar4;
  if (iVar3 == 0) {
    *(undefined4 *)(iVar8 + 0xa7bf24) = 0;
  }
  else {
    uVar2 = __aeabi_uidiv((iVar3 - iVar4) * 100);
    *(undefined4 *)(iVar8 + 0xa7bf24) = uVar2;
  }
  if (DebugLevel < 1) {
LAB_00264084:
    if (DebugLevel < 0) {
      return 1;
    }
  }
  else {
    printk("mac_rx_fcs_err_cnt: %d\n",uVar6);
    if (DebugLevel < 1) {
LAB_002641ec:
      if (DebugLevel < 1) {
LAB_0026426c:
        if (DebugLevel < 1) {
LAB_002642fc:
          if (DebugLevel < 1) goto LAB_00264084;
          iVar3 = uVar1 * 0x18 + param_1;
          printk("all_mac_rx_fcs_err_cnt: %d\n",*(undefined4 *)(iVar3 + 0xa7bf18));
          if (0 < DebugLevel) {
            printk("all_mac_rx_len_mismatch : %d\n",*(undefined4 *)(iVar3 + 0xa7bf1c));
            goto LAB_00264358;
          }
        }
        else {
          printk("phy_rx_tag_err_ofdm: %d\n",local_30._2_2_);
          if (0 < DebugLevel) {
            printk("phy_rx_mdrdy_cnt_cck: %d\n",local_2c & 0xffff);
            goto LAB_002642ac;
          }
        }
      }
      else {
        printk("phy_rx_pd_ofdm: %d\n",uStack_36);
        if (0 < DebugLevel) {
          printk("phy_rx_sig_err_cck: %d\n",local_34 & 0xffff);
          goto LAB_0026422c;
        }
      }
    }
    else {
      printk("mac_rx_len_mismatch: %d\n",local_64[9] & 0xffff);
      if (0 < DebugLevel) {
        printk("mac_rx_fifo_full: %d\n",local_64[0] & 0xffff);
        if (0 < DebugLevel) {
          printk("mac_rx_mdrdy_cnt: %d\n",local_64[8]);
          if (DebugLevel < 1) goto LAB_00264084;
          printk("phy_rx_pd_cck: %d\n",local_38 & 0xffff);
          goto LAB_002641ec;
        }
LAB_0026422c:
        if (DebugLevel < 1) {
LAB_002642ac:
          if (DebugLevel < 1) {
LAB_00264358:
            if (0 < DebugLevel) {
              printk("all_mac_rx_fifo_full : %d\n",
                     *(undefined4 *)(uVar1 * 0x18 + param_1 + 0xa7bf20));
            }
          }
          else {
            printk("phy_rx_mdrdy_cnt_ofdm: %d\n",local_2c._2_2_);
            if (0 < DebugLevel) {
              printk("all_mac_rx_mdrdy_cnt: %d\n",*(undefined4 *)(uVar1 * 0x18 + param_1 + 0xa7bf10)
                    );
              goto LAB_002642fc;
            }
          }
        }
        else {
          printk("phy_rx_sfd_err_cck: %d\n",local_34._2_2_);
          if (0 < DebugLevel) {
            printk("phy_rx_sig_err_ofdm: %d\n",local_30 & 0xffff);
            goto LAB_0026426c;
          }
        }
        goto LAB_00264084;
      }
    }
    if (DebugLevel != 0) {
      return 1;
    }
  }
  param_1 = uVar1 * 0x18 + param_1;
  printk("all_mac_rx_ok_cnt : %d\n",*(undefined4 *)(param_1 + 0xa7bf14));
  if (0 < DebugLevel) {
    printk("all_per : %d\n",*(undefined4 *)(param_1 + 0xa7bf24));
  }
  return 1;
}

