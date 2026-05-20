// module: mt7915.ko
// function: GetRoutingEntryAll @ 0xa0f78
// size: 308 bytes
//

undefined4
GetRoutingEntryAll(int param_1,uint param_2,uint param_3,uint param_4,int param_5,int param_6,
                  int *param_7)

{
  uint uVar1;
  undefined4 uVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  
  uVar1 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (param_2 < uVar1 && param_2 < 0x20) {
    if ("RT_OID_WSC_SET_CONN_BY_PROFILE_INDEX:: wrong wsc_profile_index(%d)\n"
        [param_1 + param_2 * 0x5834 + 0x41] == '\0' || param_6 == 0) {
      uVar2 = 0;
    }
    else {
      iVar4 = 0;
      _raw_spin_lock_bh("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" +
                        param_1 + param_2 * 0x5834 + 4);
      iVar5 = iVar4;
      do {
        for (piVar3 = (int *)GetRoutingTabHead(param_1,param_2,iVar5); piVar3 != (int *)0x0;
            piVar3 = (int *)*piVar3) {
          while (((*(char *)((int)piVar3 + 0x11) == '\0' ||
                  (*(ushort *)((int)piVar3 + 0x12) != param_3)) || ((param_4 & piVar3[1]) == 0))) {
            piVar3 = (int *)*piVar3;
            if (piVar3 == (int *)0x0) goto LAB_000a1084;
          }
          if (param_5 <= iVar4) goto LAB_000a1090;
          *(int **)(param_6 + iVar4 * 4) = piVar3;
          iVar4 = iVar4 + 1;
        }
LAB_000a1084:
        iVar5 = iVar5 + 1;
      } while (iVar5 != 0x40);
LAB_000a1090:
      _raw_spin_unlock_bh("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" +
                          param_1 + param_2 * 0x5834 + 4);
      uVar2 = 1;
      *param_7 = iVar4;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

