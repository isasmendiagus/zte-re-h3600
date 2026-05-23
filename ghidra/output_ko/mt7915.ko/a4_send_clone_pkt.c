// module: mt7915.ko
// function: a4_send_clone_pkt @ 0x9f728
// size: 484 bytes
//

void a4_send_clone_pkt(int param_1,int param_2,int param_3,int param_4)

{
  undefined1 uVar1;
  ushort uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  uint uVar8;
  undefined4 *puVar9;
  undefined4 uVar10;
  ushort local_2a [3];
  
  local_2a[0] = 0;
  if ((param_3 != 0) && (iVar3 = a4_get_entry_count(), 0 < iVar3)) {
    uVar8 = 0;
    if (param_4 != 0) {
      iVar3 = RoutingTabLookup(param_1,param_2,param_4,0,local_2a);
      if (iVar3 == 0) {
        uVar8 = 0;
      }
      else {
        uVar8 = *(uint *)(iVar3 + 4) & 1;
      }
    }
    pcVar6 = "Query::OID_802_11_STATISTICS\n" + param_1 + param_2 * 0x5834 + 0x1c;
    _raw_spin_lock_bh(pcVar6);
    for (pcVar7 = *(char **)("Query::OID_802_11_STATISTICS(mem alloc failed)\n" +
                            param_1 + param_2 * 0x5834); pcVar7 != pcVar6 + 4;
        pcVar7 = *(char **)pcVar7) {
      while ((((pcVar7 != (char *)0x0 && (pcVar7[8] != '\0')) &&
              (uVar2 = *(ushort *)(pcVar7 + 10),
              uVar4 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0)), uVar2 < uVar4))
             && ((uVar8 == 0 || ((uint)local_2a[0] != (uint)*(ushort *)(pcVar7 + 10)))))) {
        iVar3 = (uint)*(ushort *)(pcVar7 + 10) * 0x14c0 + param_1;
        puVar9 = *(undefined4 **)(iVar3 + 0xa1d28);
        if (puVar9 == (undefined4 *)0x0) {
          _raw_spin_unlock_bh(pcVar6,0x20);
          if (DebugLevel < 3) {
            return;
          }
          printk("%s:wdev is null \n","a4_send_clone_pkt");
          return;
        }
        uVar10 = *puVar9;
        iVar5 = skb_copy(param_3);
        if (iVar5 == 0) {
          _raw_spin_unlock_bh(pcVar6,puVar9,0);
          if (DebugLevel < 0) {
            return;
          }
          printk("%s: Fail to alloc memory for pPacketClone\n","a4_send_clone_pkt");
          return;
        }
        *(undefined4 *)(iVar5 + 0x18) = uVar10;
        *(undefined2 *)(iVar5 + 0x42) = *(undefined2 *)(iVar3 + 0xa1e00);
        uVar1 = *(undefined1 *)(puVar9 + 3);
        *(undefined1 *)(iVar5 + 0x2f) = 0;
        *(undefined1 *)(iVar5 + 0x36) = 0;
        *(undefined1 *)(iVar5 + 0x2d) = uVar1;
        a4_hard_transmit(param_1);
        pcVar7 = *(char **)pcVar7;
        if (pcVar7 == pcVar6 + 4) goto LAB_0009f89c;
      }
    }
LAB_0009f89c:
    _raw_spin_unlock_bh(pcVar6);
  }
  return;
}

