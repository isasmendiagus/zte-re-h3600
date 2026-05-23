// module: mt7915.ko
// function: WPABuildPairMsg4 @ 0x11f6ac
// size: 1460 bytes
//

void WPABuildPairMsg4(int param_1,uint *param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined1 uStack_c5;
  int local_c4;
  uint local_be;
  undefined2 local_ba;
  undefined4 local_b8;
  undefined2 local_b4;
  undefined2 local_b2;
  undefined4 local_b0;
  undefined4 local_ac;
  uint local_a8;
  undefined2 local_a4;
  undefined1 local_a2;
  undefined1 local_a1;
  undefined1 auStack_a0 [114];
  undefined1 auStack_2e [10];
  
  memset(&local_b0,0,0x88);
  if (param_3 == (int *)0x0) {
    if (-1 < DebugLevel) {
      printk("!!!%s : pEntry is NULL!!!\n","WPABuildPairMsg4");
    }
  }
  else {
    os_alloc_mem(0,&local_c4,0x5dc);
    iVar1 = local_c4;
    if (local_c4 == 0) {
      if (-1 < DebugLevel) {
        printk("!!!%s : no memory!!!\n","WPABuildPairMsg4");
      }
    }
    else {
      __memzero(local_c4,0x5dc);
      WPAConstructEapolMsg(param_3,4,param_2,param_2,iVar1);
      *(undefined1 *)(param_2 + 0xe6) = 10;
      os_zero_mem(&local_b0,0x88);
      local_a4 = (undefined2)param_3[0x38];
      local_a2 = (undefined1)param_3[0x39];
      local_a8 = param_2[0x52];
      local_a1 = (undefined1)param_2[0x53];
      local_ac = 2;
      local_b0 = 0;
      os_move_mem(auStack_2e,param_3 + 0x3b,6);
      if (((*param_2 & 0x30000) == 0) && ((char)param_2[0xa1] != '\x02')) {
        os_move_mem(auStack_a0,(void *)((int)param_2 + 0x1ee),0x20);
      }
      else {
        os_move_mem(auStack_a0,(void *)((int)param_2 + 0x206),0x20);
      }
      uVar6 = (uint)*(ushort *)(param_3 + 0x38);
      *(undefined1 *)(param_1 + uVar6 * 0x620 + 0x2f762) = 1;
      param_3[0x2b7] = 0;
      if (*(char *)((int)param_2 + 0x3d9) == '\x01') {
        if ((short)param_3[0x38] == *(short *)(&DAT_002963c2 + param_1)) {
          if (2 < DebugLevel) {
            printk("\n%s: Clear Wcid = %d FragBuffer !!!!!\n","WPABuildPairMsg4");
          }
          *(undefined4 *)(&DAT_002963b4 + param_1) = 0;
          *(undefined2 *)(&DAT_002963b8 + param_1) = 0;
          *(undefined4 *)(&DAT_002963bc + param_1) = 0;
          (&DAT_002963c5)[param_1] = 0;
          *(undefined2 *)(&DAT_002963ba + param_1) = 0;
          *(undefined2 *)(&DAT_002963c2 + param_1) = 0;
          *(undefined4 *)(&DAT_002963c8 + param_1) = 0;
          *(undefined4 *)(&DAT_002963cc + param_1) = 0;
          (&DAT_002963c4)[param_1] = 0;
        }
        WifiSysUpdatePortSecur(param_1,param_3,0);
        WPAInstallKey(param_1,&local_b0,0,1);
        *(undefined1 *)((int)param_2 + 0x3d9) = 0;
        *(undefined1 *)(param_3 + 0x519) = 1;
      }
      else if (-1 < DebugLevel) {
        printk("!!!%s : the M3 reinstall attack, skip install key\n","WPABuildPairMsg4");
      }
      local_be = param_2[0xc9];
      local_ba = (undefined2)param_2[0xca];
      local_b8 = *(undefined4 *)((int)param_2 + 0x32a);
      local_b4 = *(undefined2 *)((int)param_2 + 0x32e);
      local_b2 = EAPOL;
      if (*(char *)((int)param_2 + 0x595) == '\0') {
        uVar4 = 1;
      }
      else {
        uVar4 = 0;
        if (*(char *)(param_1 + uVar6 * 0x620 + 0x2f762) != '\x01') {
          uVar4 = 1;
        }
      }
      RTMPToWirelessSta(param_1,param_3,&local_be,0xe,iVar1,
                        CONCAT11(*(undefined1 *)(iVar1 + 2),*(undefined1 *)(iVar1 + 3)) + 4,uVar4);
      os_free_mem(local_c4);
      iVar1 = DebugLevel;
      if ((*(char *)(param_1 + 0x286285) == '\x01') && (*param_3 == 2)) {
        uVar3 = (uint)*(byte *)(param_3 + 0x39);
        iVar2 = param_1 + uVar3 * 0x2137b0;
        if ((&DAT_00580ee8)[iVar2] == '\x01') {
          (&DAT_00580ee8)[iVar2] = 0;
          if (iVar1 < 3) {
            uVar3 = (uint)*(byte *)(param_3 + 0x39);
          }
          else {
            printk("Apcli auto connected:WPABuildPairMsg4(),pAd->ApCfg.ApCliAutoConnectRunning[%d]=%d\n"
                   ,0,0);
            uVar3 = (uint)*(byte *)(param_3 + 0x39);
          }
        }
        if (((param_1 + uVar6 * 0x620 != -0x2f6a0 && uVar3 < 2) &&
            (*(char *)(param_1 + uVar6 * 0x620 + 0x2f762) == '\x01')) && ((*param_2 & 0x18) == 0)) {
          MWDSAPCliPeerEnable(param_1,&DAT_0036db58 + uVar3 * 0x2137b0 + param_1,param_3);
        }
      }
      iVar1 = GetStaCfgByWdev(param_1,param_3[2]);
      iVar2 = GetAssociatedAPByWdev(param_1,param_3[2]);
      *(undefined1 *)(param_3[2] + 0x888) = 1;
      RTMP_IndicateMediaState(param_1,1);
      _raw_spin_lock_bh(param_1 + 0x285958);
      if (iVar2 != 0) {
        *(undefined1 *)(param_1 + (uint)*(ushort *)(iVar2 + 0xe0) * 0x620 + 0x2f762) =
             *(undefined1 *)(param_3[2] + 0x888);
        *(undefined4 *)(iVar2 + 0xadc) = 0;
      }
      _raw_spin_unlock_bh(param_1 + 0x285958);
      RTMPCancelTimer(iVar1 + 0x212470,&uStack_c5);
      if (2 < DebugLevel) {
        printk("===> WifiSysUpdatePortSecur called by (%s), wcid=%d, PortSecured=%d\n",
               "WPABuildPairMsg4",(short)param_3[0x38],2);
      }
      if ((*param_2 & 0x2000) != 0) {
        set_sae_instance_removable
                  ("pci_sw_int_handler" + param_1,(undefined4 *)((int)param_2 + 0x32a),
                   param_2 + 0xc9);
      }
      iVar1 = param_3[2];
      if ((iVar1 != 0) && (*(int *)(iVar1 + 0x14) == 2)) {
        if (*(byte *)(iVar1 + 0x1a) < 0xf) {
          uVar4 = 0x145d;
          uVar5 = 0xffffffff;
        }
        else {
          uVar4 = 0x1461;
          uVar5 = 0xfffffffb;
        }
        __ZTE_STA_Assoc_Process(param_1,0x1a,0,uVar5,0,0,param_3,"WPABuildPairMsg4",uVar4);
      }
      if (2 < DebugLevel) {
        printk("<=== %s: send Msg4 of 4-way\n","WPABuildPairMsg4");
      }
    }
  }
  return;
}

