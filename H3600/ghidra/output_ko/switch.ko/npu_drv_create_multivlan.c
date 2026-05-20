// module: switch.ko
// function: npu_drv_create_multivlan @ 0x20b30
// size: 320 bytes
//

undefined4 npu_drv_create_multivlan(undefined4 param_1,int param_2)

{
  byte bVar1;
  ushort uVar2;
  int iVar3;
  undefined1 *puVar4;
  byte *pbVar5;
  undefined4 local_26;
  undefined4 local_22;
  undefined4 local_1e;
  undefined4 local_1a;
  undefined4 local_16;
  undefined2 local_12;
  
  pbVar5 = *(byte **)(param_2 + 0x14);
  bVar1 = *pbVar5;
  __memzero(&local_26,0x16);
  strncpy((char *)&local_26,*(char **)(pbVar5 + bVar1),0xf);
  bVar1 = *(byte *)(*(int *)(param_2 + 0x10) + 2);
  if ((bVar1 & 1) == 0) {
    uVar2 = *(ushort *)(*(int *)(param_2 + 0x10) + (uint)bVar1);
    iVar3 = *(int *)(param_2 + 0x14);
    local_16 = CONCAT22(local_16._2_2_,
                        (ushort)((((uVar2 & 0xff) << 8 | (uint)(uVar2 >> 8)) << 0x14) >> 0x14));
    bVar1 = *(byte *)(iVar3 + 2);
  }
  else {
    iVar3 = *(int *)(param_2 + 0x14);
    bVar1 = *(byte *)(iVar3 + 2);
  }
  if ((bVar1 & 1) == 0) {
    local_16 = CONCAT22((ushort)((((*(ushort *)(iVar3 + (uint)bVar1) & 0xff) << 8 |
                                  (uint)(*(ushort *)(iVar3 + (uint)bVar1) >> 8)) << 0x14) >> 0x14),
                        (undefined2)local_16);
  }
  _raw_spin_lock_bh(&g_multivlan_lock);
  iVar3 = npu_drv_lookup_multientry(&local_26);
  if (iVar3 == 0) {
    puVar4 = gMultiVlanEntry;
    do {
      if (*puVar4 == '\0') {
        *(undefined4 *)puVar4 = local_26;
        *(undefined4 *)(puVar4 + 4) = local_22;
        *(undefined4 *)(puVar4 + 8) = local_1e;
        *(undefined4 *)(puVar4 + 0xc) = local_1a;
        *(undefined4 *)(puVar4 + 0x10) = local_16;
        *(undefined2 *)(puVar4 + 0x14) = local_12;
        if (puVar4 != (char *)0x0) {
          *(short *)(puVar4 + 0x14) = *(short *)(puVar4 + 0x14) + 1;
          sw_multi_vlan_trans_deal(puVar4);
          goto LAB_00020bb4;
        }
        break;
      }
      puVar4 = puVar4 + 0x16;
    } while ((undefined4 *)puVar4 != &g_multivlan_lock);
    printk("multi_vlan_table full\n");
  }
  else {
    *(short *)(iVar3 + 0x14) = *(short *)(iVar3 + 0x14) + 1;
  }
LAB_00020bb4:
  _raw_spin_unlock_bh(&g_multivlan_lock);
  return 0;
}

