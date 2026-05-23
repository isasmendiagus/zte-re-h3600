// module: mt7915.ko
// function: TestMode_TxThread @ 0x2870e0
// size: 2140 bytes
//

int TestMode_TxThread(int param_1)

{
  char cVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  byte bVar9;
  char cVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  int iVar14;
  int iVar15;
  undefined4 uVar16;
  uint uVar17;
  int iVar18;
  int local_68;
  int local_58;
  uint local_40;
  undefined1 auStack_2c [8];
  
  if (param_1 == 0) {
    RtmpOSTaskNotifyToExit();
  }
  else {
    iVar18 = *(int *)(param_1 + 0x10);
    if (3 < DebugLevel) {
      printk("%s: Init thread %u for band %u\n","TestMode_TxThread",
             *(undefined4 *)(iVar18 + 0xa3a054),0);
    }
    complete(iVar18 + 0xa3ba38);
    iVar11 = iVar18 + 0xa3a044;
    local_40 = 0;
    do {
      if (*(char *)(param_1 + 0x18) != '\0') {
        local_68 = 0;
        break;
      }
      iVar3 = RtmpOSTaskWait(iVar18,param_1,auStack_2c);
      if (iVar3 == 0) {
        *(uint *)(iVar18 + 0xa39f84) = *(uint *)(iVar18 + 0xa39f84) | 0x40;
        local_68 = 0;
        break;
      }
      _raw_spin_lock_bh(iVar11);
      bVar9 = *(byte *)(iVar18 + 0xa3a050);
      if (bVar9 == 0) {
        local_68 = 0;
      }
      else {
        local_68 = 0;
        do {
          if ((bVar9 & 1) == 0) {
            if ((*(char *)(iVar18 + 0x79504d) == '\0') || ((bVar9 & 2) == 0)) {
              *(byte *)(iVar18 + 0xa3a050) = bVar9;
              _raw_spin_unlock_bh(iVar11);
              local_40 = 0xffffffff;
              goto LAB_002874d0;
            }
            iVar3 = 1;
            bVar9 = bVar9 & 0xfd;
            local_40 = 1;
          }
          else {
            iVar3 = 0;
            bVar9 = bVar9 & 0xfe;
            local_40 = 0;
          }
          net_ad_wrap_service(iVar18);
          iVar4 = net_ad_wrap_service(iVar18);
          iVar14 = iVar3 * 0xd18;
          local_58 = *(int *)(iVar18 + 0xa3a058);
          uVar2 = *(ushort *)(iVar4 + iVar14 + 0x50e);
          iVar4 = net_ad_wrap_service(iVar18);
          uVar2 = uVar2 & 0xff;
          uVar16 = *(undefined4 *)(iVar4 + iVar14 + 0x504);
          iVar4 = net_ad_wrap_service(iVar18);
          iVar5 = net_ad_wrap_service(iVar18);
          iVar12 = *(int *)(iVar4 + iVar14 + 0x10f4);
          iVar7 = *(int *)(iVar5 + iVar14 + 0x10f0);
          cVar1 = *(char *)(iVar5 + iVar14 + 0x1106);
          iVar4 = net_ad_wrap_service(iVar18);
          iVar4 = iVar4 + iVar14;
          iVar5 = hc_get_hif_type(*(undefined4 *)(iVar18 + 0xa797a0));
          if (iVar5 == 2) {
            uVar2 = hif_get_resource_idx(*(undefined4 *)(iVar18 + 0xa797a0),uVar16,2,uVar2);
            uVar2 = uVar2 & 0xff;
          }
          iVar5 = net_ad_wrap_service(iVar18);
          iVar14 = iVar3 * 0xd18;
          uVar17 = *(uint *)(iVar5 + iVar14 + 0x1120);
          iVar5 = net_ad_wrap_service(iVar18);
          uVar13 = *(uint *)(iVar5 + iVar14 + 0x1118);
          do {
            uVar6 = hif_get_tx_resource_free_num(*(undefined4 *)(iVar18 + 0xa797a0),uVar2);
            if (uVar6 < *(byte *)(iVar4 + 0x6f5)) {
              if (DebugLevel < 3) {
LAB_00287434:
                local_68 = 0;
              }
              else {
                printk("%s: [band%d] insificient ring buffer(resource=%ld:request=%d), thread dissmised!\n"
                       ,"MT_ATETxHandler",iVar3,uVar6,(uint)*(byte *)(iVar4 + 0x6f5));
                local_68 = 0;
              }
              goto LAB_00287438;
            }
            iVar5 = net_ad_wrap_service(iVar18);
            uVar8 = *(uint *)(iVar5 + iVar14 + 0x4e0);
            if ((uVar8 & 0x100) != 0) goto LAB_00287434;
            uVar8 = ((uVar8 ^ 2) << 0x1e) >> 0x1f;
            if (uVar6 == 0) {
              uVar8 = 1;
            }
            if (uVar8 != 0) goto LAB_00287434;
            while( true ) {
              if ((iVar12 != 0 || iVar7 != 0) && (0x1ff < *(uint *)(iVar18 + 0x285b54))) {
                if (DebugLevel < 3) goto LAB_00287434;
                printk("%s: [band%d] mgmt queue is full, thread dissmised!\n","MT_ATETxHandler",
                       iVar3);
                local_68 = 0;
                goto LAB_00287438;
              }
              if (uVar13 <= uVar17) {
                if (DebugLevel < 3) goto LAB_00287434;
                local_68 = 0;
                printk("%s: [band%d] reach counter(%d), thread dissmised!\n","MT_ATETxHandler",iVar3
                       ,*(byte *)(iVar4 + 0x6f5) * uVar17);
                goto LAB_00287438;
              }
              local_68 = mt_ate_enq_pkt(iVar18,iVar3,*(undefined1 *)(iVar4 + 0x6f6));
              if (local_68 != 0) goto LAB_00287438;
              cVar10 = *(char *)(iVar4 + 0x6f6) + '\x01';
              if (*(short *)(iVar4 + 0x6f8) != 0) {
                *(short *)(iVar4 + 0x6f8) = *(short *)(iVar4 + 0x6f8) + -1;
              }
              *(char *)(iVar4 + 0x6f6) = cVar10;
              if (*(char *)(iVar4 + 0x6f5) == cVar10) {
                uVar17 = uVar17 + 1;
                *(undefined1 *)(iVar4 + 0x6f6) = 0;
              }
              if (iVar12 == 0 && (cVar1 == '\0' || iVar7 == 0)) break;
              uVar16 = hc_get_ct_cb(*(undefined4 *)(iVar18 + 0xa797a0));
              iVar5 = token_tx_get_queue_by_band(uVar16,iVar3);
              iVar15 = *(int *)(iVar5 + 0x10);
              uVar8 = *(uint *)(iVar5 + 0x38);
              uVar6 = hif_get_tx_resource_free_num(*(undefined4 *)(iVar18 + 0xa797a0),uVar2);
              if (((uVar8 <= iVar15 - 100U) || (uVar6 == 0)) || (*(short *)(iVar4 + 0x6f8) == 0))
              break;
            }
            local_58 = local_58 + -1;
            if (3 < DebugLevel) {
              printk("%s:: band_idx:%u, tx_cnt:%u, txed_cnt:%u, deque:%d, multi_user:%u, free:%lu\n"
                     ,"MT_ATETxHandler",iVar3,uVar13,uVar17,local_58,0,uVar6);
            }
          } while (local_58 != 0);
          if (3 < DebugLevel) {
            printk("%s:: Dequeue %d finish, multi_user:%d\n","MT_ATETxHandler",0,0xffffffff);
          }
LAB_00287438:
          iVar4 = net_ad_wrap_service(iVar18);
          *(uint *)(iVar4 + iVar3 * 0xd18 + 0x1120) = uVar17;
          iVar5 = net_ad_wrap_service(iVar18);
          iVar4 = DebugLevel;
          *(uint *)(iVar5 + iVar3 * 0xd18 + 0x1118) = uVar13;
          if (3 < iVar4) {
            printk("%s:: band_idx:%u, tx_cnt:%u, txed_cnt:%u, deque:%d\n","MT_ATETxHandler",iVar3,
                   uVar13,uVar17,local_58);
          }
        } while (bVar9 != 0);
      }
      *(undefined1 *)(iVar18 + 0xa3a050) = 0;
      _raw_spin_unlock_bh(iVar11);
      iVar3 = net_ad_wrap_service(iVar18);
      iVar4 = local_40 * 0xd18;
      if ((*(uint *)(iVar3 + iVar4 + 0x4e0) & 0x40) != 0) {
        iVar3 = net_ad_wrap_service(iVar18);
        uVar17 = *(uint *)(iVar3 + iVar4 + 0x1120);
        iVar3 = net_ad_wrap_service(iVar18);
        uVar13 = *(uint *)(iVar3 + iVar4 + 0x1118);
        iVar3 = net_ad_wrap_service(iVar18);
        iVar3 = iVar3 + iVar4;
        iVar4 = iVar3 + 0x11b4;
        if ((iVar4 == 0) || (*(int *)(iVar3 + 0x11cc) == 0)) {
          if (0 < DebugLevel) {
            printk("%s: mps_cb/mps_setting NULL %p %p\n","MT_ATEMPSRunStatCheck",iVar4,0);
            FUN_00286a70(iVar18,local_40);
            goto LAB_002874c0;
          }
        }
        else {
          uVar6 = *(uint *)(iVar3 + 0x11c8);
          if (uVar17 < uVar13) {
            uVar17 = 0;
          }
          else {
            uVar17 = *(uint *)(iVar3 + 0x11c0) & 1;
          }
          if (uVar17 != 0) {
            if (0 < DebugLevel) {
              printk("%s: MPS Item Finished idx:%d mps_cnt:%d\n","MT_ATEMPSRunStatCheck",uVar6,
                     *(undefined4 *)(iVar3 + 0x11b8));
            }
            OS_SPIN_LOCK(iVar4);
            *(undefined4 *)(iVar3 + 0x11c0) = 0;
            OS_SPIN_UNLOCK(iVar4);
            if (*(uint *)(iVar3 + 0x11b8) < uVar6) {
              iVar5 = net_ad_wrap_service(iVar18);
              iVar4 = DebugLevel;
              uVar17 = *(uint *)(local_40 * 0xd18 + iVar5 + 0x4e0);
              *(undefined1 *)(iVar3 + 0x11c4) = 0;
              if (0 < iVar4) {
                printk("%s: MPS All Finished idx:%d mps_cnt:%d\n","MT_ATEMPSRunStatCheck",uVar6,
                       *(undefined4 *)(iVar3 + 0x11b8));
              }
              iVar3 = net_ad_wrap_service(iVar18);
              *(uint *)(local_40 * 0xd18 + iVar3 + 0x4e0) = uVar17 & 0xffffffbf;
              MT_MPSTxStop(iVar18);
              FUN_00286a70(iVar18,local_40);
              goto LAB_002874c0;
            }
          }
        }
        FUN_00286a70(iVar18,local_40);
      }
LAB_002874c0:
      schedule();
    } while (local_68 == 0);
LAB_002874d0:
    RtmpOSTaskNotifyToExit(param_1);
    if (iVar18 != 0) {
      MtATESetMacTxRx(iVar18,1,1,local_40 & 0xff);
      *(uint *)(iVar18 + 0xa39f84) = *(uint *)(iVar18 + 0xa39f84) & 0xffffffbf;
    }
    if (iVar18 != -0xa3a010) {
      *(undefined1 *)(iVar18 + 0xa3a010) = 0;
    }
    if (local_68 != 0) {
      if (DebugLevel < 0) {
        return local_68;
      }
      printk("%s: abnormal leave err %d\n","TestMode_TxThread",local_68);
      goto LAB_00287798;
    }
  }
  local_68 = 0;
LAB_00287798:
  if (DebugLevel < 4) {
    return local_68;
  }
  printk("%s: leave\n","TestMode_TxThread");
  return local_68;
}

