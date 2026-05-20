// module: switch.ko
// function: npu_drv_delete_multivlan @ 0x20ad8
// size: 248 bytes
//

undefined4 npu_drv_delete_multivlan(undefined4 param_1,int param_2)

{
  byte bVar1;
  ushort uVar2;
  int iVar3;
  short sVar4;
  byte *pbVar5;
  char acStack_26 [16];
  ushort local_16;
  ushort local_14;
  
  pbVar5 = *(byte **)(param_2 + 0x14);
  bVar1 = *pbVar5;
  __memzero(acStack_26,0x16);
  snprintf(acStack_26,0x10,"%s",*(undefined4 *)(pbVar5 + bVar1));
  bVar1 = *(byte *)(*(int *)(param_2 + 0x10) + 2);
  if ((bVar1 & 1) == 0) {
    uVar2 = *(ushort *)(*(int *)(param_2 + 0x10) + (uint)bVar1);
    iVar3 = *(int *)(param_2 + 0x14);
    local_16 = (ushort)((((uVar2 & 0xff) << 8 | (uint)(uVar2 >> 8)) << 0x14) >> 0x14);
    bVar1 = *(byte *)(iVar3 + 2);
  }
  else {
    iVar3 = *(int *)(param_2 + 0x14);
    bVar1 = *(byte *)(iVar3 + 2);
  }
  if ((bVar1 & 1) == 0) {
    local_14 = (ushort)((((*(ushort *)(iVar3 + (uint)bVar1) & 0xff) << 8 |
                         (uint)(*(ushort *)(iVar3 + (uint)bVar1) >> 8)) << 0x14) >> 0x14);
  }
  _raw_spin_lock_bh(&g_multivlan_lock);
  iVar3 = npu_drv_lookup_multientry(acStack_26);
  if (iVar3 == 0) {
    printk(" multi_vlan_table no has this entry\n");
  }
  else {
    sVar4 = *(short *)(iVar3 + 0x14) + -1;
    *(short *)(iVar3 + 0x14) = sVar4;
    if (sVar4 == 0) {
      sw_multi_vlan_trans_deal(iVar3,1);
      __memzero(iVar3,0x16);
    }
  }
  _raw_spin_unlock_bh(&g_multivlan_lock);
  return 0;
}

