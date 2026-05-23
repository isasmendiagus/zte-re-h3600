// module: mt7915.ko
// function: sta_probe_response_xmit @ 0x79784
// size: 836 bytes
//

undefined4 sta_probe_response_xmit(int param_1,int *param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  ushort uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  bool bVar11;
  undefined1 *puVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  undefined1 *puVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  undefined1 *puVar18;
  undefined4 uVar19;
  undefined1 *puVar20;
  undefined4 uVar21;
  undefined4 uVar22;
  undefined1 *puVar23;
  undefined4 uVar24;
  undefined1 *puVar25;
  undefined4 uVar26;
  undefined4 uVar27;
  undefined1 local_6c;
  undefined1 local_6b;
  ushort local_6a;
  undefined2 local_67;
  undefined1 local_65;
  int local_64;
  int local_60;
  int local_5c;
  undefined1 auStack_58 [8];
  int local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  int *local_40;
  undefined4 local_3c;
  undefined1 auStack_38 [24];
  
  local_67 = 0x12a;
  local_65 = 0;
  local_6c = 1;
  local_64 = 0;
  local_60 = 0;
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = (int *)0x0;
  local_3c = 0;
  local_6b = 2;
  iVar1 = GetStaCfgByWdev();
  if (iVar1 != 0) {
    wlan_operate_get_addht(param_2);
    local_48 = CONCAT22(local_48._2_2_,(short)param_2[6]);
    local_4c._0_3_ = CONCAT12(*(undefined1 *)((int)param_2 + 0x1a),(undefined2)local_4c);
    local_4c = CONCAT31(local_4c._1_3_,5);
    local_40 = param_2;
    iVar2 = os_alloc_mem(param_1,&local_64,0x900);
    if (iVar2 == 0) {
      MgtMacHeaderInit(param_1,auStack_38,5,0,param_3,iVar1 + 0x1b,iVar1 + 0x212428);
      if (param_2[0xb] == 1) {
        if (param_2[0x5d] == 1) {
          uVar3 = 2;
        }
        else {
          uVar3 = 0x12;
        }
      }
      else {
        uVar3 = 0x12;
      }
      puVar12 = &SsidIe;
      uVar13 = 1;
      iVar2 = iVar1 + 0x212426;
      uVar10 = (uint)*(byte *)(iVar1 + 0x212426);
      uVar14 = 1;
      iVar8 = iVar1 + 0x40c6;
      puVar15 = &SupRateIe;
      uVar16 = 1;
      iVar6 = iVar1 + 0x212406;
      uVar9 = (uint)*(byte *)(iVar1 + 0x40c6);
      uVar17 = 1;
      if (*(int *)(param_1 + 0x795064) == 1) {
        local_6a = 0x20;
      }
      else {
        local_6a = 0;
      }
      puVar18 = &DsIe;
      local_6a = local_6a | uVar3;
      puVar23 = &IbssIe;
      puVar20 = &local_6c;
      puVar25 = &local_6b;
      uVar19 = 1;
      iVar4 = iVar1 + 0x40c7;
      iVar7 = iVar1 + 0x40b2;
      uVar21 = 1;
      iVar5 = (int)param_2 + 0x1a;
      uVar22 = 1;
      uVar24 = 1;
      uVar26 = 2;
      uVar27 = 0xffffffff;
      MakeOutgoingFrame(local_64,&local_60,0x18,auStack_38,8,auStack_58,2,&DAT_00794c50 + param_1,2,
                        &local_6a,1,&SsidIe,1,iVar2,uVar10,iVar6,1,&SupRateIe,1,iVar8,uVar9,iVar4,1,
                        &DsIe,1,puVar20,1,iVar5,1,&IbssIe,1,puVar25,2,iVar7,0xffffffff);
      if (*(char *)(iVar1 + 0x40d3) != '\0') {
        MakeOutgoingFrame(local_64 + local_60,&local_5c,3,&local_67,1,&ExtRateIe,1,iVar1 + 0x40d3,
                          *(char *)(iVar1 + 0x40d3),iVar1 + 0x40d4,0xffffffff,puVar12,uVar13,iVar2,
                          uVar10,iVar6,uVar14,puVar15,uVar16,iVar8,uVar9,iVar4,uVar17,puVar18,uVar19
                          ,puVar20,uVar21,iVar5,uVar22,puVar23,uVar24,puVar25,uVar26,iVar7,uVar27);
        local_60 = local_5c + local_60;
      }
      iVar1 = build_rsn_ie(param_1,param_2,local_64 + local_60);
      bVar11 = (*(ushort *)(param_2 + 6) & 0x18) != 0;
      if (!bVar11) {
        param_2 = &local_50;
      }
      local_60 = iVar1 + local_60;
      if (bVar11) {
        local_50 = local_64 + local_60;
        param_2 = &local_50;
        iVar1 = build_ht_ies(param_1,param_2);
        local_60 = iVar1 + local_60;
      }
      local_50 = local_64 + local_60;
      iVar1 = build_wsc_ie(param_1,param_2);
      local_60 = iVar1 + local_60;
      MiniportMMRequest(param_1,0,local_64);
      os_free_mem(local_64);
      return 1;
    }
  }
  return 0;
}

