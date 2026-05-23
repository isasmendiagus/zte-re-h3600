// module: mt7915.ko
// function: sta_cntl_connect_proc @ 0x74178
// size: 2420 bytes
//

void sta_cntl_connect_proc(int param_1,undefined4 *param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  char cVar5;
  int iVar6;
  uint uVar7;
  uint __n;
  void *__dest;
  void *__dest_00;
  undefined4 uVar8;
  int iVar9;
  size_t local_78;
  undefined1 auStack_74 [32];
  undefined4 local_54;
  uint local_50;
  undefined2 local_4c;
  byte local_4a;
  undefined1 auStack_49 [37];
  
  switch(*param_2) {
  case 0:
    iVar2 = *(int *)(param_1 + 8);
    cVar5 = *(char *)(param_2 + 1);
    puVar4 = (undefined4 *)get_scan_tab_by_wdev(iVar2,param_1);
    iVar6 = GetStaCfgByWdev(iVar2,param_1);
    if (iVar6 == 0) {
      printk(&_LC1,0x20e);
      dump_stack();
      return;
    }
    os_zero_mem(&local_78,0x24);
    if (cVar5 != '$') {
      if (DebugLevel < 1) {
        return;
      }
      printk("%s():: data_len %d != sizeof(NDIS_802_11_SSID)\n","sta_cntl_connect_by_ssid",cVar5);
      return;
    }
    __dest = (void *)(iVar6 + 0x4119);
    os_move_mem(&local_78,(void *)((int)param_2 + 5),0x24);
    os_zero_mem(__dest,0x20);
    os_move_mem(__dest,auStack_74,local_78);
    cVar5 = *(char *)(iVar6 + 0x4060);
    *(char *)(iVar6 + 0x4139) = (char)local_78;
    if (cVar5 == '\x01') {
      os_zero_mem(iVar6 + 0x413a,6);
      cVar5 = *(char *)(iVar6 + 0x4060);
    }
    *(char *)(iVar6 + 0x4118) = cVar5;
    *(undefined1 *)(iVar6 + 0x213172) = 0;
    os_zero_mem((void *)(iVar6 + 0x213211),0x20);
    __dest_00 = (void *)(iVar6 + 0x212406);
    os_move_mem((void *)(iVar6 + 0x213211),auStack_74,local_78);
    *(char *)(iVar6 + 0x213210) = (char)local_78;
    *(undefined1 *)(iVar6 + 0x213231) = *(undefined1 *)(iVar6 + 0x4060);
    os_zero_mem(__dest_00,0x20);
    os_move_mem(__dest_00,auStack_74,local_78);
    *(char *)(iVar6 + 0x212426) = (char)local_78;
    BssTableSsidSort(iVar2,iVar6,iVar6 + 0x4228,__dest,*(undefined1 *)(iVar6 + 0x4139));
    if (DebugLevel < 3) {
      if (*(char *)(iVar6 + 0x4139) == ' ') {
LAB_000747b8:
        hex_dump("\nSSID",__dest,0x20);
      }
    }
    else {
      printk("%s():CNTL - %d BSS of %d BSS match the desire ","sta_cntl_connect_by_ssid",
             *(undefined4 *)(iVar6 + 0x4228),*puVar4);
      if (*(char *)(iVar6 + 0x4139) == ' ') goto LAB_000747b8;
      if (2 < DebugLevel) {
        printk("(%d)SSID - %s\n",*(char *)(iVar6 + 0x4139),__dest);
      }
    }
    if (((((*(uint *)(iVar6 + 0x212464) & 0x81) == 0x81) &&
         ((uint)*(byte *)(iVar6 + 0x42c4) == (uint)*(byte *)(iVar6 + 0x212426))) &&
        (iVar3 = memcmp(__dest_00,(void *)(iVar6 + 0x42c5),(uint)*(byte *)(iVar6 + 0x42c4)),
        iVar3 == 0)) &&
       (iVar3 = memcmp((void *)(iVar6 + 0x212428),(void *)(iVar6 + 0x4236),6), iVar3 == 0)) {
      if (((*(uint *)(param_1 + 0x2c) & 0x12cf8) == 0) || (*(char *)(param_1 + 0x888) != '\x02')) {
        if (*(char *)(iVar6 + 0x212468) != '\x01') {
          if (2 < DebugLevel) {
            printk("%s():CNTL - already with this BSSID. ignore this SET_SSID request\n",
                   "sta_cntl_connect_by_ssid");
          }
          if ((*(uint *)(iVar6 + 0x212464) & 1) != 0) {
            RTMP_IndicateMediaState(iVar2,1);
            *(undefined4 *)(iVar2 + 0xa39fa4) = 0;
          }
          cntl_fsm_state_transition(param_1,0,"sta_cntl_connect_by_ssid");
          goto LAB_000745e4;
        }
        if (2 < DebugLevel) {
          printk("%s():CNTL - disassociate with current AP Because config changed...\n",
                 "sta_cntl_connect_by_ssid");
        }
      }
      else {
LAB_000745d0:
        if (2 < DebugLevel) {
          printk("%s():CNTL - disassociate with current AP...\n","sta_cntl_connect_by_ssid");
        }
      }
      FUN_000707c0(iVar6);
    }
    else {
      if ((*(uint *)(iVar6 + 0x212464) & 1) != 0) {
        if (((uint)*(byte *)(iVar6 + 0x4139) != (uint)*(byte *)(iVar6 + 0x212426)) ||
           (iVar2 = memcmp(__dest_00,__dest,(uint)*(byte *)(iVar6 + 0x4139)), iVar2 != 0)) {
          BN_mod_lshift1[iVar6] = (code)0x1;
        }
        goto LAB_000745d0;
      }
      if ((*(int *)(iVar6 + 0x4228) == 0) && (*(char *)(iVar6 + 0x213171) == '\x01')) {
        if (*(char *)(iVar6 + 0x4118) == '\x01') {
          if ((*(uint *)(iVar2 + 0xa39f84) & 0x4000) == 0) goto LAB_0007485c;
        }
        else if ((*(char *)(iVar6 + 0x4118) == '\0') && (*(char *)(param_1 + 0xbc9) == '\0')) {
LAB_0007485c:
          iVar3 = MlmeValidateSSID(__dest,*(undefined1 *)(iVar6 + 0x4139));
          if (iVar3 == 1) {
            if (2 < DebugLevel) {
              printk("%s():CNTL - No matching BSS, start a new scan\n","sta_cntl_connect_by_ssid");
            }
            ScanParmFill(iVar2,&local_54,__dest,*(undefined1 *)(iVar6 + 0x4139),2,0);
            cntl_scan_request(param_1,&local_54);
            goto LAB_000745e4;
          }
        }
      }
      if ((*(byte *)(iVar2 + 0x794c44) & 0x7f) == 0x21) {
        if (*(char *)(*(int *)(iVar6 + 0x211e40) * 0xaf4 + iVar6 + 0x423c) == '\x0e') {
          if (*(char *)(iVar2 + 0x794c49) == '\0') {
            *(char *)(iVar2 + 0x794c49) = (char)*(undefined2 *)(param_1 + 0x18);
            RTMPSetPhyMode(iVar2,param_1,2);
          }
        }
        else if (*(char *)(iVar2 + 0x794c49) != '\0') {
          RTMPSetPhyMode(iVar2,param_1);
          *(undefined1 *)(iVar2 + 0x794c49) = 0;
        }
      }
      *(undefined4 *)(iVar6 + 0x211e40) = 0;
      IterateOnBssTab(iVar2,param_1);
    }
LAB_000745e4:
    os_zero_mem((void *)(iVar6 + 0x4140),0x20);
    os_move_mem((void *)(iVar6 + 0x4140),__dest,(uint)*(byte *)(iVar6 + 0x4139));
    *(undefined1 *)(iVar6 + 0x4160) = *(undefined1 *)(iVar6 + 0x4139);
    break;
  case 1:
    FUN_00070850(param_1,(int)param_2 + 5);
    break;
  case 2:
    iVar2 = *(int *)(param_1 + 8);
    uVar7 = (uint)*(byte *)(param_1 + 0xe);
    iVar6 = GetStaCfgByWdev(iVar2,param_1);
    if (iVar6 == 0) {
      printk(&_LC7,0x183);
      dump_stack();
      return;
    }
    if (2 < DebugLevel) {
      printk("(%s) Start Probe Req.\n","sta_cntl_connect_by_cfg");
    }
    if (1 < uVar7) {
      return;
    }
    iVar3 = scan_in_run_state(iVar2,param_1);
    if (iVar3 == 1) {
      return;
    }
    __memzero(&local_54,0x2c);
    iVar3 = memcmp((void *)(iVar6 + 0x213303),&ZERO_MAC_ADDR,6);
    if (iVar3 != 0) {
      local_50 = *(uint *)(iVar6 + 0x213303);
      local_4c = *(undefined2 *)(iVar6 + 0x213307);
    }
    if ((*(int *)(iVar6 + 0x12e4) == 0) || (*(char *)(iVar6 + 0x3cc8) != '\x01')) {
      bVar1 = *(byte *)(iVar6 + 0x213302);
      if (bVar1 == 0) goto LAB_00074320;
      local_4a = bVar1;
      memmove(auStack_49,(void *)(iVar6 + 0x2132e2),(uint)bVar1);
    }
    else {
      iVar3 = get_scan_tab_by_wdev(iVar2,param_1);
      __memzero(auStack_49,0x20);
      iVar9 = iVar2 + uVar7 * 0x2137b0;
      local_4a = (&DAT_0036ee64)[iVar9];
      __n = (uint)local_4a;
      memmove(auStack_49,(void *)(iVar9 + 0x36ee68),__n);
      if (*(int *)(iVar6 + 0x12e8) == 1) {
        iVar9 = BssSsidTableSearchBySSID(iVar3,auStack_49,__n);
        if (iVar9 == -1) {
          ApSiteSurvey_by_wdev(iVar2,0,3,0,param_1);
          return;
        }
        uVar8 = *(undefined4 *)(iVar6 + 0x12e4);
        cVar5 = *(char *)(iVar9 * 0xaf4 + iVar3 + 0x14);
        if (*(char *)(param_1 + 0x1a) != cVar5) {
          rtmp_set_channel(iVar2,param_1,cVar5);
          *(char *)(param_1 + 0x1a) = cVar5;
          *(undefined4 *)(iVar6 + 0x12e4) = uVar8;
          *(undefined4 *)(iVar6 + 0x12f4) = 2;
          *(undefined4 *)(iVar6 + 0x12f0) = 0x27;
          *(undefined4 *)(iVar6 + 0x12e8) = 1;
          *(undefined1 *)(iVar6 + 0x3cc8) = 1;
          return;
        }
LAB_00074320:
        __n = (uint)local_4a;
      }
      if ((__n == 0) && (iVar6 = memcmp(&local_50,&ZERO_MAC_ADDR,6), iVar6 == 0)) {
        if (DebugLevel < 2) {
          return;
        }
        printk("(%s) SsidLen=0 & zero mac bssid, return\n","sta_cntl_connect_by_cfg");
        return;
      }
    }
    if (2 < DebugLevel) {
      printk("(%s) Probe Ssid=%s, Bssid=%02x:%02x:%02x:%02x:%02x:%02x\n","sta_cntl_connect_by_cfg",
             auStack_49,local_50 & 0xff,local_50 >> 8 & 0xff,local_50 >> 0x10 & 0xff,
             local_50 >> 0x18,(undefined1)local_4c,local_4c._1_1_);
    }
    cntl_fsm_state_transition(param_1,1,"sta_cntl_connect_by_cfg");
    local_54 = 0xffffffff;
    MlmeEnqueueWithWdev(iVar2,4,0,0x2c,&local_54,uVar7,param_1);
    break;
  case 3:
    iVar6 = *(int *)(param_1 + 8);
    if (iVar6 == 0) {
      printk(&_LC5,0x409);
      dump_stack();
    }
    iVar2 = GetStaCfgByWdev(iVar6,param_1);
    if (iVar2 != 0) {
      if (2 < DebugLevel) {
        printk("CNTL - Roaming in MlmeAux.RoamTab...\n");
      }
      wlan_operate_set_ht_bw(param_1,0,0);
      memcpy((void *)(iVar2 + 0x4228),(void *)(iVar2 + 0x162a38),0xaf408);
      *(undefined4 *)(iVar2 + 0x4228) = *(undefined4 *)(iVar2 + 0x162a38);
      BssTableSortByRssi((void *)(iVar2 + 0x4228),0);
      *(undefined4 *)(iVar2 + 0x211e40) = 0;
      IterateOnBssTab(iVar6,param_1);
      return;
    }
    printk(&_LC1,0x40a);
    dump_stack();
    break;
  default:
    if (-1 < DebugLevel) {
      printk("%s: Unknow conn_type(=%d)\n","sta_cntl_connect_proc");
    }
  }
  return;
}

