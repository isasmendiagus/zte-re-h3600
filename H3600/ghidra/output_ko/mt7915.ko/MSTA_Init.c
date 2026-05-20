// module: mt7915.ko
// function: MSTA_Init @ 0x68e30
// size: 1648 bytes
//

/* WARNING: Type propagation algorithm not settling */

void MSTA_Init(int param_1,undefined4 *param_2)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  char *pcVar8;
  uint uVar9;
  undefined4 uVar10;
  undefined4 *puVar11;
  int iVar12;
  undefined *puVar13;
  char cVar14;
  undefined4 *puVar15;
  undefined4 *puVar16;
  uint local_ac;
  undefined1 *local_9c;
  uint local_90 [2];
  char local_88 [32];
  undefined4 local_68 [8];
  undefined *local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined2 local_3c;
  undefined1 local_2a;
  
  local_90[0] = 0;
  local_90[1] = 0;
  local_ac = (uint)*(byte *)(param_1 + 0x794ab9);
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar3 = DebugLevel;
  if ((*(byte *)(param_1 + 0x286294) & 3) == 3) {
    uVar9 = (uint)(byte)(&DAT_003678f9)[param_1];
    local_ac = uVar9;
    if (1 < uVar9) {
      local_ac = 2;
    }
    if (*(char *)(param_1 + 0x794aba) != '\0') {
      *(char *)(param_1 + 0x794ab8) = (char)local_ac;
      if (0 < iVar3) {
        printk("%s re-assign MSTANum=%d\n","MSTA_Init");
        uVar9 = (uint)(byte)(&DAT_003678f9)[param_1];
      }
      local_90[0] = 0;
      if (uVar9 == 0) {
        return;
      }
      do {
        iVar3 = local_90[0] * 0x2137b0;
        wlan_config_set_ext_cha(&DAT_0036db58 + param_1 + iVar3,0xf);
        apcli_sync_wdev(param_1,&DAT_0036db58 + param_1 + iVar3);
        local_90[0] = local_90[0] + 1;
      } while (local_90[0] < (byte)(&DAT_003678f9)[param_1]);
      return;
    }
    uVar9 = 0;
    if (DebugLevel < 1) {
      local_9c = apcli_wdev_ops;
      uVar10 = 0x400;
      goto LAB_00068ed0;
    }
    local_9c = apcli_wdev_ops;
    uVar10 = 0x400;
    pcVar8 = "ApCli";
  }
  else {
    if (*(char *)(param_1 + 0x794aba) != '\0') {
      return;
    }
    if (DebugLevel < 1) {
      uVar9 = 1;
      uVar10 = 0x800;
      local_9c = sta_wdev_ops;
      goto LAB_00068ed0;
    }
    local_9c = sta_wdev_ops;
    pcVar8 = "STA";
    uVar10 = 0x800;
    uVar9 = 1;
  }
  printk("%s (%d) ---> %s\n","MSTA_Init",local_ac,pcVar8);
LAB_00068ed0:
  local_90[0] = uVar9;
  if (uVar9 < local_ac) {
    do {
      local_88[0] = '\0';
      local_88[1] = '\0';
      local_88[2] = '\0';
      local_88[3] = '\0';
      local_88[4] = '\0';
      local_88[5] = '\0';
      local_88[6] = '\0';
      local_88[7] = '\0';
      local_88[8] = '\0';
      local_88[9] = '\0';
      local_88[10] = '\0';
      local_88[0xb] = '\0';
      local_88[0xc] = '\0';
      local_88[0xd] = '\0';
      local_88[0xe] = '\0';
      local_88[0xf] = '\0';
      puVar13 = &DAT_0036db58 + param_1 + uVar9 * 0x2137b0;
      local_88[0x10] = '\0';
      local_88[0x11] = '\0';
      local_88[0x12] = '\0';
      local_88[0x13] = '\0';
      local_88[0x14] = '\0';
      local_88[0x15] = '\0';
      local_88[0x16] = '\0';
      local_88[0x17] = '\0';
      local_88[0x18] = '\0';
      local_88[0x19] = '\0';
      local_88[0x1a] = '\0';
      local_88[0x1b] = '\0';
      local_88[0x1c] = '\0';
      local_88[0x1d] = '\0';
      local_88[0x1e] = '\0';
      local_88[0x1f] = '\0';
      local_90[0] = uVar9;
      iVar3 = get_dev_name_prefix(param_1,uVar10);
      iVar4 = RtmpOSNetDevCreate(0,local_90 + 1,uVar10,local_90[0],0x10,iVar3,1);
      if ((*(byte *)(param_1 + 0x286294) & 3) == 3) {
        if (iVar3 == 0) {
          if (-1 < DebugLevel) {
            printk("%s(): apcli interface name is null,apcli idx=%d!\n","MSTA_Init",local_90[0]);
          }
          break;
        }
        snprintf(local_88,0x20,"%s",iVar3);
        multi_profile_apcli_devname_req(param_1,local_88,local_90);
        if (*(char *)(param_1 + 0x79504d) == '\x01') {
          iVar4 = RtmpOSNetDevCreate(0,local_90 + 1,uVar10,0,0x10,local_88,1);
        }
        else {
          iVar4 = RtmpOSNetDevCreate(0,local_90 + 1,uVar10,local_90[0],0x10,local_88,1);
        }
      }
      iVar3 = DebugLevel;
      if (iVar4 == 0) break;
      cVar14 = (char)local_90[0];
      *(char *)(param_1 + 0x794ab8) = cVar14 + '\x01';
      if (0 < iVar3) {
        printk("Register MSTA IF (%s) , pAd->MSTANum = %d\n",iVar4);
        cVar14 = (char)local_90[0];
      }
      iVar3 = param_1 + uVar9 * 0x2137b0;
      (&DAT_00580eeb)[iVar3] = 0x13;
      (&DAT_00580eec)[iVar3] = 0x13;
      iVar3 = wdev_init(param_1,puVar13,2,iVar4,(int)cVar14,puVar13,param_1);
      if (iVar3 == 0) {
        if (-1 < DebugLevel) {
          printk("Assign wdev idx for %s failed, free net device!\n",iVar4);
        }
LAB_000693a4:
        RtmpOSNetDevFree(iVar4);
        CliLinkMapInit(param_1);
        return;
      }
      iVar3 = wdev_ops_register(puVar13,2,local_9c,*(undefined1 *)(iVar2 + 0x75));
      if (iVar3 == 0) {
        if (-1 < DebugLevel) {
          printk("register wdev_ops %s failed, free net device!\n",iVar4);
        }
        goto LAB_000693a4;
      }
      puVar11 = local_68;
      puVar15 = param_2;
      do {
        puVar16 = puVar15 + 4;
        uVar5 = puVar15[1];
        uVar6 = puVar15[2];
        uVar7 = puVar15[3];
        *puVar11 = *puVar15;
        puVar11[1] = uVar5;
        puVar11[2] = uVar6;
        puVar11[3] = uVar7;
        puVar11 = puVar11 + 4;
        puVar15 = puVar16;
      } while (puVar16 != param_2 + 0x10);
      iVar3 = uVar9 * 0x2137b0;
      local_2a = 1;
      iVar12 = param_1 + iVar3;
      *(undefined4 *)(&DAT_0036db70 + iVar12 + 3) = *(undefined4 *)(param_1 + 0x794b5b);
      *(undefined2 *)(&DAT_0036db70 + iVar12 + 7) = *(undefined2 *)(param_1 + 0x794b5f);
      local_48 = puVar13;
      local_44 = uVar10;
      if ((*(byte *)(param_1 + 0x286294) & 3) == 3) {
        apcli_sync_wdev(param_1,puVar13);
        SetCommonHtVht(param_1,puVar13);
        RTMPUpdateRateInfo(*(undefined2 *)(&DAT_0036db70 + param_1 + iVar3),
                           &DAT_0036e636 + param_1 + iVar3);
        AsicSetWdevIfAddr(param_1,puVar13,0);
      }
      else {
        iVar3 = param_1 + iVar3;
        (&DAT_0036db73)[iVar3] = (&DAT_0036db73)[iVar3] | 2;
        (&DAT_0036db76)[iVar3] = (&DAT_0036db76)[iVar3] & 0xef | (byte)(local_90[0] << 4);
      }
      RtmpOsSetNetDevPriv(iVar4,param_1);
      RtmpOsSetNetDevWdev(iVar4,puVar13);
      local_40 = *(undefined4 *)(&DAT_0036db70 + iVar12 + 3);
      local_3c = *(undefined2 *)(&DAT_0036db70 + iVar12 + 7);
      iVar12 = param_1 + uVar9 * 0x2137b0;
      HcGetBandByWdev(puVar13);
      iVar3 = ApcliCardIndex2WlanIdmMap();
      uVar1 = 0;
      if (iVar3 != 0) {
        uVar1 = *(undefined1 *)(iVar3 + 0x21);
      }
      uVar5 = register_idm_fdb_node(uVar1,iVar4);
      *(undefined4 *)(s__RB_FULL__Free_Queue_List___00371ba4 + iVar12 + 0xc) = uVar5;
      setHwMirrorFlag(iVar4);
      RtmpOSNetDevAttach(*(undefined1 *)(param_1 + 0x286285),iVar4,local_68);
      (&DAT_00580e8c)[iVar12] = 1;
      uVar9 = local_90[0] + 1;
      *(undefined1 *)(param_1 + 0x794aba) = 1;
      local_90[0] = uVar9;
    } while (uVar9 < local_ac);
  }
  CliLinkMapInit(param_1);
  return;
}

