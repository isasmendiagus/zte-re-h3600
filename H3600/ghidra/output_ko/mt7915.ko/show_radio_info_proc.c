// module: mt7915.ko
// function: show_radio_info_proc @ 0xc33e4
// size: 920 bytes
//

undefined4 show_radio_info_proc(int param_1)

{
  ushort uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  char *pcVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  undefined4 local_68;
  undefined4 local_64;
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
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  local_68 = 0;
  local_64 = 0;
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
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  if ((0 < DebugLevel) && (printk("==========BBP radio information==========\n"), 0 < DebugLevel)) {
    pcVar6 = "Enable";
    if (*(char *)(param_1 + 0x79504d) == '\0') {
      pcVar6 = "Disable";
    }
    printk("DBDCEn\t: %s\n",pcVar6);
  }
  hc_show_radio_info(param_1);
  if (0 < DebugLevel) {
    printk("##########WDEV radio information##########\n");
  }
  piVar9 = (int *)(param_1 + 8);
  iVar8 = 0;
  do {
    piVar9 = piVar9 + 1;
    iVar7 = *piVar9;
    if (iVar7 != 0) {
      uVar2 = wlan_config_get_ext_cha(iVar7);
      uVar3 = wlan_operate_get_ext_cha(iVar7);
      uVar4 = wdev_type2str(*(undefined4 *)(iVar7 + 0x14));
      if (((0 < DebugLevel) && (printk("==========wdev(%d)==========\n",iVar8), 0 < DebugLevel)) &&
         (printk("type\t: %s\n",uVar4), 0 < DebugLevel)) {
        printk("fun_idx\t: %d\n",*(undefined1 *)(iVar7 + 0xe));
      }
      iVar5 = wmode_2_str(*(undefined2 *)(iVar7 + 0x18));
      if (iVar5 != 0) {
        if (0 < DebugLevel) {
          printk("wmode\t: %s\n",iVar5);
        }
        os_free_mem(iVar5);
      }
      if (DebugLevel < 1) {
        uVar1 = *(ushort *)(iVar7 + 0x18);
        if ((uVar1 & 0x18) != 0) goto LAB_000c3530;
LAB_000c3474:
        if (((uVar1 & 0x20) != 0) && (0 < DebugLevel)) {
          uVar2 = wlan_config_get_cen_ch_2(iVar7);
          uVar3 = wlan_operate_get_cen_ch_2(iVar7);
          printk("cen_ch2\t: (%d,%d)\n",uVar2,uVar3);
          if (0 < DebugLevel) {
            uVar2 = wlan_config_get_vht_bw(iVar7);
            uVar3 = wlan_operate_get_vht_bw(iVar7);
            printk("vht_bw\t: (%d,%d)\n",uVar2,uVar3);
          }
        }
      }
      else {
        uVar4 = wlan_operate_get_prim_ch(iVar7);
        printk("channel\t: %d\n",uVar4);
        if (DebugLevel < 1) {
          if ((*(ushort *)(iVar7 + 0x18) & 0x18) != 0) goto LAB_000c3530;
        }
        else {
          uVar4 = wlan_operate_get_ch_band(iVar7);
          printk("ch band\t: %d\n",uVar4);
          uVar1 = *(ushort *)(iVar7 + 0x18);
          if ((uVar1 & 0x18) == 0) goto LAB_000c3474;
          if (0 < DebugLevel) {
            uVar4 = wlan_operate_get_cen_ch_1(iVar7);
            printk("cen_ch1\t: %d\n",uVar4);
          }
LAB_000c3530:
          uVar4 = wlan_config_get_ht_bw(iVar7);
          bw_2_str(uVar4,&local_68);
          uVar4 = wlan_operate_get_ht_bw(iVar7);
          bw_2_str(uVar4,&local_48);
          if (0 < DebugLevel) {
            printk("ht_bw\t: (%s,%s)\n",&local_68,&local_48);
          }
          extcha_2_str(uVar2,&local_68);
          extcha_2_str(uVar3,&local_48);
          if (0 < DebugLevel) {
            printk("ext_ch\t: (%s,%s)\n",&local_68,&local_48);
            uVar1 = *(ushort *)(iVar7 + 0x18);
            goto LAB_000c3474;
          }
        }
      }
      uVar2 = wlan_operate_get_bw(iVar7);
      bw_2_str(uVar2,&local_68);
      if (0 < DebugLevel) {
        printk("bw\t: %s\n",&local_68);
      }
      hc_show_hdev_obj(iVar7);
    }
    iVar8 = iVar8 + 1;
    if (iVar8 == 0x68) {
      return 1;
    }
  } while( true );
}

