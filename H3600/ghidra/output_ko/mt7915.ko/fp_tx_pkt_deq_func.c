// module: mt7915.ko
// function: fp_tx_pkt_deq_func @ 0xd4938
// size: 1648 bytes
//

void fp_tx_pkt_deq_func(int param_1,int param_2)

{
  char cVar1;
  ushort uVar2;
  uint uVar3;
  byte bVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  undefined4 uVar12;
  byte local_1c0;
  undefined1 local_1bf;
  undefined1 local_1bd;
  undefined1 local_1bc;
  undefined1 local_1bb;
  undefined2 local_1ba;
  int local_1b8;
  int local_1b4;
  int local_1b0;
  undefined4 local_168;
  int local_5c;
  int local_58;
  int local_54;
  uint local_50;
  uint local_4c;
  int local_48;
  int local_44;
  int local_40;
  uint local_3c;
  int local_38;
  int local_34;
  ushort *local_30;
  uint local_2c;
  
  local_30 = *(ushort **)(param_1 + 0x285ae8);
  cVar1 = *(char *)(param_1 + param_2 + 0x285bac);
  local_38 = param_2;
  local_50 = hif_get_tx_res_num(*(undefined4 *)(param_1 + 0xa797a0));
  local_4c = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if ((*(uint *)(param_1 + 0xa39f84) & 0x804140) == 0) {
    iVar8 = param_1 + local_38 * 0x10;
    if (*(int *)(iVar8 + 0x285b54) != 0) {
      iVar10 = param_1 + local_38 * 4 + 0x285b3c;
      OS_SPIN_LOCK_BH(iVar10);
      if (*(int *)(iVar8 + 0x285b74) == 0) {
        iVar5 = param_1 + local_38 * 0x10;
        *(undefined4 *)(iVar5 + 0x285b6c) = *(undefined4 *)(iVar5 + 0x285b4c);
        *(undefined4 *)(iVar5 + 0x285b70) = *(undefined4 *)(iVar5 + 0x285b50);
        *(undefined4 *)(iVar8 + 0x285b74) = *(undefined4 *)(iVar8 + 0x285b54);
      }
      else if (*(int *)(iVar8 + 0x285b54) != 0) {
        iVar5 = param_1 + local_38 * 0x10;
        **(undefined4 **)(iVar5 + 0x285b70) = *(undefined4 *)(iVar5 + 0x285b4c);
        *(undefined4 *)(iVar5 + 0x285b70) = *(undefined4 *)(iVar5 + 0x285b50);
        *(int *)(iVar8 + 0x285b74) = *(int *)(iVar8 + 0x285b54) + *(int *)(iVar8 + 0x285b74);
      }
      iVar5 = param_1 + local_38 * 0x10;
      *(undefined4 *)(iVar8 + 0x285b78) = *(undefined4 *)(iVar8 + 0x285b58);
      *(undefined4 *)(iVar5 + 0x285b4c) = 0;
      *(undefined4 *)(iVar5 + 0x285b50) = 0;
      *(undefined4 *)(iVar8 + 0x285b54) = 0;
      OS_SPIN_UNLOCK_BH(iVar10);
    }
    if (*(int *)(iVar8 + 0x285af4) != 0) {
      iVar10 = param_1 + local_38 * 4 + 0x285b2c;
      OS_SPIN_LOCK_BH(iVar10);
      if (*(int *)(iVar8 + 0x285b14) == 0) {
        iVar5 = param_1 + local_38 * 0x10;
        *(undefined4 *)(iVar5 + 0x285b0c) = *(undefined4 *)(iVar5 + 0x285aec);
        *(undefined4 *)(iVar5 + 0x285b10) = *(undefined4 *)(iVar5 + 0x285af0);
        *(undefined4 *)(iVar8 + 0x285b14) = *(undefined4 *)(iVar8 + 0x285af4);
      }
      else if (*(int *)(iVar8 + 0x285af4) != 0) {
        iVar5 = param_1 + local_38 * 0x10;
        **(undefined4 **)(iVar5 + 0x285b10) = *(undefined4 *)(iVar5 + 0x285aec);
        *(undefined4 *)(iVar5 + 0x285b10) = *(undefined4 *)(iVar5 + 0x285af0);
        *(int *)(iVar8 + 0x285b14) = *(int *)(iVar8 + 0x285af4) + *(int *)(iVar8 + 0x285b14);
      }
      iVar5 = param_1 + local_38 * 0x10;
      *(undefined4 *)(iVar8 + 0x285b18) = *(undefined4 *)(iVar8 + 0x285af8);
      *(undefined4 *)(iVar5 + 0x285aec) = 0;
      *(undefined4 *)(iVar5 + 0x285af0) = 0;
      *(undefined4 *)(iVar8 + 0x285af4) = 0;
      OS_SPIN_UNLOCK_BH(iVar10);
    }
    if ((cVar1 != '\0') && (*local_30 != 0)) {
      local_54 = local_38 * 0x10;
      local_44 = param_1 + local_54;
      local_48 = param_1 + (local_38 + 0xa16cc) * 4;
      local_58 = local_44 + 0x285b68;
      local_2c = 0;
      local_3c = 0;
      do {
        __memzero(&local_1c0,0xc0);
        if (*(int *)(iVar8 + 0x285b74) == 0) {
LAB_000d4b10:
          if (*(int *)(iVar8 + 0x285b14) == 0) break;
          iVar5 = local_48 + 4;
          OS_SPIN_LOCK_BH(iVar5);
          iVar10 = *(int *)(local_44 + 0x285b0c);
          OS_SPIN_UNLOCK_BH(iVar5);
          if (iVar10 == 0) break;
        }
        else {
          iVar5 = param_1 + local_38 * 4 + 0x285b44;
          OS_SPIN_LOCK_BH(iVar5);
          iVar10 = *(int *)(local_58 + 4);
          OS_SPIN_UNLOCK_BH(iVar5);
          if (iVar10 == 0) goto LAB_000d4b10;
        }
        iVar10 = wdev_search_by_pkt(param_1,iVar10);
        if (iVar10 == 0) {
          uVar6 = FUN_000d38d0(param_1,local_38);
          RTMPFreeNdisPacket(param_1,uVar6);
        }
        else {
          local_34 = *(int *)(iVar10 + 0x904);
          bVar4 = hif_get_resource_idx(*(undefined4 *)(param_1 + 0xa797a0),iVar10,0,0);
          local_1c0 = bVar4;
          local_40 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
          uVar12 = *(undefined4 *)(local_40 + 0x94);
          uVar6 = HcGetBandByWdev(iVar10);
          uVar6 = token_tx_get_queue_by_band(uVar12,uVar6);
          iVar5 = asic_check_hw_resource(param_1,iVar10,bVar4);
          if (iVar5 == 1) {
            hif_free_txd(param_1,bVar4);
            local_5c = asic_check_hw_resource(param_1,iVar10,bVar4);
            if (local_5c == 1) break;
            pci_set_resource_state(param_1,bVar4,1);
            iVar5 = local_5c;
          }
          if (iVar5 == 3) {
            pci_rx_event_dma_done_handle(param_1,*(undefined1 *)(local_40 + 0x98));
            local_40 = asic_check_hw_resource(param_1,iVar10,bVar4);
            if (local_40 == 3) break;
            token_tx_set_state(uVar6,1);
            iVar5 = local_40;
          }
          if (iVar5 != 0) break;
          iVar5 = FUN_000d38d0(param_1,local_38);
          uVar2 = *(ushort *)(iVar5 + 0x42);
          if (uVar2 < local_4c) {
            if ((*(byte *)(iVar5 + 0x3a) & 8) == 0) {
              iVar7 = param_1 + 0x9d000 + local_54;
              *(int *)(iVar7 + 0xcb0) = *(int *)(iVar7 + 0xcb0) + 1;
            }
            local_1bf = *(undefined1 *)(iVar5 + 0x4d);
            local_1ba = (undefined2)*(undefined4 *)(iVar5 + 100);
            local_1b8 = param_1 + (uint)uVar2 * 0x620 + 0x2f6a0;
            local_1bd = 1;
            local_1bc = 1;
            local_1b4 = iVar5;
            local_1b0 = iVar10;
            local_1bb = tx_pkt_classification(param_1,iVar5,&local_1c0);
            local_168 = hif_get_tx_buf(*(undefined4 *)(param_1 + 0xa797a0),&local_1c0,local_1c0);
            iVar10 = (**(code **)(local_34 + 0x14))(param_1,iVar10,&local_1c0);
            if (iVar10 == 0) {
              local_3c = local_3c | 1 << local_1c0;
            }
            local_2c = local_2c + 1 & 0xffff;
          }
          else {
            if (3 < DebugLevel) {
              printk("%s(): WCID is invalid\n","fp_tx_pkt_deq_func");
            }
            *(int *)(param_1 + 0x9db70) = *(int *)(param_1 + 0x9db70) + 1;
            wlan_dbg_set_last_error(0,0,0x1d8,"fp_tx_pkt_deq_func");
            RTMPFreeNdisPacket(param_1,iVar5);
          }
        }
      } while (local_2c < *local_30);
      uVar3 = local_50;
      if (local_3c != 0 && local_50 != 0) {
        uVar9 = 0;
        uVar11 = local_3c;
        do {
          if ((uVar11 & 1) != 0) {
            hif_kickout_data_tx(param_1,&local_1c0,uVar9);
          }
          uVar11 = uVar11 >> 1;
          uVar9 = uVar9 + 1 & 0xff;
        } while (uVar9 < uVar3 && uVar11 != 0);
      }
    }
  }
  return;
}

