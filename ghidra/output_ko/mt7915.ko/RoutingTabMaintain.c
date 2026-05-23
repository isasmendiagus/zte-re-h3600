// module: mt7915.ko
// function: RoutingTabMaintain @ 0xa13cc
// size: 960 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void RoutingTabMaintain(int param_1,uint param_2)

{
  bool bVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  byte bVar9;
  code *pcVar10;
  int *piVar11;
  int iVar12;
  int *piVar13;
  int *piVar14;
  int iVar15;
  undefined4 *local_48;
  undefined4 local_34;
  undefined4 local_2e;
  undefined2 local_2a;
  
  iVar8 = *(int *)("Get_RBIST_Raw_Data_Proc" + param_1 + 0x14);
  local_34 = 0;
  local_2e = 0;
  local_2a = 0;
  uVar3 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if ((param_2 < uVar3 && param_2 < 0x20) &&
     (iVar4 = RoutingTabGetEntryCount(param_1,param_2), iVar4 != 0)) {
    iVar5 = memcmp(&DAT_00368118 + param_1,&ZERO_MAC_ADDR,6);
    iVar4 = jiffies;
    if (iVar5 == 0) {
      pcVar10 = _release_firmware;
      if (_release_firmware != release_firmware) {
        do {
          if (((*(int *)(pcVar10 + 0x108) == 2) && (*(int *)(pcVar10 + 0x18c) != 0)) &&
             (iVar5 = *(int *)(*(int *)(pcVar10 + 0x18c) + 0xc), iVar5 != 0)) {
            local_34 = *(undefined4 *)(iVar5 + 0x1c);
            local_2e = **(undefined4 **)(pcVar10 + 0x1a8);
            local_2a = *(undefined2 *)(*(undefined4 **)(pcVar10 + 0x1a8) + 1);
            goto LAB_000a14ec;
          }
          pcVar10 = *(code **)pcVar10;
        } while (pcVar10 != release_firmware);
      }
    }
    else {
      local_2e = *(undefined4 *)(&DAT_00368118 + param_1);
      local_2a = *(undefined2 *)(&DAT_0036811c + param_1);
LAB_000a14ec:
      local_48 = &local_2e;
      iVar12 = param_2 * 0x5834;
      iVar15 = 0;
      iVar5 = param_1 + iVar12;
      bVar1 = false;
      _raw_spin_lock_bh("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" +
                        param_1 + iVar12 + 4);
      piVar14 = (int *)("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" +
                       param_1 + iVar12 + 0x18);
      do {
        piVar6 = (int *)GetRoutingTabHead(param_1,param_2,iVar15);
        if (piVar6 != (int *)0x0) {
          do {
            while( true ) {
              piVar13 = (int *)*piVar6;
              if (*(int *)(param_1 + 0xa7cbe4) == 0) break;
              *(undefined1 *)((int)piVar6 + 0x1e) = 1;
              if ((*(char *)((int)piVar6 + 0x11) == '\0') || (-1 < piVar6[2] - iVar4))
              goto LAB_000a15a4;
LAB_000a1698:
              if (piVar6[5] == 0) goto LAB_000a1620;
              bVar9 = *(byte *)(piVar6 + 4);
              if (bVar9 != 0) goto LAB_000a16b0;
LAB_000a15b0:
              *(byte *)(piVar6 + 4) = bVar9 + 1;
              piVar6[3] = iVar4 + 200;
              iVar7 = RoutingEntrySendAliveCheck(param_1,param_2,piVar6,local_48,local_34);
              if (iVar7 != 0) {
                bVar1 = true;
              }
LAB_000a15ec:
              piVar6 = piVar13;
              if (piVar13 == (int *)0x0) goto LAB_000a1638;
            }
            if ((*(char *)((int)piVar6 + 0x11) != '\0') && (piVar6[2] - iVar4 < 0))
            goto LAB_000a1698;
LAB_000a1620:
            if (*(char *)((int)piVar6 + 0x1e) != '\0') {
LAB_000a15a4:
              bVar9 = *(byte *)(piVar6 + 4);
              if (bVar9 == 0) goto LAB_000a15b0;
LAB_000a16b0:
              if ((piVar6[3] - iVar4 < 0) || (*(char *)((int)piVar6 + 0x1e) != '\0')) {
                if (bVar9 < 5) goto LAB_000a15b0;
                piVar11 = (int *)*piVar14;
                if (piVar11 != (int *)0x0) {
                  if (piVar6 == piVar11) {
                    iVar7 = *piVar6;
                    *piVar14 = iVar7;
                    if (iVar7 == 0) {
                      piVar14[1] = 0;
                    }
LAB_000a1768:
                    *(char *)(piVar14 + 2) = (char)piVar14[2] + -1;
                  }
                  else {
                    for (piVar2 = (int *)*piVar11; piVar2 != (int *)0x0; piVar2 = (int *)*piVar2) {
                      if (piVar2 == piVar6) {
                        *piVar11 = *piVar6;
                        if (piVar6 == (int *)piVar14[1]) {
                          piVar14[1] = (int)piVar11;
                        }
                        goto LAB_000a1768;
                      }
                      piVar11 = piVar2;
                    }
                  }
                }
                __memzero(piVar6,0x20);
                *piVar6 = 0;
                if (*(undefined4 **)
                     ("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + iVar5 + 0x10)
                    == (undefined4 *)0x0) {
                  *(int **)("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" +
                           iVar5 + 0xc) = piVar6;
                }
                else {
                  **(undefined4 **)
                    ("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + iVar5 + 0x10)
                       = piVar6;
                }
                *(int **)("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" +
                         iVar5 + 0x10) = piVar6;
                "RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n"[iVar5 + 0x14] =
                     "RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n"[iVar5 + 0x14] +
                     '\x01';
              }
              goto LAB_000a15ec;
            }
            *(undefined1 *)(piVar6 + 4) = 0;
            piVar6 = piVar13;
          } while (piVar13 != (int *)0x0);
        }
LAB_000a1638:
        iVar15 = iVar15 + 1;
        piVar14 = piVar14 + 3;
      } while (iVar15 != 0x40);
      _raw_spin_unlock_bh("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" +
                          param_1 + iVar12 + 4);
      if (bVar1) {
        (**(code **)(iVar8 + 0x3c))(param_1,0);
      }
    }
  }
  return;
}

