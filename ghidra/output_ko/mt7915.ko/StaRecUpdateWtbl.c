// module: mt7915.ko
// function: StaRecUpdateWtbl @ 0x1c51b0
// size: 1780 bytes
//

undefined4 StaRecUpdateWtbl(int param_1,undefined4 param_2,char *param_3)

{
  byte bVar1;
  undefined2 uVar2;
  byte bVar3;
  bool bVar4;
  undefined1 *puVar5;
  byte bVar6;
  undefined4 uVar7;
  undefined1 uVar8;
  byte bVar9;
  int iVar10;
  int *piVar12;
  int iVar13;
  int iVar14;
  byte local_8d;
  undefined1 *local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  uint local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  uint local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  uint local_50;
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
  uint3 local_24;
  undefined1 uStack_21;
  uint uVar11;
  
  iVar13 = *(int *)(param_3 + 0x9c);
  local_8c = (undefined1 *)0x0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  _local_24 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_84 = 0;
  local_80 = 0;
  local_7c = 0;
  local_78 = 0;
  local_74 = 0;
  local_70 = 0;
  local_6c = 0;
  local_68 = 0;
  local_64 = 0;
  local_60 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_5c = 0;
  local_58 = 0;
  local_54 = 0;
  local_50 = 0;
  local_88 = 0;
  local_8d = 0;
  os_alloc_mem(param_1,&local_8c,0xfc);
  if (local_8c == (undefined1 *)0x0) {
    return 0xffffffff;
  }
  os_zero_mem(local_8c,0xfc);
  local_8c[1] = 0;
  *local_8c = 0xd;
  local_8c[3] = 0;
  local_8c[2] = 0xfc;
  if (*(int *)(param_3 + 8) != 0x10020) {
    local_48._0_3_ = CONCAT12(1,(undefined2)local_48);
    local_48 = CONCAT13(1,(undefined3)local_48);
    if (iVar13 == 0) {
      if (-1 < DebugLevel) {
        printk("\n\nERROR%s: No MacEntry. widx=%d ConnTyp=0x%x feat=0x%x\n\n\n","StaRecUpdateWtbl",
               *(undefined2 *)(param_3 + 2),*(int *)(param_3 + 8),*(undefined4 *)(param_3 + 0xc));
      }
      os_free_mem(local_8c);
      return 0xffffffff;
    }
    iVar14 = *(int *)(iVar13 + 8);
    _local_24 = CONCAT22(stack0xffffffde,*(undefined2 *)(iVar13 + 0xf8));
    local_28 = CONCAT22(local_28._2_2_,
                        CONCAT11((char)*(undefined4 *)(iVar13 + 0xb4),(undefined1)local_28)) &
               0xffff01ff;
    local_2c._0_3_ = CONCAT12(param_3[5],(undefined2)local_2c);
    os_move_mem(&local_30,(void *)(iVar13 + 0xec),6);
    iVar10 = *(int *)(iVar14 + 0x14);
    if ((*(uint *)(iVar13 + 0xb4) & 0x100200) == 0x100200) {
      _local_24 = CONCAT13(1,local_24);
    }
    if (iVar10 == 2 || iVar10 == 0x100) {
      local_48._0_2_ = CONCAT11(1,(undefined1)local_48);
      local_68 = CONCAT22(local_68._2_2_,1);
    }
    else if (iVar10 == 1) {
      local_68 = CONCAT22(local_68._2_2_,0x100);
    }
    else if (iVar10 == 8) {
      local_68 = CONCAT31(CONCAT21(local_68._2_2_,1),1);
    }
    else if (-1 < DebugLevel) {
      printk("%s: Unknown wdev type(%d) do not support header translation\n","StaRecUpdateWtbl",
             *(undefined4 *)(*(int *)(iVar13 + 8) + 0x14));
    }
    if ((*(char *)(iVar13 + 0xe8) != '\0') && (*(int *)(iVar14 + 0x14) == 2)) {
      local_68 = CONCAT31(CONCAT21(local_68._2_2_,1),1);
    }
    uVar11 = *(uint *)(iVar13 + 0x2c4) & 0x10;
    uVar8 = (undefined1)uVar11;
    bVar6 = *(byte *)(iVar13 + 0xbf) >> 5;
    if (uVar11 != 0) {
      uVar8 = 1;
    }
    local_68._0_3_ = CONCAT12(uVar8,(undefined2)local_68);
    if (bVar6 < 2) {
      local_70 = (uint)local_70._1_3_ << 8;
      local_38 = (uint)CONCAT21(local_38._2_2_,(char)*(undefined2 *)(param_1 + 0xa78698)) << 8;
    }
    else {
      local_28._0_2_ = CONCAT11(1,(undefined1)local_28);
      local_80 = CONCAT13(*(undefined1 *)(iVar13 + 0xd04),
                          CONCAT12(*(undefined1 *)(iVar13 + 0xd05),(undefined2)local_80));
      local_80 = CONCAT31(local_80._1_3_,1);
      local_24 = (uint3)(ushort)local_24;
      if ((*(uint *)(iVar13 + 0xb4) & 0x200) != 0) {
        local_60 = CONCAT22(local_60._2_2_,0x100);
        uVar11 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
        local_60 = CONCAT31(local_60._1_3_,
                            uVar11 == 0x7915 ||
                            (uVar11 == 0x6867 ||
                            (uVar11 == 0x7663 ||
                            (uVar11 == 0x6632 ||
                            (uVar11 == 0x7615 ||
                            (*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xfffb) == 0x7622
                            ))))) ^ 1;
      }
      local_58 = CONCAT31(local_58._1_3_,*(char *)(iVar13 + 0xd10) == '\x01');
      if ((bVar6 < 4) || ((*(uint *)(iVar13 + 100) & 8) != 0)) {
        local_70 = (uint)local_70._1_3_ << 8;
        local_38 = (uint)CONCAT21(local_38._2_2_,(char)*(undefined2 *)(param_1 + 0xa78698)) << 8;
      }
      else {
        iVar10 = wlan_config_get_vht_bw_sig(*(undefined4 *)(iVar13 + 8));
        uVar7 = local_78;
        if (iVar10 == 2) {
          local_78._0_2_ = CONCAT11(1,(byte)local_78);
        }
        else {
          local_78._0_2_ = (ushort)(byte)local_78;
        }
        bVar6 = *(byte *)(iVar13 + 0xbf) >> 5;
        local_78._3_1_ = SUB41(uVar7,3);
        local_78._0_3_ = CONCAT12(1,(ushort)local_78);
        local_70 = local_70 & 0xffffff00;
        local_38 = (uint)CONCAT21(local_38._2_2_,(char)*(undefined2 *)(param_1 + 0xa78698)) << 8;
        if (bVar6 < 2) goto LAB_001c54b0;
      }
      bVar1 = *(byte *)(param_1 + 0x794ccd);
      bVar9 = bVar1 & 4;
      bVar3 = bVar9;
      if ((bVar1 & 4) != 0) {
        bVar3 = (byte)(((uint)*(byte *)(iVar13 + 0xc3d) << 0x1e) >> 0x1f);
      }
      if (*(int *)(param_1 + 0x79599c) == 0) {
        local_3c._0_2_ = (ushort)bVar3;
      }
      else {
        local_3c = CONCAT22(local_3c._2_2_,CONCAT11(*(undefined1 *)(iVar13 + 0xc3d),bVar3)) &
                   0xffff01ff;
      }
      if (3 < bVar6) {
        if ((bVar1 & 4) != 0) {
          bVar9 = (byte)(((uint)*(byte *)(iVar13 + 0xc3d) << 0x1e) >> 0x1f);
        }
        local_3c._0_3_ = CONCAT12(bVar9,(ushort)local_3c);
        if (*(int *)(param_1 + 0x79599c) == 0) {
          local_3c = (uint)(uint3)local_3c;
        }
        else {
          local_3c = CONCAT13(*(undefined1 *)(iVar13 + 0xc3d),(uint3)local_3c) & 0x1ffffff;
        }
      }
    }
    goto LAB_001c54b0;
  }
  local_48._0_3_ = CONCAT12(1,(undefined2)local_48);
  local_48 = CONCAT13(1,(undefined3)local_48);
  local_2c._0_3_ = CONCAT12(0xe,(undefined2)local_2c);
  os_move_mem(&local_30,&BROADCAST_ADDR,6);
  if (param_1 + (uint)*(ushort *)(param_3 + 2) * 0x620 != -0x2f6a0) {
    iVar13 = param_1 + (uint)*(ushort *)(param_3 + 2) * 0x620;
    if (*(int *)(iVar13 + 0x2f6a4) == 0) {
      if (*(int *)(iVar13 + 0x2f6a0) != 0x400) {
        bVar4 = false;
        goto LAB_001c5840;
      }
    }
    else {
      iVar10 = *(int *)(*(int *)(iVar13 + 0x2f6a4) + 0x14);
      bVar4 = iVar10 == 0x100 || (iVar10 - 2U & 0xfffffffd) == 0;
      if (*(int *)(iVar13 + 0x2f6a0) != 0x400) {
LAB_001c5840:
        printk(&_LC73,0x9e7);
        dump_stack();
      }
      if (bVar4) {
        _raw_spin_lock_bh(param_1 + 0xa7bf00);
        for (piVar12 = *(int **)(param_1 + 0xa7bee4); (int *)(param_1 + 0xa7bee4) != piVar12;
            piVar12 = (int *)*piVar12) {
          while (*(char *)((int)piVar12 + -0xff) != *param_3) {
            piVar12 = (int *)*piVar12;
            if ((int *)(param_1 + 0xa7bee4) == piVar12) goto LAB_001c57a4;
          }
          os_move_mem(&local_30,(void *)((int)piVar12 + -0xfe),6);
        }
LAB_001c57a4:
        _raw_spin_unlock_bh(param_1 + 0xa7bf00);
      }
    }
  }
  local_48._0_2_ = CONCAT11(1,(undefined1)local_48);
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    local_68 = (uint)CONCAT21(local_68._2_2_,1) << 8;
  }
  local_70 = local_70 & 0xffffff00;
LAB_001c54b0:
  puVar5 = local_8c;
  local_50 = local_50 & 0xffffff00;
  uVar7 = pTlvAppend(local_8c + 0xc,0,0x14,&local_34,&local_88,&local_8d);
  uVar7 = pTlvAppend(uVar7,1,0xc,&local_4c,&local_88,&local_8d);
  uVar7 = pTlvAppend(uVar7,2,8,&local_84,&local_88,&local_8d);
  uVar7 = pTlvAppend(uVar7,9,8,&local_64,&local_88,&local_8d);
  uVar7 = pTlvAppend(uVar7,0xd,8,&local_5c,&local_88,&local_8d);
  uVar7 = pTlvAppend(uVar7,3,8,&local_7c,&local_88,&local_8d);
  uVar7 = pTlvAppend(uVar7,5,8,&local_74,&local_88,&local_8d);
  uVar7 = pTlvAppend(uVar7,6,8,&local_6c,&local_88,&local_8d);
  if (*(short *)(param_1 + 0xa78698) != -1) {
    uVar7 = pTlvAppend(uVar7,0xc,0xc,&local_40,&local_88,&local_8d);
  }
  pTlvAppend(uVar7,0x10,8,&local_54,&local_88,&local_8d);
  *(ushort *)(puVar5 + 6) = (ushort)local_8d;
  puVar5[8] = (byte)(((uint)*(ushort *)(param_3 + 2) << 0x16) >> 0x1e);
  uVar2 = *(undefined2 *)(param_3 + 2);
  puVar5[5] = 1;
  puVar5[4] = (char)uVar2;
  AndesAppendCmdMsg(param_2,local_8c,0xfc);
  os_free_mem(local_8c);
  return 0;
}

