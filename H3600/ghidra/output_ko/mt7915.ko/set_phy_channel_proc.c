// module: mt7915.ko
// function: set_phy_channel_proc @ 0xd8718
// size: 584 bytes
//

undefined4 set_phy_channel_proc(int *param_1,char *param_2)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined1 local_33;
  undefined1 local_32;
  undefined1 local_31;
  undefined1 local_30;
  undefined1 local_2f;
  undefined1 local_2e;
  undefined1 local_2d;
  undefined1 local_2c;
  undefined1 local_2b;
  undefined1 local_2a;
  undefined1 local_29;
  
  iVar4 = *param_1;
  uVar1 = *(undefined1 *)(iVar4 + 0x3c);
  iVar2 = get_wdev_by_ioctl_idx_and_iftype(param_1,uVar1,*(undefined4 *)(iVar4 + 0x38));
  local_60 = 0;
  local_5c = 0;
  local_58 = 0;
  local_54 = 0;
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  if (iVar2 == 0) {
    uVar3 = 0;
    if (-1 < DebugLevel) {
      printk("%s: wdev == NULL! if_type %d, if_idx = %d\n","set_phy_channel_proc",
             *(undefined4 *)(iVar4 + 0x38),uVar1);
    }
  }
  else {
    uVar3 = HcGetBandByWdev();
    if (-1 < DebugLevel) {
      printk("%s(): band_idx = %d\n","set_phy_channel_proc",uVar3);
    }
    os_zero_mem(&local_33,0xb);
    if (param_2 != (char *)0x0) {
      iVar2 = sscanf(param_2,"%u-%u-%u-%u-%u-%u-%u-%u-%u-%u-%u",&local_60,&local_5c,&local_58,
                     &local_54,&local_50,&local_4c,&local_48,&local_44,&local_40,&local_3c,&local_38
                    );
      if (iVar2 == 0xb) {
        if (-1 < DebugLevel) {
          printk("%s():ch_band = %d\n ht_bw = %d\n vht_bw = %d\nbw = %d\n ext_cha = %d\n prim_ch = %d\n cen_ch_1 = %d\ncen_ch_2 = %d\n rx_stream = %d\n ap_bw = %d\n ap_cen_ch = %d\n"
                 ,"set_phy_channel_proc",local_60,local_5c,local_58,local_54,local_50,local_4c,
                 local_48,local_44,local_40,local_3c,local_38);
        }
        local_2a = (undefined1)local_3c;
        local_33 = (undefined1)local_60;
        local_32 = (undefined1)local_5c;
        local_31 = (undefined1)local_58;
        local_30 = (undefined1)local_54;
        local_2f = (undefined1)local_50;
        local_2e = (undefined1)local_4c;
        local_2d = (undefined1)local_48;
        local_2c = (undefined1)local_44;
        local_2b = (undefined1)local_40;
        local_29 = (undefined1)local_38;
        AsicSwitchChannel(param_1,uVar3,&local_33,0);
        return 1;
      }
      if (-1 < DebugLevel) {
        printk(
              "Format Error! Please enter in the following format\nch_band-ht_bw-vht_bw-bw-ext_cha-prim_ch-cen_ch_1-cen_ch_2-rx_stream-ap_bw-ap_cen_ch\n"
              );
      }
    }
    uVar3 = 1;
  }
  return uVar3;
}

