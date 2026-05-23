// module: mt7915.ko
// function: wlan_dbg_show_sta_offline @ 0x1589e4
// size: 684 bytes
//

undefined4 wlan_dbg_show_sta_offline(int *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined1 *puVar5;
  int iVar6;
  int local_3c;
  char *local_2c [2];
  
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  iVar2 = 0;
  if (iVar1 != 0) {
    iVar2 = HcGetBandByWdev();
  }
  if (param_2 == 0) {
    local_3c = 0;
  }
  puVar5 = g_arrstWlanOffline + iVar2 * 0x380;
  if (param_2 != 0) {
    local_3c = os_str_tol(param_2,0,10);
  }
  uVar4 = *(uint *)((int)&g_ulWlanOffLineIndex + iVar2 * 4);
  if (uVar4 < 0x10) {
    os_alloc_mem(0,local_2c,0x400);
    if (local_2c[0] == (char *)0x0) {
      printk("\nwlan_dbg_show_sta_offline Memory malloc failed\n");
    }
    else {
      if (uVar4 == 0) {
        iVar1 = 0xf;
      }
      else {
        iVar1 = uVar4 - 1;
      }
      printk(
            "\nMAC:              OnTime(sec):   RSSI:         PsMode:  MmpsMode:   OneSecTx:    AvgTxBytes(kbps):  AvgRxBytes(kbps):\n"
            );
      iVar6 = 0x10;
      do {
        iVar3 = *(int *)(puVar5 + iVar1 * 0x38 + 8);
        if (iVar3 != 0) {
          if (*(int *)(puVar5 + iVar1 * 0x38 + 0xc) == 0) {
            uVar4 = snprintf(local_2c[0],0x400,"Line=%lu,Reason=%d,Times=%lu\n",iVar3,
                             (uint)*(ushort *)(puVar5 + iVar1 * 0x38 + 0x1e),
                             *(undefined4 *)(puVar5 + iVar1 * 0x38 + 0x10));
          }
          else {
            uVar4 = snprintf(local_2c[0],0x400,"Func:%s Line=%lu, Reason=%d,Times=%lu\n",
                             *(int *)(puVar5 + iVar1 * 0x38 + 0xc),iVar3,
                             (uint)*(ushort *)(puVar5 + iVar1 * 0x38 + 0x1e),
                             *(undefined4 *)(puVar5 + iVar1 * 0x38 + 0x10));
          }
          if (0x3fe < uVar4) {
LAB_00158b98:
            os_free_mem(local_2c[0]);
            return 1;
          }
          iVar3 = snprintf(local_2c[0] + uVar4,0x400 - uVar4,
                           "%02x:%02x:%02x:%02x:%02x:%02x  %-10lu  %-3d/%-3d/%-3d/%-3d  %-2d       %-2d          %-10lu      %-10lu       %-10lu\n"
                           ,(uint)(byte)puVar5[iVar1 * 0x38],(uint)(byte)puVar5[iVar1 * 0x38 + 1],
                           (uint)(byte)puVar5[iVar1 * 0x38 + 2],(uint)(byte)puVar5[iVar1 * 0x38 + 3]
                           ,(uint)(byte)puVar5[iVar1 * 0x38 + 4],
                           (uint)(byte)puVar5[iVar1 * 0x38 + 5],
                           *(undefined4 *)(puVar5 + iVar1 * 0x38 + 0x14),
                           (int)(char)puVar5[iVar1 * 0x38 + 0x18],
                           (int)(char)puVar5[iVar1 * 0x38 + 0x19],
                           (int)(char)puVar5[iVar1 * 0x38 + 0x1a],
                           (int)(char)puVar5[iVar1 * 0x38 + 0x1b],
                           (uint)(byte)puVar5[iVar1 * 0x38 + 0x1c],
                           (uint)(byte)puVar5[iVar1 * 0x38 + 0x1d],
                           *(undefined4 *)(puVar5 + iVar1 * 0x38 + 0x2c),
                           *(uint *)(puVar5 + iVar1 * 0x38 + 0x30) >> 7,
                           *(uint *)(puVar5 + iVar1 * 0x38 + 0x34) >> 7);
          uVar4 = iVar3 + uVar4;
          if (0x3fe < uVar4) goto LAB_00158b98;
          StatRateToString(param_1,local_2c[0] + uVar4,0,
                           *(undefined4 *)(puVar5 + iVar1 * 0x38 + 0x20));
          StatRateToString(param_1,local_2c[0] + uVar4,1,
                           *(undefined4 *)(puVar5 + iVar1 * 0x38 + 0x24));
          printk(&_LC108,local_2c[0]);
        }
        if (iVar1 == 0) {
          iVar1 = 0xf;
        }
        else {
          iVar1 = iVar1 + -1;
        }
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
      printk(&_LC45);
      os_free_mem(local_2c[0]);
      if (local_3c != 0) {
        __memzero(puVar5,0x380);
        *(undefined4 *)((int)&g_ulWlanOffLineIndex + iVar2 * 4) = 0;
      }
    }
  }
  else {
    printk("\nwlan_dbg_show_sta_offline ulCurIndex is %lu error\n",uVar4);
  }
  return 1;
}

