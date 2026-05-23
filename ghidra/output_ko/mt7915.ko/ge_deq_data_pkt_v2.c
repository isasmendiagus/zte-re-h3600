// module: mt7915.ko
// function: ge_deq_data_pkt_v2 @ 0xd163c
// size: 1288 bytes
//

void ge_deq_data_pkt_v2(int param_1,undefined2 param_2,char *param_3,undefined4 *param_4)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  uint uVar6;
  uint *puVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  uint *puVar11;
  uint *local_30;
  uint local_2c [2];
  
  local_30 = (uint *)0x0;
  local_2c[0] = 0;
  hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (*param_3 == '\0') {
    *(undefined2 *)(param_3 + 10) = param_2;
    *(undefined2 *)(param_3 + 0xc) = param_2;
    *(undefined2 *)(param_3 + 0xe) = param_2;
    *(undefined2 *)(param_3 + 0x10) = param_2;
    *param_3 = '\x01';
  }
  uVar6 = 3;
  do {
    if (*(short *)(param_1 + (*(int *)(param_1 + uVar6 * 0x4018 + 0x28a350) + uVar6 * 0x200c +
                             0x1431a4) * 2 + 4) != 0) {
      uVar1 = hif_get_resource_idx(*(undefined4 *)(param_1 + 0xa797a0),0,0,uVar6);
      puVar11 = local_2c;
      iVar2 = mt_ct_get_hw_resource_free_num(param_1,0,uVar1,&local_30,puVar11);
      if (iVar2 == 3) {
        hif_free_txd(param_1,uVar1);
        puVar11 = local_2c;
        iVar2 = mt_ct_get_hw_resource_free_num(param_1,0,uVar1,&local_30,puVar11);
        pci_dec_resource_full_cnt(param_1,uVar1);
        if (iVar2 != 0) goto LAB_000d19cc;
        asic_set_resource_state(param_1,uVar1,1);
      }
      else if (iVar2 != 0) {
LAB_000d19cc:
        (param_3 + (uVar6 + 4) * 2 + 2)[0] = '\0';
        (param_3 + (uVar6 + 4) * 2 + 2)[1] = '\0';
        goto LAB_000d16c0;
      }
      if (((*(short *)(param_3 + uVar6 * 2 + 10) != 0) && (local_30 != (uint *)0x0)) &&
         ((uint)param_4[2] < local_2c[0])) {
        iVar2 = param_1 + uVar6 * 0x4018;
        uVar9 = (uint)*(ushort *)
                       (param_1 + (*(int *)(iVar2 + 0x28a350) + uVar6 * 0x200c + 0x1431a4) * 2 + 4);
        if (uVar9 == 0) {
          if (4 < DebugLevel) {
            puVar7 = (uint *)0x0;
            goto LAB_000d1b2c;
          }
        }
        else {
          iVar8 = param_1 + uVar6 * 4 + 0x28633c;
          puVar7 = (uint *)0x0;
          do {
            if (3 < DebugLevel) {
              puVar11 = puVar7;
              printk("%s(): deq_info:cur_wcid=%d, cur_qidx=%d, pkt_cnt=%d\n","ge_deq_data_pkt_v2",
                     uVar9,uVar6,puVar7);
            }
            iVar10 = param_1 + (uVar6 + uVar9 * 0x188) * 4 + 0x2f734;
            _raw_spin_lock_bh(iVar10);
            iVar4 = param_1 + (uVar6 + uVar9 * 0x62) * 0x10;
            piVar5 = *(int **)(iVar4 + 0x2f6c4);
            if (piVar5 == (int *)0x0) {
              _raw_spin_unlock_bh(iVar10);
            }
            else {
              iVar3 = *piVar5;
              *piVar5 = 0;
              *(int *)(iVar4 + 0x2f6c4) = iVar3;
              if (iVar3 == 0) {
                *(undefined4 *)(iVar4 + 0x2f6c8) = 0;
              }
              iVar3 = param_1 + uVar9 * 0x620;
              iVar4 = param_1 + (uVar6 + uVar9 * 0x62) * 0x10;
              *(int *)(iVar4 + 0x2f6cc) = *(int *)(iVar4 + 0x2f6cc) + -1;
              *(int *)(iVar3 + 0x2f714) = *(int *)(iVar3 + 0x2f714) + -1;
              _raw_spin_unlock_bh(iVar10);
              if (*(ushort *)((int)piVar5 + 0x42) != uVar9) {
                printk(&_LC27,0x6c6,piVar5,(uint)*(ushort *)((int)piVar5 + 0x42),puVar11);
                dump_stack();
              }
              *piVar5 = 0;
              puVar7 = (uint *)((int)puVar7 + 1);
              if ((undefined4 *)param_4[1] == (undefined4 *)0x0) {
                *param_4 = piVar5;
              }
              else {
                *(undefined4 *)param_4[1] = piVar5;
              }
              param_4[1] = piVar5;
              param_4[2] = param_4[2] + 1;
              *(short *)(param_3 + uVar6 * 2 + 10) = *(short *)(param_3 + uVar6 * 2 + 10) + -1;
            }
            _raw_spin_lock_bh(iVar8);
            *(undefined2 *)
             (param_1 + (uVar6 * 0x200c + *(int *)(iVar2 + 0x28a350) + 0x1431a4) * 2 + 4) = 0;
            uVar9 = *(int *)(iVar2 + 0x28a350) + 1;
            if (0x1fff < uVar9) {
              uVar9 = 0;
            }
            *(uint *)(iVar2 + 0x28a350) = uVar9;
            _raw_spin_unlock_bh(iVar8);
            if (((*(short *)(param_3 + uVar6 * 2 + 10) == 0) || (local_30 <= puVar7)) ||
               (local_2c[0] <= (uint)param_4[2])) {
              if (puVar7 == (uint *)0x0) goto LAB_000d16c0;
              goto LAB_000d1a08;
            }
            uVar9 = (uint)*(ushort *)
                           (param_1 + (uVar6 * 0x200c + *(int *)(iVar2 + 0x28a350) + 0x1431a4) * 2 +
                           4);
          } while (uVar9 != 0);
          if (4 < DebugLevel) {
LAB_000d1b2c:
            printk("%s():tx_swq[%d] emtpy!\n","ge_deq_data_pkt_v2",uVar6);
          }
          if (puVar7 != (uint *)0x0) {
            iVar8 = param_1 + uVar6 * 4 + 0x28633c;
LAB_000d1a08:
            _raw_spin_lock_bh(iVar8);
            iVar2 = tx_flow_check_state(param_1,1,uVar6);
            if (iVar2 != 0) {
              iVar4 = param_1 + uVar6 * 0x4018;
              iVar2 = *(int *)(iVar4 + 0x28a34c);
              iVar4 = *(int *)(iVar4 + 0x28a350);
              if (iVar2 < iVar4) {
                iVar2 = -iVar2;
              }
              else {
                iVar2 = 0x2000 - iVar2;
              }
              if (*(uint *)(param_1 + uVar6 * 0x4018 + 0x28a358) < (uint)(iVar4 + iVar2)) {
                tx_flow_set_state_block(param_1,0,1,0,uVar6);
              }
            }
            _raw_spin_unlock_bh(iVar8);
            goto LAB_000d16c0;
          }
        }
        (param_3 + uVar6 * 2 + 10)[0] = '\0';
        (param_3 + uVar6 * 2 + 10)[1] = '\0';
      }
    }
LAB_000d16c0:
    uVar6 = uVar6 - 1 & 0xff;
  } while( true );
}

