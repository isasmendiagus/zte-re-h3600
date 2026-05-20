// module: mt7915.ko
// function: peer_twt_action @ 0x1694d0
// size: 1512 bytes
//

void peer_twt_action(int param_1,int param_2)

{
  char cVar1;
  byte bVar2;
  ushort uVar3;
  bool bVar4;
  int *piVar5;
  uint uVar6;
  int iVar7;
  int *piVar8;
  undefined4 uVar9;
  int iVar10;
  int *piVar11;
  ushort *puVar12;
  int iVar13;
  undefined4 local_58;
  int local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  puVar12 = (ushort *)(param_2 + 0x920);
  uVar3 = *puVar12;
  if ((*(byte *)(param_2 + 1) & 0x80) == 0) {
    iVar13 = 0;
  }
  else {
    iVar13 = 4;
  }
  uVar6 = HcGetMaxStaNum();
  if (((uVar3 < uVar6) && (param_1 + (uint)*puVar12 * 0x14c0 + 0xa1d20 != 0)) &&
     (iVar10 = param_1 + (uint)*puVar12 * 0x14c0, *(int *)(iVar10 + 0xa1d28) != 0)) {
    if ((*(uint *)(iVar10 + 0xa1d84) & 0x18) == 0) {
      if (2 < DebugLevel) {
        uVar9 = get_phymode_str(*(byte *)(iVar10 + 0xa1ddf) >> 5);
        printk("%s: Non-HE STA, MaxCap=%s reject\n","peer_twt_action",uVar9);
      }
    }
    else {
      if (iVar13 != 0) {
        memmove((void *)(param_2 + 0x18),(void *)(param_2 + iVar13 + 0x18),
                *(int *)(param_2 + 0x908) - iVar13);
      }
      cVar1 = *(char *)(param_2 + 0x19);
      if (2 < DebugLevel) {
        printk("%s: get twt action=%d\n","peer_twt_action",cVar1);
      }
      if (cVar1 == '\a') {
        iVar13 = *(int *)(param_2 + 0x92c);
        uVar3 = *puVar12;
        if (iVar13 == 0) {
          if (-1 < DebugLevel) {
            printk("%s: wdev=NULL, please check\n","peer_twt_teardown_action");
          }
        }
        else {
          if (2 < DebugLevel) {
            printk("%s: wcid=%d,flow_id=%d\n","peer_twt_teardown_action",uVar3,
                   *(undefined1 *)(param_2 + 0x1a));
          }
          if (*(int *)(iVar13 + 0x14) == 2) {
            twtReqFsmRunEventRxTeardown(param_1,iVar13,*(undefined1 *)(param_2 + 0x1a));
          }
          else {
            FUN_00167230(iVar13,uVar3,*(undefined1 *)(param_2 + 0x1a));
          }
        }
      }
      else if (cVar1 == '\v') {
        iVar13 = *(int *)(param_2 + 0x92c);
        uVar3 = *puVar12;
        local_4c = 0;
        local_48 = 0;
        local_44 = 0;
        local_40 = 0;
        local_3c = 0;
        local_38 = 0;
        local_34 = 0;
        local_30 = 0;
        local_2c = 0;
        local_28 = 0;
        local_24 = 0;
        local_54 = 0;
        local_50 = 0;
        if (iVar13 == 0) {
          if (-1 < DebugLevel) {
            printk("%s: wdev=NULL, please check\n","peer_twt_info_action");
          }
        }
        else {
          iVar10 = hc_get_hdev_ctrl(iVar13);
          bVar2 = *(byte *)(param_2 + 0x1b);
          uVar6 = ((uint)bVar2 << 0x19) >> 0x1e;
          if (uVar6 != 0) {
            os_move_mem(&local_54,(void *)(param_2 + 0x1c),8);
          }
          piVar11 = (int *)0x0;
          piVar8 = (int *)(iVar10 + 0x30c0);
          bVar4 = false;
          do {
            for (piVar5 = (int *)*piVar8; piVar8 != piVar5; piVar5 = (int *)*piVar5) {
              if (piVar5 == (int *)0x0) {
                if (DebugLevel < 0) {
                  return;
                }
                printk("%s: twt_entry=NULL, please check\n","peer_twt_info_action");
                return;
              }
              piVar11 = piVar5;
              if ((uVar3 == *(ushort *)(piVar5 + 3)) &&
                 ((uint)*(byte *)((int)piVar5 + 0xb) == (bVar2 & 3))) {
                bVar4 = true;
                break;
              }
              if (((*(ushort *)(piVar5 + 3) & 0x8000) != 0) &&
                 (*(char *)((int)piVar5 + 0x37) == '\x01')) {
                puVar12 = (ushort *)((int)piVar5 + 0x36);
                do {
                  puVar12 = puVar12 + 1;
                  if (*puVar12 == uVar3) {
                    bVar4 = true;
                    break;
                  }
                } while (puVar12 != (ushort *)((int)piVar5 + 0x46));
              }
            }
            piVar8 = piVar8 + 2;
          } while (piVar8 != (int *)(iVar10 + 0x30d0));
          if (bVar4) {
            if (uVar6 != 0) {
              *(undefined1 *)((int)piVar11 + 0x35) = 0;
            }
            *(undefined1 *)((int)piVar11 + 0x10) = 8;
            *(int *)((int)piVar11 + 0x28) = local_54;
            *(undefined4 *)((int)piVar11 + 0x2c) = local_50;
            FUN_001671a4(iVar13,piVar11);
            FUN_00166f44(iVar13,piVar11);
            local_4c = CONCAT13(*(undefined1 *)((int)piVar11 + 0xb),
                                CONCAT12(*(undefined1 *)((int)piVar11 + 10),
                                         CONCAT11(1,*(undefined1 *)((int)piVar11 + 9))));
            local_48 = *(undefined4 *)((int)piVar11 + 0xc);
            local_44 = *(undefined4 *)((int)piVar11 + 0x28);
            local_40 = *(undefined4 *)((int)piVar11 + 0x2c);
            local_3c = CONCAT13(1,*(undefined3 *)((int)piVar11 + 0x30));
            local_38 = CONCAT31(local_38._1_3_,*(undefined1 *)((int)piVar11 + 0x33));
            mt_asic_twt_agrt_update
                      (iVar13,local_4c,local_48,local_44,local_40,local_3c,local_38,local_34,
                       local_30,local_2c,local_28,local_24);
          }
          else if (-1 < DebugLevel) {
            printk("%s: found=FALSE, please check\n","peer_twt_info_action");
          }
        }
      }
      else if (cVar1 == '\x06') {
        iVar13 = *(int *)(param_2 + 0x92c);
        iVar10 = param_2 + 0x1b;
        local_58 = 0;
        local_54 = 0;
        if (iVar13 == 0) {
          if (-1 < DebugLevel) {
            printk("%s: wdev=NULL, please check\n","peer_twt_setup_action");
          }
        }
        else if (*(int *)(iVar13 + 0x14) == 2) {
          if (-1 < DebugLevel) {
            printk("-->%s\n","peer_twt_setup_action");
          }
          bVar2 = *(byte *)(iVar13 + 0xe);
          iVar7 = twtGetRxSetupFlowId(iVar10);
          twtParseTWTElement(iVar10,param_1 + (uint)bVar2 * 0x2137b0 + iVar7 * 0x38 + 0x580f58);
          twtReqFsmRunEventRxSetup(param_1,iVar13,iVar7);
        }
        else {
          iVar7 = os_alloc_mem(param_1,&local_58,0x900);
          if (iVar7 == 0) {
            iVar7 = FUN_00166d4c(iVar10);
            if (iVar7 == 0) {
              uVar9 = 7;
            }
            else {
              uVar9 = 4;
            }
            os_zero_mem(&local_4c);
            ActHeaderInit(param_1,&local_4c,param_2 + 10,iVar13 + 0x1b,iVar13 + 0x21);
            local_34 = CONCAT31(CONCAT21(CONCAT11(local_34._3_1_,*(undefined1 *)(param_2 + 0x1a)),6)
                                ,0x16);
            FUN_00168130(iVar13,*puVar12,uVar9,iVar10,(int)&local_34 + 3);
            MakeOutgoingFrame(local_58,&local_54,0x2c,&local_4c,0xffffffff);
            MiniportMMRequest(param_1,1,local_58,local_54);
            os_free_mem(local_58);
          }
          else if (-1 < DebugLevel) {
            printk("%s: allocate memory failed, please check\n","peer_twt_setup_action");
          }
        }
      }
      else if (-1 < DebugLevel) {
        printk("%s: unexpected action=%d, please check\n","peer_twt_action",cVar1);
      }
    }
  }
  return;
}

