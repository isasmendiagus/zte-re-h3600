// module: mt7915.ko
// function: AdjustChannelRelatedValue @ 0x74f1c
// size: 388 bytes
//

void AdjustChannelRelatedValue
               (int param_1,undefined1 *param_2,undefined4 param_3,int param_4,byte param_5,
               byte param_6,int param_7)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined1 uVar6;
  undefined1 uVar7;
  undefined1 uVar8;
  undefined1 uStack_29;
  undefined1 local_28;
  undefined1 local_27;
  undefined1 local_26;
  undefined1 local_25;
  undefined1 local_24;
  
  iVar2 = GetStaCfgByWdev(param_1,param_7);
  if (iVar2 == 0) {
    printk(&_LC1,0x11eb);
    dump_stack();
    return;
  }
  *param_2 = 0;
  if ((*(uint *)(param_1 + 0xa39f84) & 0x4000) != 0) {
    return;
  }
  *(byte *)(param_7 + 0x1a) = param_5;
  if (param_5 < param_6 && param_4 == 1) {
    uVar6 = 1;
  }
  else {
    if (param_5 <= param_6 || param_4 != 1) {
      uVar6 = 0;
      uVar7 = 0;
      uVar8 = 0;
      goto LAB_00074fa8;
    }
    uVar6 = 3;
  }
  if (*(char *)(iVar2 + 0x40f2) == '\x01') {
    uVar8 = *(undefined1 *)(iVar2 + 0x40f3);
    uVar7 = 1;
  }
  else {
    uVar7 = 1;
    uVar8 = 0;
  }
LAB_00074fa8:
  os_zero_mem(&uStack_29,9);
  local_25 = *(undefined1 *)(param_7 + 0x1a);
  local_28 = uVar7;
  local_27 = uVar8;
  local_26 = uVar6;
  local_24 = wlan_operate_get_cen_ch_2(param_7);
  wlan_operate_set_phy(param_7,&uStack_29);
  if (0 < DebugLevel) {
    uVar6 = *(undefined1 *)(param_7 + 0x1a);
    cVar1 = "rtmp_read_dot11v_mbssid_cfg_from_file"[param_1 + 0x20];
    uVar3 = wlan_operate_get_cen_ch_1(param_7);
    uVar4 = wlan_operate_get_cen_ch_2(param_7);
    uVar5 = wlan_operate_get_bw(param_7);
    printk("%s(): RF-Ch=%d, CtrlCh=%d, CentralCh=%d, CentralCh2=%d, BW=%d\n",
           "AdjustChannelRelatedValue",cVar1,uVar6,uVar3,uVar4,uVar5);
  }
  return;
}

