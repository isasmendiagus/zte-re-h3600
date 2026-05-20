// module: mt7915.ko
// function: ZTE_BStaBeaconMetricsReport @ 0x161b84
// size: 692 bytes
//

undefined4 ZTE_BStaBeaconMetricsReport(int *param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  char *pcVar4;
  int *piVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  uint uVar11;
  int local_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined2 local_68;
  int local_66;
  undefined4 local_62;
  undefined4 local_5e;
  undefined4 local_5a;
  undefined4 local_56;
  undefined4 local_52;
  undefined2 local_4e;
  uint local_4c;
  undefined1 auStack_48 [36];
  
  local_74 = 0x4030201;
  local_66 = 0x302c2824;
  local_62 = 0x403c3834;
  uStack_70 = 0x8070605;
  uStack_6c = 0xc0b0a09;
  local_5e = 0x706c6864;
  local_68 = 0xe0d;
  local_5a = 0x807c7874;
  local_56 = 0x908c8884;
  local_52 = 0xa19d9995;
  local_4e = 0xa9a5;
  if (*(int *)(*param_1 + 0x38) == 0x400) {
    piVar10 = param_1 + (uint)*(byte *)(*param_1 + 0x3c) * 0x84dec + 0xdb6d6;
    iVar1 = HcGetBandByWdev(piVar10);
    iVar9 = param_1[(int)("mt_cmd_get_sta_tx_statistic" + iVar1)];
    if ((iVar9 != 0) &&
       (uVar11 = (uint)*(byte *)(iVar9 + 0xe), param_1 + uVar11 * 0x160d != (int *)0xffd43944)) {
      if (iVar1 == 1) {
        iVar1 = 0x1a;
        piVar2 = &local_66;
      }
      else {
        piVar2 = &local_74;
        iVar1 = 0xe;
      }
      iVar3 = param_1[uVar11 * 0x160d + 0xaf1af];
      iVar7 = iVar1;
      if (iVar3 != 0) {
        pcVar4 = (char *)((int)param_1 +
                         (int)(
                              "Query::RT_OID_802_11_QUERY_APSD_SETTING (=0x%lx,APSDCap=%d,AC_BE=%d,AC_BK=%d,AC_VI=%d,AC_VO=%d,MAXSPLen=%d)\n"
                              + uVar11 * 0x5834 + 0x6b));
        do {
          piVar5 = piVar2;
          do {
            piVar6 = (int *)((int)piVar5 + 1);
            if ((char)*piVar5 == *pcVar4) {
              *(char *)piVar5 = '\0';
              iVar7 = iVar7 + -1;
              break;
            }
            piVar5 = piVar6;
          } while (piVar6 != (int *)((int)piVar2 + iVar1));
          pcVar4 = pcVar4 + 0x2d;
        } while (pcVar4 != (char *)((int)param_1 +
                                   (int)(
                                        "Query::RT_OID_802_11_QUERY_APSD_SETTING (=0x%lx,APSDCap=%d,AC_BE=%d,AC_BK=%d,AC_VI=%d,AC_VO=%d,MAXSPLen=%d)\n"
                                        + uVar11 * 0x5834 + iVar3 * 0x2d + 0x6b)));
      }
      iVar3 = get_scan_ctrl_by_wdev(param_1,piVar10);
      *(char *)(iVar3 + 0x79) = (char)iVar7;
      if (*(int *)(iVar3 + 0x7c) != 0) {
        os_free_mem();
      }
      os_alloc_mem(0,iVar3 + 0x7c,iVar7);
      if (*(int *)(iVar3 + 0x7c) != 0) {
        pcVar4 = (char *)((int)&local_68 + 1);
        iVar8 = 0;
        do {
          pcVar4 = pcVar4 + 1;
          if (*pcVar4 != '\0' && iVar8 < iVar7) {
            *(char *)(*(int *)(iVar3 + 0x7c) + iVar8) = *pcVar4;
            if (0 < DebugLevel) {
              printk("Channel %d\n",*(undefined1 *)(*(int *)(iVar3 + 0x7c) + iVar8));
            }
            iVar8 = iVar8 + 1;
          }
        } while (pcVar4 != (char *)((int)&local_68 + iVar1 + 1));
        iVar1 = (uint)*(byte *)(iVar9 + 0xe) * 0x5834;
        local_4c = (uint)*(byte *)((int)param_1 + iVar1 + 0x2bb2d1);
        memcpy(auStack_48,
               (char *)((int)param_1 +
                       (int)(
                            "Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n"
                            + iVar1 + 0x34)),local_4c);
        ApSiteSurvey_by_wdev(param_1,&local_4c,0,0,piVar10);
        return 1;
      }
    }
  }
  return 0;
}

