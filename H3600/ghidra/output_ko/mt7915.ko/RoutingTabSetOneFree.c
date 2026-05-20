// module: mt7915.ko
// function: RoutingTabSetOneFree @ 0xa0cc0
// size: 692 bytes
//

void RoutingTabSetOneFree(int param_1,uint param_2,void *param_3,uint param_4)

{
  char *pcVar1;
  int *piVar2;
  uint uVar3;
  int *piVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  uint uVar8;
  
  uVar3 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (uVar3 <= param_2 || 0x1f < param_2) {
    return;
  }
  if ("RT_OID_WSC_SET_CONN_BY_PROFILE_INDEX:: wrong wsc_profile_index(%d)\n"
      [param_1 + param_2 * 0x5834 + 0x41] == '\0') {
    return;
  }
  if (param_3 == (void *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s: Hash Id isn\'t correct!\n","RoutingTabSetOneFree");
      return;
    }
    return;
  }
  uVar3 = *(byte *)((int)param_3 + 5) & 0x3f;
  _raw_spin_lock_bh("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" +
                    param_1 + param_2 * 0x5834 + 4);
  for (piVar4 = (int *)GetRoutingTabHead(param_1,param_2,uVar3); piVar4 != (int *)0x0;
      piVar4 = (int *)*piVar4) {
    if ((*(char *)((int)piVar4 + 0x11) != '\0') &&
       (iVar5 = memcmp(param_3,piVar4 + 6,6), iVar5 == 0)) {
      uVar8 = piVar4[1];
      piVar4[1] = uVar8 & ~param_4;
      if ((uVar8 & ~param_4) == 0) {
        iVar5 = param_1 + param_2 * 0x5834 + uVar3 * 0xc;
        piVar6 = *(int **)("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" +
                          iVar5 + 0x18);
        if (piVar6 == (int *)0x0) goto LAB_000a0e44;
        if (piVar6 != piVar4) {
          piVar2 = (int *)*piVar6;
          goto joined_r0x000a0e1c;
        }
        iVar7 = *piVar4;
        *(int *)("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + iVar5 + 0x18) =
             iVar7;
        if (iVar7 == 0) {
          pcVar1 = "RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" +
                   param_1 + uVar3 * 0xc + param_2 * 0x5834 + 0x1c;
          pcVar1[0] = '\0';
          pcVar1[1] = '\0';
          pcVar1[2] = '\0';
          pcVar1[3] = '\0';
        }
        iVar5 = param_1 + param_2 * 0x5834 + uVar3 * 0xc;
        "RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n"[iVar5 + 0x20] =
             "RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n"[iVar5 + 0x20] + -1;
        goto LAB_000a0e44;
      }
      break;
    }
  }
LAB_000a0d98:
  _raw_spin_unlock_bh("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" +
                      param_1 + param_2 * 0x5834 + 4);
  return;
joined_r0x000a0e1c:
  if (piVar2 == (int *)0x0) goto LAB_000a0e44;
  if (piVar2 == piVar4) {
    *piVar6 = *piVar4;
    iVar5 = param_1 + param_2 * 0x5834 + uVar3 * 0xc;
    if (*(int **)("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + iVar5 + 0x1c) ==
        piVar4) {
      *(int **)("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + iVar5 + 0x1c) =
           piVar6;
    }
    iVar5 = param_1 + param_2 * 0x5834 + uVar3 * 0xc;
    "RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n"[iVar5 + 0x20] =
         "RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n"[iVar5 + 0x20] + -1;
    goto LAB_000a0e44;
  }
  piVar6 = piVar2;
  piVar2 = (int *)*piVar2;
  goto joined_r0x000a0e1c;
LAB_000a0e44:
  __memzero(piVar4,0x20);
  iVar5 = param_2 * 0x5834 + param_1;
  *piVar4 = 0;
  if (*(undefined4 **)
       ("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + iVar5 + 0x10) ==
      (undefined4 *)0x0) {
    *(int **)("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + iVar5 + 0xc) = piVar4
    ;
  }
  else {
    **(undefined4 **)("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + iVar5 + 0x10)
         = piVar4;
  }
  iVar5 = param_2 * 0x5834 + param_1;
  *(int **)("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + iVar5 + 0x10) = piVar4;
  "RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n"[iVar5 + 0x14] =
       "RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n"[iVar5 + 0x14] + '\x01';
  goto LAB_000a0d98;
}

