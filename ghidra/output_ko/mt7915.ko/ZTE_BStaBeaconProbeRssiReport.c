// module: mt7915.ko
// function: ZTE_BStaBeaconProbeRssiReport @ 0x161e3c
// size: 812 bytes
//

undefined4 ZTE_BStaBeaconProbeRssiReport(int param_1,int param_2,uint *param_3)

{
  char cVar1;
  int iVar2;
  undefined1 *__s1;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  char *__s2;
  int iVar7;
  bool bVar8;
  uint local_38;
  undefined4 *local_2c [2];
  
  local_2c[0] = (undefined4 *)0x0;
  iVar2 = HcGetBandByWdev(param_2);
  iVar3 = *(int *)(param_1 + (int)("mt_cmd_get_sta_tx_statistic" + iVar2) * 4);
  scan_release_mem(param_1);
  if (param_3 != (uint *)0x0 && iVar3 != 0) {
    uVar5 = (uint)*(byte *)(iVar3 + 0xe);
    iVar3 = uVar5 * 0x5834;
    if (param_1 + iVar3 != -0x2bc6bc) {
      os_alloc_mem(0,local_2c,0x40c);
      if (local_2c[0] != (undefined4 *)0x0) {
        __memzero(local_2c[0],0x40c);
        if (0 < DebugLevel) {
          printk("==mac=%02x:%02x:%02x:%02x:%02x:%02x num=%d--%d\n",*(undefined1 *)(param_2 + 0x1b),
                 *(undefined1 *)(param_2 + 0x1c),*(undefined1 *)(param_2 + 0x1d),
                 *(undefined1 *)(param_2 + 0x1e),*(undefined1 *)(param_2 + 0x1f),
                 *(undefined1 *)(param_2 + 0x20),
                 *(undefined4 *)
                  (
                  "Query::RT_OID_802_11_QUERY_APSD_SETTING (=0x%lx,APSDCap=%d,AC_BE=%d,AC_BK=%d,AC_VI=%d,AC_VO=%d,MAXSPLen=%d)\n"
                  + param_1 + iVar3 + 0x60),*param_3);
        }
        iVar7 = uVar5 * 0x5834;
        iVar3 = param_1 + iVar7;
        *local_2c[0] = *(undefined4 *)(param_2 + 0x1b);
        *(undefined2 *)(local_2c[0] + 1) = *(undefined2 *)(param_2 + 0x1f);
        uVar5 = 0;
        if (*(int *)(
                    "Query::RT_OID_802_11_QUERY_APSD_SETTING (=0x%lx,APSDCap=%d,AC_BE=%d,AC_BK=%d,AC_VI=%d,AC_VO=%d,MAXSPLen=%d)\n"
                    + iVar3 + 0x60) != 0) {
          uVar6 = *param_3;
          __s2 = "Query::RT_OID_802_11_QUERY_APSD_SETTING (=0x%lx,APSDCap=%d,AC_BE=%d,AC_BK=%d,AC_VI=%d,AC_VO=%d,MAXSPLen=%d)\n"
                 + param_1 + iVar7 + 100;
          uVar5 = 0;
          local_38 = 0;
          do {
            if (uVar6 != 0) {
              __s1 = (undefined1 *)((int)param_3 + 0xe);
              uVar4 = 0;
              do {
                iVar7 = memcmp(__s1,__s2,6);
                if (iVar7 == 0) {
                  if ((byte)__s1[6] < 0x24) {
                    if (iVar2 == 1) break;
                  }
                  else if (iVar2 == 0) break;
                  *(char *)((int)local_2c[0] + 6) = *(char *)((int)local_2c[0] + 6) + '\x01';
                  *(undefined1 *)((int)local_2c[0] + uVar5 + 0xd) = 0x1e;
                  *(undefined1 *)((int)local_2c[0] + uVar5 + 0x11) = 0;
                  *(undefined1 *)((int)local_2c[0] + uVar5 + 0x12) = __s1[6];
                  cVar1 = __s1[0x6b];
                  if (cVar1 == '\0') {
                    cVar1 = -1;
                  }
                  *(char *)((int)local_2c[0] + uVar5 + 0x1e) = cVar1;
                  *(undefined4 *)((int)local_2c[0] + uVar5 + 0x20) = *(undefined4 *)__s2;
                  bVar8 = -1 < DebugLevel;
                  *(undefined2 *)((int)local_2c[0] + uVar5 + 0x24) = *(undefined2 *)(__s2 + 4);
                  if (bVar8) {
                    printk("rcpi=%u channel=%d rssi=%d %02x:%02x j=%d\n",
                           *(undefined1 *)((int)local_2c[0] + uVar5 + 0x1e),
                           *(undefined1 *)((int)local_2c[0] + uVar5 + 0x12),(int)(char)__s1[0x6b],
                           *__s1,__s1[5],uVar4);
                  }
                  uVar6 = *param_3;
                  uVar5 = uVar5 + 0x20 & 0xffff;
                }
                uVar4 = uVar4 + 1;
                __s1 = __s1 + 0xaf4;
              } while (uVar4 < uVar6);
            }
            __s2 = __s2 + 0x2d;
            local_38 = local_38 + 1;
          } while (local_38 <
                   *(uint *)(
                            "Query::RT_OID_802_11_QUERY_APSD_SETTING (=0x%lx,APSDCap=%d,AC_BE=%d,AC_BK=%d,AC_VI=%d,AC_VO=%d,MAXSPLen=%d)\n"
                            + iVar3 + 0x60));
        }
        if (*(char *)((int)local_2c[0] + 6) != '\0') {
          local_2c[0][2] = uVar5;
          Kernel_ASEND("multiapd.map.slave",0xa2bc,local_2c[0],0x40c,0,0);
        }
        os_free_mem(local_2c[0]);
        return 1;
      }
      if (-1 < DebugLevel) {
        printk("alloc memory failed sizeof=%u",0x40c);
      }
    }
  }
  return 0;
}

