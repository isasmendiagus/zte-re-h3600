// module: mt7915.ko
// function: ge_tx_pkt_deq_func @ 0xd0ec4
// size: 1904 bytes
//

void ge_tx_pkt_deq_func(int param_1)

{
  undefined1 uVar1;
  ushort uVar2;
  int *piVar3;
  char cVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  int *piVar9;
  uint uVar10;
  int iVar11;
  int *piVar12;
  sbyte local_1e0;
  undefined1 local_1df;
  char local_1dd;
  undefined1 local_1dc;
  char local_1db;
  undefined2 local_1da;
  int local_1d8;
  int *local_1d4;
  int local_1d0;
  int *local_1c8;
  int *local_1a0;
  int *local_19c;
  int local_198;
  undefined4 local_188;
  int local_90;
  uint local_8c;
  uint local_88;
  int local_84;
  undefined4 local_80;
  int local_7c;
  int local_78;
  int *local_74;
  int *local_70;
  int local_6c;
  int *local_64;
  undefined4 local_60;
  int local_5c;
  undefined4 local_54;
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
  
  local_6c = param_1 + 0xa79000;
  local_80 = *(undefined4 *)(param_1 + 0xa18f8);
  local_54 = 0;
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_7c = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  local_88 = hif_get_tx_res_num(*(undefined4 *)(param_1 + 0xa797a0));
  local_84 = *(int *)("Get_RBIST_Raw_Data_Proc" + param_1 + 0x14);
  if (((*(uint *)(param_1 + 0xa39f84) & 0x804140) != 0) ||
     (local_8c = IsStopingPdma(param_1 + 0xa7bf04), local_8c != 0)) {
    return;
  }
  local_50 = CONCAT13(local_50._3_1_,0x47fff);
  local_90 = param_1 + 0x285bac;
  piVar9 = (int *)(param_1 + 0x285b3c);
  __memzero(&local_64,0x10);
  local_78 = param_1 + 0x285b98;
  local_70 = &DebugLevel;
LAB_000d0ffc:
  if (local_90 == 0) {
LAB_000d1548:
    uVar6 = local_88;
    if (local_8c == 0) {
      return;
    }
    if (local_88 == 0) {
      return;
    }
    uVar10 = 0;
    uVar8 = local_8c;
    while( true ) {
      if ((uVar8 & 1) != 0) {
        hif_kickout_data_tx(param_1,&local_1e0,uVar10 & 0xff);
      }
      uVar8 = uVar8 >> 1;
      uVar10 = uVar10 + 1;
      if (uVar8 == 0) break;
      if (uVar10 == uVar6) {
        return;
      }
    }
    return;
  }
LAB_000d1010:
  __memzero(&local_1e0,0x140);
  while( true ) {
    _raw_spin_lock_bh(piVar9);
    iVar11 = *(int *)(param_1 + 0x285b4c);
    _raw_spin_unlock_bh(piVar9);
    iVar7 = local_78;
    if (iVar11 == 0) break;
    iVar5 = wdev_search_by_pkt(param_1,iVar11);
    local_1e0 = hif_get_resource_idx
                          (*(undefined4 *)(local_6c + 0x7a0),iVar5,(int)*(char *)(iVar11 + 0x4f),
                           *(undefined1 *)(iVar11 + 0x4d));
    iVar11 = asic_check_hw_resource(param_1,iVar5);
    iVar7 = local_78;
    if (iVar11 != 0) break;
    _raw_spin_lock_bh(piVar9);
    piVar12 = *(int **)(param_1 + 0x285b4c);
    if (piVar12 == (int *)0x0) {
      _raw_spin_unlock_bh(piVar9);
      iVar7 = local_78;
      break;
    }
    iVar7 = *piVar12;
    *piVar12 = 0;
    *(int *)(param_1 + 0x285b4c) = iVar7;
    if (iVar7 == 0) {
      *(undefined4 *)(param_1 + 0x285b50) = 0;
    }
    *(int *)(param_1 + 0x285b54) = *(int *)(param_1 + 0x285b54) + -1;
    _raw_spin_unlock_bh(piVar9);
    uVar2 = *(ushort *)((int)piVar12 + 0x42);
    uVar6 = hc_get_chip_wtbl_max_num(*(undefined4 *)(local_6c + 0x7a0));
    if (uVar2 < uVar6) {
      if (iVar5 != 0) {
        local_1df = *(undefined1 *)((int)piVar12 + 0x4d);
        local_1da = (undefined2)piVar12[0x19];
        local_1d8 = param_1 + (uint)uVar2 * 0x620 + 0x2f6a0;
        local_1dd = '\x01';
        local_1dc = 1;
        local_1d4 = piVar12;
        local_1d0 = iVar5;
        local_1db = tx_pkt_classification(param_1,piVar12,&local_1e0);
        local_188 = hif_get_tx_buf(*(undefined4 *)(local_6c + 0x7a0),&local_1e0,local_1e0);
        *piVar12 = 0;
        piVar3 = piVar12;
        if (local_19c != (int *)0x0) {
          *local_19c = (int)piVar12;
          piVar3 = local_1a0;
        }
        local_1a0 = piVar3;
        local_198 = local_198 + 1;
        local_19c = piVar12;
        goto LAB_000d1198;
      }
    }
    else if (3 < *local_70) {
      printk("%s(): WCID is invalid\n","ge_deq_mgmt_pkt");
    }
    RTMPFreeNdisPacket(param_1,piVar12);
  }
  do {
    local_74 = piVar9;
    _raw_spin_lock_bh(iVar7);
    iVar11 = *(int *)(param_1 + 0x285b9c);
    _raw_spin_unlock_bh(iVar7);
    piVar9 = local_74;
    if (iVar11 == 0) break;
    iVar5 = wdev_search_by_pkt(param_1,iVar11);
    local_1df = *(undefined1 *)(iVar11 + 0x4d);
    local_1e0 = hif_get_resource_idx(*(undefined4 *)(local_6c + 0x7a0),iVar5,1,local_1df);
    iVar11 = asic_check_hw_resource(param_1,iVar5);
    piVar9 = local_74;
    if (iVar11 != 0) break;
    _raw_spin_lock_bh(iVar7);
    piVar9 = local_74;
    piVar12 = *(int **)(param_1 + 0x285b9c);
    if (piVar12 == (int *)0x0) {
      _raw_spin_unlock_bh(local_78);
      break;
    }
    iVar11 = *piVar12;
    *piVar12 = 0;
    *(int *)(param_1 + 0x285b9c) = iVar11;
    if (iVar11 == 0) {
      *(undefined4 *)(param_1 + 0x285ba0) = 0;
    }
    *(int *)(param_1 + 0x285ba4) = *(int *)(param_1 + 0x285ba4) + -1;
    _raw_spin_unlock_bh(iVar7);
    uVar2 = *(ushort *)((int)piVar12 + 0x42);
    uVar6 = hc_get_chip_wtbl_max_num(*(undefined4 *)(local_6c + 0x7a0));
    piVar9 = local_74;
    if (uVar2 < uVar6) {
      if (iVar5 != 0) {
        local_1df = *(undefined1 *)((int)piVar12 + 0x4d);
        local_1c8 = (int *)((uint)local_1c8 | 0x4000000);
        local_1d8 = param_1 + (uint)uVar2 * 0x620 + 0x2f6a0;
        local_1da = (undefined2)piVar12[0x19];
        local_1dd = '\x01';
        local_1dc = 1;
        local_1d4 = piVar12;
        local_1d0 = iVar5;
        local_74 = piVar12;
        local_1db = tx_pkt_classification(param_1,piVar12,&local_1e0);
        local_188 = hif_get_tx_buf(*(undefined4 *)(local_6c + 0x7a0),&local_1e0,local_1e0);
        piVar12 = local_1c8;
        if ((((uint)local_1c8 & 0x10000000) != 0) &&
           (iVar7 = FUN_000cfd30(param_1,local_1d4,&local_1e0), iVar7 == 0)) {
          local_1c8 = (int *)((uint)piVar12 & 0xefffffff);
        }
        *local_74 = 0;
        piVar12 = local_74;
        if (local_19c != (int *)0x0) {
          *local_19c = (int)local_74;
          piVar12 = local_1a0;
        }
        local_1a0 = piVar12;
        local_198 = local_198 + 1;
        local_19c = local_74;
        if (local_198 == 1 && local_1db == '\x04') {
          local_1db = '\x02';
        }
        goto LAB_000d1198;
      }
    }
    else if (3 < *local_70) {
      printk("%s(): WCID is invalid\n","ge_deq_high_prio_pkt");
    }
    RTMPFreeNdisPacket(param_1,piVar12);
    piVar9 = local_74;
  } while( true );
  if (*(char *)(local_7c + 0x159) == '\x02') {
    piVar12 = local_64;
    if (local_64 == (int *)0x0) {
      __memzero(&local_64,0x10);
      iVar7 = (**(code **)(local_84 + 0x48))(param_1,local_80,&local_54,&local_64);
      if (iVar7 == 0) goto LAB_000d1548;
      piVar12 = local_64;
      if (local_64 == (int *)0x0) goto LAB_000d1198;
    }
    local_64 = (int *)*piVar12;
    uVar1 = *(undefined1 *)((int)piVar12 + 0x4d);
    *piVar12 = 0;
    if (local_64 == (int *)0x0) {
      local_60 = 0;
    }
    local_5c = local_5c + -1;
    local_1df = uVar1;
    local_1d0 = wdev_search_by_pkt(param_1,piVar12);
    iVar7 = param_1 + (uint)*(ushort *)((int)piVar12 + 0x42) * 0x620;
    local_1d8 = iVar7 + 0x2f6a0;
    iVar7 = *(int *)(iVar7 + 0x2f6a4);
    if (local_1d0 != iVar7) {
      local_1d0 = iVar7;
    }
    local_1e0 = hif_get_resource_idx(*(undefined4 *)(local_6c + 0x7a0),iVar7,0,uVar1);
    cVar4 = tx_pkt_classification(param_1,piVar12,&local_1e0);
    local_1db = cVar4;
    if (((uint)local_1c8 & 0x10000000) != 0) {
      local_74 = local_1c8;
      iVar7 = FUN_000cfd30(param_1,piVar12,&local_1e0);
      if (iVar7 == 0) {
        local_1c8 = (int *)((uint)local_74 & 0xefffffff);
      }
    }
    local_1dc = *(undefined1 *)((int)piVar12 + 0x2b);
    local_1da = (undefined2)piVar12[0x19];
    local_1dd = '\x01';
    local_1d4 = piVar12;
    local_188 = hif_get_tx_buf(*(undefined4 *)(local_6c + 0x7a0),&local_1e0,local_1e0,cVar4);
    *piVar12 = 0;
    piVar3 = piVar12;
    if (local_19c != (int *)0x0) {
      *local_19c = (int)piVar12;
      piVar3 = local_1a0;
    }
    local_1a0 = piVar3;
    local_198 = local_198 + 1;
    local_19c = piVar12;
  }
  else {
    iVar7 = (**(code **)(local_84 + 0x44))(param_1,&local_1e0,local_80,&local_54);
    if (iVar7 != 0) goto LAB_000d1548;
  }
LAB_000d1198:
  if (local_1dd != '\0') goto code_r0x000d11a4;
  goto LAB_000d1010;
code_r0x000d11a4:
  if (local_1d0 == 0) {
    printk(&_LC24,0x81a);
    dump_stack();
    if (local_1d0 == 0) goto LAB_000d11c4;
  }
  (**(code **)(*(int *)(local_1d0 + 0x904) + 0x14))(param_1,local_1d0,&local_1e0);
LAB_000d11c4:
  local_8c = local_8c | 1 << local_1e0;
  goto LAB_000d0ffc;
}

