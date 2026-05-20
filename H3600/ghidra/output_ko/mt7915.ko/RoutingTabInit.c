// module: mt7915.ko
// function: RoutingTabInit @ 0xa02a8
// size: 492 bytes
//

void RoutingTabInit(int param_1,uint param_2,uint param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  char *pcVar6;
  int iVar7;
  
  uVar1 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (uVar1 <= param_2 || 0x1f < param_2) {
    return;
  }
  iVar3 = param_1 + param_2 * 0x5834;
  if ("RT_OID_WSC_SET_CONN_BY_PROFILE_INDEX:: wrong wsc_profile_index(%d)\n"[iVar3 + 0x41] == '\0')
  {
    iVar2 = *(int *)("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + iVar3 + 8);
    if (iVar2 == 0) {
      os_alloc_mem(param_1,"RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" +
                           param_1 + param_2 * 0x5834 + 8,0x2000);
      iVar2 = *(int *)("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + iVar3 + 8);
      if (iVar2 == 0) {
        if (-1 < DebugLevel) {
          printk("%s: Fail to alloc memory for MBSSID[%d].pRoutingEntryPool\n","RoutingTabInit",
                 param_2,param_4);
          return;
        }
        return;
      }
    }
    iVar5 = param_2 * 0x5834;
    __memzero(iVar2,0x2000);
    iVar2 = param_1 + iVar5;
    pcVar6 = "RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + iVar2 + 0x14;
    iVar3 = 0;
    pcVar4 = "RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + iVar2 + 0x10;
    pcVar4[0] = '\0';
    pcVar4[1] = '\0';
    pcVar4[2] = '\0';
    pcVar4[3] = '\0';
    pcVar4 = "RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + iVar2 + 0xc;
    pcVar4[0] = '\0';
    pcVar4[1] = '\0';
    pcVar4[2] = '\0';
    pcVar4[3] = '\0';
    *pcVar6 = '\0';
    do {
      iVar7 = *(int *)("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + iVar2 + 8) +
              iVar3;
      *(undefined4 *)
       (*(int *)("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + iVar2 + 8) + iVar3
       ) = 0;
      iVar3 = iVar3 + 0x20;
      if (*(int **)("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + iVar2 + 0x10)
          == (int *)0x0) {
        *(int *)("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + iVar2 + 0xc) =
             iVar7;
      }
      else {
        **(int **)("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + iVar2 + 0x10) =
             iVar7;
      }
      *(int *)("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + iVar2 + 0x10) =
           iVar7;
      *pcVar6 = *pcVar6 + '\x01';
    } while (iVar3 != 0x2000);
    pcVar4 = "RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + param_1 + iVar5 + 0x1c
    ;
    do {
      pcVar4[0] = '\0';
      pcVar4[1] = '\0';
      pcVar4[2] = '\0';
      pcVar4[3] = '\0';
      pcVar6 = pcVar4 + 0xc;
      pcVar4[-0xffffffff00000004] = '\0';
      pcVar4[-0xffffffff00000003] = '\0';
      pcVar4[-0xffffffff00000002] = '\0';
      pcVar4[-0xffffffff00000001] = '\0';
      pcVar4[4] = '\0';
      pcVar4 = pcVar6;
    } while (pcVar6 != "Query::OID_802_11_STATISTICS\n" + param_1 + iVar5 + 0x1c);
    param_1 = param_2 * 0x5834 + param_1;
    pcVar4 = "RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + param_1 + 4;
    pcVar4[0] = '\0';
    pcVar4[1] = '\0';
    pcVar4[2] = '\0';
    pcVar4[3] = '\0';
    uVar1 = *(uint *)("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + param_1);
    "RT_OID_WSC_SET_CONN_BY_PROFILE_INDEX:: wrong wsc_profile_index(%d)\n"[param_1 + 0x41] = '\x01';
    *(uint *)("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + param_1) =
         param_3 | uVar1;
    return;
  }
  *(uint *)("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + iVar3) =
       param_3 | *(uint *)("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + iVar3);
  return;
}

