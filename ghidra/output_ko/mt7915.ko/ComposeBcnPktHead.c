// module: mt7915.ko
// function: ComposeBcnPktHead @ 0xb5368
// size: 952 bytes
//

int ComposeBcnPktHead(int param_1,int param_2,int param_3)

{
  short sVar1;
  bool bVar2;
  char cVar3;
  undefined1 *puVar4;
  ushort uVar5;
  uint uVar6;
  ushort *puVar7;
  undefined1 *puVar8;
  int iVar9;
  undefined4 uVar10;
  undefined1 *puVar11;
  undefined4 uVar12;
  byte *pbVar13;
  undefined4 uVar14;
  undefined1 local_5f;
  byte local_5e;
  undefined1 local_5d;
  undefined1 local_5c;
  char local_5b;
  ushort local_5a;
  int local_58;
  int local_54;
  undefined1 local_4e;
  undefined1 local_4d;
  undefined1 local_4c;
  undefined1 local_4b;
  undefined1 local_4a;
  undefined1 local_49;
  undefined1 auStack_48 [8];
  undefined1 auStack_40 [28];
  
  local_58 = 0;
  local_5e = 0;
  local_4e = 0;
  local_4d = 0;
  local_4c = 0;
  local_4b = 0;
  local_4a = 0;
  local_49 = 0;
  local_5f = 1;
  local_5c = 2;
  if (param_2 != 0) {
    local_5b = *(char *)(param_2 + 0x1a);
    sVar1 = *(short *)(param_2 + 0x18);
    if (*(int *)(param_2 + 0x14) != 1) {
      if (*(int *)(param_2 + 0x14) == 2) {
        iVar9 = GetStaCfgByWdev();
        if (iVar9 == 0) {
          return 0;
        }
        local_5e = *(byte *)(iVar9 + 0x212426);
        puVar11 = (undefined1 *)(iVar9 + 0x212428);
        puVar8 = (undefined1 *)(iVar9 + 0x212406);
        puVar4 = (undefined1 *)(param_2 + 0x1b);
        if (*(int *)(param_2 + 0x2c) == 1) {
          if (*(int *)(param_2 + 0x174) == 1) {
            uVar5 = 2;
          }
          else {
            uVar5 = 0x12;
          }
        }
        else {
          uVar5 = 0x12;
        }
        bVar2 = true;
        if (*(int *)(param_1 + 0x795064) == 0) {
          local_5a = 0;
        }
        else {
          local_5a = 0x20;
        }
        local_5a = local_5a | uVar5;
        puVar7 = &local_5a;
      }
      else {
        puVar4 = &local_4e;
        puVar7 = &local_5a;
        iVar9 = 0;
        bVar2 = false;
        puVar11 = puVar4;
        puVar8 = puVar4;
      }
LAB_000b53f0:
      MgtMacHeaderInit(param_1,auStack_40,8,0,&BROADCAST_ADDR,puVar4,puVar11);
      uVar6 = (uint)local_5e;
      puVar11 = &SsidIe;
      pbVar13 = &local_5e;
      uVar10 = 1;
      uVar14 = 0xffffffff;
      uVar12 = 1;
      MakeOutgoingFrame(param_3,&local_58,0x18,auStack_40,8,auStack_48,2,&DAT_00794c50 + param_1,2,
                        puVar7,1,&SsidIe,1,pbVar13,uVar6,puVar8,0xffffffff);
      local_5d = *(undefined1 *)(param_2 + 0xade);
      if (sVar1 == 2) {
        local_5d = 4;
      }
      local_54 = 0;
      MakeOutgoingFrame(param_3 + local_58,&local_54,1,&SupRateIe,1,&local_5d,local_5d,
                        param_2 + 0xadf,0xffffffff,puVar7,uVar10,puVar11,uVar12,pbVar13,uVar6,puVar8
                        ,uVar14);
      local_58 = local_54 + local_58;
      local_54 = 0;
      MakeOutgoingFrame(param_3 + local_58,&local_54,1,&DsIe,1,&local_5f,1,&local_5b,0xffffffff);
      local_58 = local_54 + local_58;
      if (*(char *)(param_1 + 0x286285) == '\0') {
        if (iVar9 == 0) {
          iVar9 = GetStaCfgByWdev(param_1,param_2);
        }
        if (iVar9 == 0) {
          bVar2 = false;
        }
        if (bVar2) {
          local_54 = 0;
          MakeOutgoingFrame(param_3 + local_58,&local_54,1,&IbssIe,1,&local_5c,2,iVar9 + 0x40b2,
                            0xffffffff,puVar7,uVar10,puVar11,uVar12,pbVar13,uVar6,puVar8,uVar14);
          return local_54 + local_58;
        }
      }
      return local_58;
    }
    iVar9 = *(int *)(param_2 + 4);
    if (iVar9 != 0) {
      puVar8 = (undefined1 *)(iVar9 + 0x4068);
      puVar7 = (ushort *)(iVar9 + 0x408c);
      puVar4 = (undefined1 *)(param_2 + 0x1b);
      if (*(char *)(iVar9 + 0x408a) == '\0') {
        local_5e = *(byte *)(iVar9 + 0x4089);
      }
      else {
        local_5e = 0;
      }
      iVar9 = *(int *)(param_2 + 0x3fe4);
      puVar11 = (undefined1 *)(param_2 + 0x21);
      if (iVar9 != 0) {
        cVar3 = local_5b;
        if (((*(char *)(param_1 + 0x795074) == '\x01') && (*(char *)(iVar9 + 4) == '\x01')) &&
           (cVar3 = *(char *)(iVar9 + 5), *(char *)(iVar9 + 5) == '\0')) {
          cVar3 = local_5b;
        }
        local_5b = cVar3;
        iVar9 = 0;
        bVar2 = false;
        goto LAB_000b53f0;
      }
    }
  }
  return 0;
}

