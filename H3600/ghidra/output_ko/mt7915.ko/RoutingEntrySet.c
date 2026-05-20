// module: mt7915.ko
// function: RoutingEntrySet @ 0xa05f8
// size: 368 bytes
//

void RoutingEntrySet(int param_1,uint param_2,undefined2 param_3,undefined4 *param_4,
                    undefined4 *param_5)

{
  byte bVar1;
  undefined2 uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  
  uVar3 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (uVar3 <= param_2 || 0x1f < param_2) {
    return;
  }
  iVar4 = param_2 * 0x5834;
  if ("RT_OID_WSC_SET_CONN_BY_PROFILE_INDEX:: wrong wsc_profile_index(%d)\n"[param_1 + iVar4 + 0x41]
      == '\0' || param_5 == (undefined4 *)0x0) {
    return;
  }
  if (param_4 != (undefined4 *)0x0) {
    bVar1 = *(byte *)((int)param_4 + 5);
    *(undefined2 *)((int)param_5 + 0x12) = param_3;
    *(undefined1 *)((int)param_5 + 0x11) = 1;
    uVar3 = bVar1 & 0x3f;
    param_5[6] = *param_4;
    uVar2 = *(undefined2 *)(param_4 + 1);
    *param_5 = 0;
    *(undefined2 *)(param_5 + 7) = uVar2;
    RoutingEntryRefresh(param_1,param_2,param_5);
    _raw_spin_lock_bh("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" +
                      param_1 + iVar4 + 4);
    *param_5 = 0;
    iVar5 = param_1 + iVar4 + uVar3 * 0xc;
    if (*(undefined4 **)
         ("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + iVar5 + 0x1c) ==
        (undefined4 *)0x0) {
      *(undefined4 **)
       ("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + iVar5 + 0x18) = param_5;
    }
    else {
      **(undefined4 **)
        ("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + iVar5 + 0x1c) = param_5;
    }
    iVar5 = param_1 + param_2 * 0x5834 + uVar3 * 0xc;
    *(undefined4 **)("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + iVar5 + 0x1c)
         = param_5;
    "RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n"[iVar5 + 0x20] =
         "RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n"[iVar5 + 0x20] + '\x01';
    _raw_spin_unlock_bh("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" +
                        param_1 + iVar4 + 4);
    return;
  }
  if (-1 < DebugLevel) {
    printk("%s: Hash Id isn\'t correct!\n","RoutingEntrySet");
    return;
  }
  return;
}

