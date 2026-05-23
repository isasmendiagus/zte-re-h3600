// module: mt7915.ko
// function: AsicUpdateRxWCIDTable @ 0x133978
// size: 880 bytes
//

void AsicUpdateRxWCIDTable(int param_1,uint param_2,void *param_3,int param_4,undefined1 param_5)

{
  char cVar1;
  byte bVar2;
  undefined4 uVar3;
  undefined1 uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  byte bVar8;
  uint *puVar9;
  byte bVar10;
  byte bVar11;
  undefined4 local_58;
  undefined4 uStack_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 uStack_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  iVar5 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  os_zero_mem(&local_58,0x30);
  local_30._0_3_ = CONCAT12(param_5,(undefined2)local_30);
  local_58 = CONCAT22(local_58._2_2_,(short)param_2);
  os_move_mem(&uStack_48,param_3,6);
  uVar6 = HcGetMaxStaNum(param_1);
  if (param_2 < uVar6) {
    puVar9 = (uint *)(param_2 * 0x14c0 + param_1 + 0xa1d20);
  }
  else {
    puVar9 = (uint *)0x0;
  }
  if ((param_4 == 1) ||
     (uVar6 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0)), uVar3 = uStack_38,
     uVar6 == param_2)) {
    local_4c = 3;
    uStack_54._0_2_ = CONCAT11(0xe,(undefined1)uStack_54);
    local_40 = 0;
    if (((*(byte *)(param_1 + 0x286294) & 3) == 3) &&
       (iVar7 = HcGetWcidLinkType(param_1,param_2), iVar7 == 2)) {
      local_4c = 4;
    }
    goto LAB_00133bc4;
  }
  if (puVar9 == (uint *)0x0) {
    if (3 < DebugLevel) {
      printk("%s():mac_entry is NULL!\n","AsicUpdateRxWCIDTable");
    }
    goto LAB_00133bc4;
  }
  uVar6 = *puVar9;
  if (uVar6 == 0x20001) {
    uVar6 = puVar9[2];
    if (*(int *)(uVar6 + 0x14) == 1) {
LAB_00133c8c:
      local_4c = 1;
    }
    else if (*(int *)(uVar6 + 0x14) == 2) {
      local_4c = 0;
    }
  }
  else if (uVar6 == 2) {
    uVar6 = puVar9[2];
    local_4c = 2;
  }
  else if (uVar6 == 0x40001) {
    uVar6 = puVar9[2];
    local_4c = 5;
  }
  else {
    if ((uVar6 & 4) == 0) {
      uVar6 = puVar9[2];
      goto LAB_00133c8c;
    }
    uVar6 = puVar9[2];
    local_4c = 6;
  }
  bVar2 = *(byte *)((int)puVar9 + 0xbf) >> 5;
  uStack_54._0_2_ = CONCAT11(*(undefined1 *)(uVar6 + 0x29),(undefined1)uStack_54);
  local_3c = CONCAT31(local_3c._1_3_,(char)*(undefined2 *)(param_1 + 0xa78698));
  local_58 = CONCAT22((short)puVar9[0x3e],(undefined2)local_58);
  if (1 < bVar2) {
    bVar11 = (byte)(((uint)*(byte *)((int)puVar9 + 0xc3d) << 0x1e) >> 0x18);
    bVar10 = bVar11 >> 7;
    bVar11 = bVar11 >> 7;
    bVar8 = *(byte *)((int)puVar9 + 0xc3d) & 1;
    if ((*(byte *)(param_1 + 0x794ccd) & 4) == 0) {
      bVar10 = 0;
    }
    if (*(int *)(param_1 + 0x79599c) != 1) {
      bVar8 = 0;
    }
    uStack_38._3_1_ = SUB41(uVar3,3);
    uStack_38._0_3_ = CONCAT12(bVar8,CONCAT11(bVar10,(undefined1)uStack_38));
    if (3 < bVar2) {
      local_34 = CONCAT31(local_34._1_3_,bVar8);
      if ((*(byte *)(param_1 + 0x794ccd) & 4) == 0) {
        bVar11 = 0;
      }
      uStack_38 = CONCAT13(bVar11,(undefined3)uStack_38);
    }
  }
  if ((puVar9[0x2d] & 0x100200) == 0x100200) {
    local_50._0_2_ = CONCAT11(1,(undefined1)local_50);
  }
  if ((puVar9[0x2d] & 1) != 0) {
    local_30 = CONCAT31(local_30._1_3_,1);
  }
  if (1 < bVar2) {
    if ((puVar9[0x2d] & 0x200) != 0) {
      local_34 = CONCAT13(1,(undefined3)local_34);
    }
    uVar3 = local_34;
    local_34._0_2_ = CONCAT11(1,(undefined1)local_34);
    local_50 = CONCAT31(local_50._1_3_,(char)puVar9[0x341]);
    uStack_54 = CONCAT13(*(undefined1 *)((int)puVar9 + 0xd05),
                         CONCAT12((char)puVar9[0x344],(undefined2)uStack_54));
    if (3 < bVar2) {
      local_34._3_1_ = SUB41(uVar3,3);
      local_34._0_3_ = CONCAT12(1,(undefined2)local_34);
      uVar4 = wlan_config_get_vht_bw_sig();
      local_50._0_3_ = CONCAT12(uVar4,(undefined2)local_50);
      local_3c._0_3_ = CONCAT12(0x3f,(undefined2)local_3c);
    }
  }
  cVar1 = (char)puVar9[0x3a];
  if ((puVar9[0xb1] & 0x10) == 0) {
    local_30 = CONCAT13(cVar1 != '\0',(undefined3)local_30);
    if (cVar1 == '\0') goto LAB_00133bc4;
  }
  else {
    if (cVar1 == '\0') {
      local_30 = local_30 & 0xffffff;
    }
    bVar2 = (byte)local_30;
    local_30._0_2_ = CONCAT11(1,(byte)local_30);
    if (cVar1 == '\0') goto LAB_00133bc4;
    local_30 = CONCAT13(1,(undefined3)local_30);
    local_30 = CONCAT22(local_30._2_2_,(ushort)bVar2);
  }
  if (2 < DebugLevel) {
    printk("AsicUpdateRxWCIDTable: Enable A4 in WTBLinfo\n");
  }
LAB_00133bc4:
  if (*(code **)(iVar5 + 0x138) == (code *)0x0) {
    AsicNotSupportFunc(param_1,"AsicUpdateRxWCIDTable");
    return;
  }
  (**(code **)(iVar5 + 0x138))
            (param_1,local_58,uStack_54,local_50,local_4c,uStack_48,uStack_44,local_40,local_3c,
             uStack_38,local_34,local_30,local_2c);
  return;
}

