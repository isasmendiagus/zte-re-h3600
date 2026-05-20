// module: switch.ko
// function: npu_drv_delete_flow @ 0x213fc
// size: 368 bytes
//

undefined4 npu_drv_delete_flow(undefined4 param_1,int param_2)

{
  byte bVar1;
  byte bVar2;
  ushort uVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  byte *pbVar7;
  char acStack_44 [16];
  ushort local_34;
  undefined2 local_32;
  ushort uStack_30;
  ushort local_2e;
  undefined2 uStack_2c;
  undefined4 local_2a;
  undefined4 local_26;
  
  if (DAT_0002bbbc == 0) {
    return 0xffffffff;
  }
  iVar5 = *(int *)(*(int *)(param_2 + 0x34) + 0x14);
  if (iVar5 == 4) {
    iVar5 = *(int *)(param_2 + 0x10);
    pbVar7 = *(byte **)(param_2 + 0x14);
    bVar1 = *(byte *)(iVar5 + 5);
    bVar2 = *pbVar7;
    __memzero(acStack_44,0x18);
    uVar6 = *(uint *)(iVar5 + (uint)bVar1 + 4);
    local_2e = (ushort)((uVar6 << 0x18) >> 0x10) | (ushort)(uVar6 >> 8) & 0xff;
    uStack_30 = (ushort)((uVar6 >> 0x10 & 0xff) << 8) | (ushort)(byte)(uVar6 >> 0x18);
    snprintf(acStack_44,0x10,"%s",*(undefined4 *)(pbVar7 + bVar2));
    bVar1 = *(byte *)(*(int *)(param_2 + 0x10) + 2);
    if ((bVar1 & 1) == 0) {
      uVar3 = *(ushort *)(*(int *)(param_2 + 0x10) + (uint)bVar1);
      local_34 = (uVar3 & 0xf) << 8 | uVar3 >> 8;
    }
    sw_del_igmp_addr_e8v4(acStack_44);
    npu_drv_delete_multivlan(param_1,param_2);
    uVar4 = 0;
  }
  else {
    if (iVar5 == 5) {
      pbVar7 = *(byte **)(param_2 + 0x14);
      bVar1 = *pbVar7;
      iVar5 = *(int *)(param_2 + 0x10) + (uint)*(byte *)(*(int *)(param_2 + 0x10) + 7);
      __memzero(acStack_44,0x22);
      local_2a = *(undefined4 *)(iVar5 + 0x20);
      local_26 = *(undefined4 *)(iVar5 + 0x24);
      local_32 = (undefined2)*(undefined4 *)(iVar5 + 0x18);
      uStack_30 = (ushort)((uint)*(undefined4 *)(iVar5 + 0x18) >> 0x10);
      local_2e = (ushort)*(undefined4 *)(iVar5 + 0x1c);
      uStack_2c = (undefined2)((uint)*(undefined4 *)(iVar5 + 0x1c) >> 0x10);
      snprintf(acStack_44,0x10,"%s",*(undefined4 *)(pbVar7 + bVar1));
      bVar1 = *(byte *)(*(int *)(param_2 + 0x10) + 2);
      if ((bVar1 & 1) == 0) {
        uVar3 = *(ushort *)(*(int *)(param_2 + 0x10) + (uint)bVar1);
        local_34 = (uVar3 & 0xf) << 8 | uVar3 >> 8;
      }
      sw_del_mld_addr_e8v4(acStack_44);
      npu_drv_delete_multivlan(param_1,param_2);
      return 0;
    }
    uVar4 = npu_drv_delete_flow_part_1(param_2);
  }
  return uVar4;
}

