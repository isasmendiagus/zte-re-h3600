// module: mt7915.ko
// function: RoutingTabSetAllFree @ 0xa0ac8
// size: 504 bytes
//

void RoutingTabSetAllFree(int param_1,uint param_2,uint param_3,uint param_4)

{
  undefined4 *puVar1;
  uint uVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined4 *puVar7;
  int iVar8;
  char *pcVar9;
  
  uVar2 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (param_2 < uVar2 && param_2 < 0x20) {
    iVar6 = param_2 * 0x5834;
    iVar4 = param_1 + iVar6;
    if ("RT_OID_WSC_SET_CONN_BY_PROFILE_INDEX:: wrong wsc_profile_index(%d)\n"[iVar4 + 0x41] != '\0'
       ) {
      _raw_spin_lock_bh("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" +
                        param_1 + iVar6 + 4);
      pcVar9 = "RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" +
               param_1 + iVar6 + 0x18;
      iVar8 = 0;
      do {
        puVar3 = (undefined4 *)GetRoutingTabHead(param_1,param_2,iVar8);
        if (puVar3 != (undefined4 *)0x0) {
          do {
            while (((puVar7 = (undefined4 *)*puVar3, *(char *)((int)puVar3 + 0x11) != '\0' &&
                    (*(ushort *)((int)puVar3 + 0x12) == param_3)) &&
                   (uVar2 = puVar3[1], puVar3[1] = uVar2 & ~param_4, (uVar2 & ~param_4) == 0))) {
              puVar5 = *(undefined4 **)pcVar9;
              if (puVar5 != (undefined4 *)0x0) {
                if (puVar3 == puVar5) {
                  *(undefined4 **)pcVar9 = puVar7;
                  if (puVar7 == (undefined4 *)0x0) {
                    pcVar9[4] = '\0';
                    pcVar9[5] = '\0';
                    pcVar9[6] = '\0';
                    pcVar9[7] = '\0';
                  }
LAB_000a0ca0:
                  pcVar9[8] = pcVar9[8] + -1;
                }
                else {
                  for (puVar1 = (undefined4 *)*puVar5; puVar1 != (undefined4 *)0x0;
                      puVar1 = (undefined4 *)*puVar1) {
                    if (puVar1 == puVar3) {
                      *puVar5 = puVar7;
                      if (puVar3 == *(undefined4 **)(pcVar9 + 4)) {
                        *(undefined4 **)(pcVar9 + 4) = puVar5;
                      }
                      goto LAB_000a0ca0;
                    }
                    puVar5 = puVar1;
                  }
                }
              }
              __memzero(puVar3,0x20);
              *puVar3 = 0;
              if (*(undefined4 **)
                   ("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + iVar4 + 0x10)
                  == (undefined4 *)0x0) {
                *(undefined4 **)
                 ("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + iVar4 + 0xc) =
                     puVar3;
              }
              else {
                **(undefined4 **)
                  ("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + iVar4 + 0x10) =
                     puVar3;
              }
              *(undefined4 **)
               ("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + iVar4 + 0x10) =
                   puVar3;
              "RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n"[iVar4 + 0x14] =
                   "RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n"[iVar4 + 0x14] +
                   '\x01';
              puVar3 = puVar7;
              if (puVar7 == (undefined4 *)0x0) goto LAB_000a0c6c;
            }
            puVar3 = puVar7;
          } while (puVar7 != (undefined4 *)0x0);
        }
LAB_000a0c6c:
        iVar8 = iVar8 + 1;
        pcVar9 = pcVar9 + 0xc;
        if (iVar8 == 0x40) {
          _raw_spin_unlock_bh("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" +
                              param_1 + iVar6 + 4);
          return;
        }
      } while( true );
    }
  }
  return;
}

