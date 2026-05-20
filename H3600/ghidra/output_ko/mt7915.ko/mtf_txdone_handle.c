// module: mt7915.ko
// function: mtf_txdone_handle @ 0x1a02b4
// size: 1368 bytes
//

undefined4 mtf_txdone_handle(int param_1,uint *param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  undefined4 *puVar7;
  uint uVar8;
  uint *puVar9;
  uint uVar11;
  int iVar12;
  char local_29 [5];
  uint *puVar10;
  
  uVar1 = hc_get_ct_cb(*(undefined4 *)(param_1 + 0xa797a0));
  uVar5 = (param_2[1] << 0xd) >> 0x1d;
  if (uVar5 == 3) {
    uVar11 = *param_2;
    uVar5 = (uVar11 << 6) >> 0x16;
    if (3 < DebugLevel) {
      printk("%s: rx_byte_cnt = %d,token_cnt = %d, token_cnt = %d\n","mtf_v2_txdone_handle",
             uVar11 & 0xffff,uVar5,uVar5);
    }
    if (uVar11 >> 0x1b == 6) {
      param_2 = param_2 + 2;
      iVar6 = *(int *)("Get_RBIST_Raw_Data_Proc" + param_1 + 0x14);
      if (uVar5 != 0) {
        iVar12 = 0;
        uVar11 = 0;
        do {
          if ((int)*param_2 < 0) {
LAB_001a048c:
            param_2 = param_2 + 1;
          }
          else {
            uVar8 = (*param_2 << 1) >> 0x11;
            uVar11 = uVar11 + 1;
            iVar12 = token_tx_get_queue_by_token_id(uVar1,uVar8);
            *(int *)(iVar12 + 0x44) = *(int *)(iVar12 + 0x44) + 1;
            iVar2 = token_tx_deq(param_1,iVar12,uVar8,local_29);
            if (iVar2 == 0) {
              if (-1 < DebugLevel) {
                printk("%s: Get a token_id[%d] = 0x%x but PktPtr is NULL!\n",
                       "tx_free_v2_notify_handler",uVar11,uVar8);
              }
              goto LAB_001a048c;
            }
            if ((*(uint *)(param_1 + 0xa3ac14) & 1) == 0) {
              if ((*(int *)(param_1 + 0xa77bb4) != 1) ||
                 (puVar7 = *(undefined4 **)(param_1 + 0xa77bb8), (puVar7[0x138] & 1) == 0)) {
                if ((*(byte *)(iVar2 + 0x3a) & 8) != 0) {
                  twtTxDoneCheckSetupFrame(param_1,iVar2);
                }
                if (local_29[0] == '\x01') {
                  RTMPFreeNdisPacketIRQ(param_1,iVar2);
                }
                else {
                  RTMPFreeNdisPacket();
                }
                goto LAB_001a048c;
              }
            }
            else {
              puVar7 = *(undefined4 **)(param_1 + 0xa77bb8);
            }
            if (*(byte *)(iVar2 + 0x2d) < 0x68) {
              iVar3 = HcGetBandByWdev(*(undefined4 *)
                                       (param_1 + (uint)*(byte *)(iVar2 + 0x2d) * 4 + 0xc));
              net_ad_post_tx(*puVar7,puVar7 + iVar3 * 0x346 + 0x138,iVar3,iVar2);
              RTMPFreeNdisPacket(param_1,iVar2);
              goto LAB_001a048c;
            }
          }
        } while (uVar11 < uVar5);
        if ((iVar12 != 0) && (iVar2 = token_tx_get_state(iVar12), iVar2 != 0)) {
          uVar5 = token_tx_get_free_cnt(iVar12);
          uVar11 = token_tx_get_hwmark(iVar12);
          if (uVar11 <= uVar5) {
            token_tx_set_state(iVar12,1);
            (**(code **)(iVar6 + 0x3c))(param_1,*(undefined1 *)(iVar12 + 1));
          }
        }
      }
    }
    else if (0 < DebugLevel) {
      printk("Invalid type(%d)!\n",uVar11 >> 0x1b);
    }
  }
  else if (uVar5 == 2) {
    uVar5 = *param_2;
    uVar11 = (uVar5 << 9) >> 0x19;
    if (3 < DebugLevel) {
      printk("%s: rx_byte_cnt = %d,token_cnt = %d, token_cnt = %d\n","mtf_v1_txdone_handle",
             uVar5 & 0xffff,uVar11,uVar11);
    }
    if (uVar5 >> 0x1b == 6) {
      uVar5 = uVar5 & 0xffff;
      if (uVar11 * 4 + 8 == uVar5) {
        iVar6 = *(int *)("Get_RBIST_Raw_Data_Proc" + param_1 + 0x14);
        if (uVar11 != 0) {
          iVar12 = 0;
          puVar9 = param_2 + 2;
          do {
            puVar10 = puVar9 + 1;
            uVar5 = *puVar9 & 0x7fff;
            iVar2 = token_tx_get_queue_by_token_id(uVar1,uVar5);
            *(int *)(iVar2 + 0x44) = *(int *)(iVar2 + 0x44) + 1;
            iVar3 = token_tx_deq(param_1,iVar2,uVar5,local_29);
            if (iVar3 == 0) {
              if (-1 < DebugLevel) {
                printk("%s: Get a token_id[%d] = 0x%x but PktPtr is NULL!\n",
                       "tx_free_v1_notify_handler",iVar12,uVar5);
              }
            }
            else {
              if ((*(uint *)(param_1 + 0xa3ac14) & 1) == 0) {
                if ((*(int *)(param_1 + 0xa77bb4) != 1) ||
                   (puVar7 = *(undefined4 **)(param_1 + 0xa77bb8), (puVar7[0x138] & 1) == 0)) {
                  if ((*(byte *)(iVar3 + 0x3a) & 8) != 0) {
                    twtTxDoneCheckSetupFrame(param_1,iVar3);
                  }
                  if (local_29[0] == '\x01') {
                    RTMPFreeNdisPacketIRQ(param_1,iVar3);
                  }
                  else {
                    RTMPFreeNdisPacket();
                  }
                  goto LAB_001a0610;
                }
              }
              else {
                puVar7 = *(undefined4 **)(param_1 + 0xa77bb8);
              }
              if (*(byte *)(iVar3 + 0x2d) < 0x68) {
                iVar4 = HcGetBandByWdev(*(undefined4 *)
                                         (param_1 + (uint)*(byte *)(iVar3 + 0x2d) * 4 + 0xc));
                net_ad_post_tx(*puVar7,puVar7 + iVar4 * 0x346 + 0x138,iVar4,iVar3);
                RTMPFreeNdisPacket(param_1,iVar3);
              }
            }
LAB_001a0610:
            iVar12 = iVar12 + 1;
            puVar9 = puVar10;
          } while (puVar10 != param_2 + uVar11 + 2);
          if ((iVar2 != 0) && (iVar12 = token_tx_get_state(iVar2), iVar12 != 0)) {
            uVar5 = token_tx_get_free_cnt(iVar2);
            uVar11 = token_tx_get_hwmark(iVar2);
            if (uVar11 <= uVar5) {
              token_tx_set_state(iVar2,1);
              (**(code **)(iVar6 + 0x3c))(param_1,*(undefined1 *)(iVar2 + 1));
            }
          }
        }
      }
      else {
        if (0 < DebugLevel) {
          printk("token_cnt(%d) and rx_byte_cnt(%d) mismatch!\n",uVar11,uVar5);
        }
        hex_dump("TxFreeNotifyEventMisMatchFrame",param_2,uVar5);
      }
    }
    else if (0 < DebugLevel) {
      printk("Invalid type(%d)!\n",uVar5 >> 0x1b);
    }
  }
  else if (0 < DebugLevel) {
    printk("invalid txdone version(%d)!\n");
  }
  return 1;
}

