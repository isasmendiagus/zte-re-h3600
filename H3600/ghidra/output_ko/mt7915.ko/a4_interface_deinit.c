// module: mt7915.ko
// function: a4_interface_deinit @ 0x9fba8
// size: 436 bytes
//

undefined4 a4_interface_deinit(int param_1,uint param_2,int param_3,uint param_4)

{
  uint uVar1;
  char *pcVar2;
  int iVar3;
  char *pcVar4;
  bool bVar5;
  
  if (param_3 == 0) {
    if (1 < param_2) {
      return 0;
    }
    iVar3 = param_1 + param_2 * 0x2137b0;
    if (((byte)(&DAT_00580ee9)[iVar3] == 0) ||
       (uVar1 = (uint)(byte)(&DAT_00580ee9)[iVar3] & ~(1 << (param_4 & 0xff)),
       (&DAT_00580ee9)[iVar3] = (char)uVar1, uVar1 != 0)) goto LAB_0009fc28;
  }
  else {
    uVar1 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    if (uVar1 <= param_2 || 0x1f < param_2) {
      return 0;
    }
    iVar3 = param_1 + param_2 * 0x5834;
    uVar1 = (uint)(byte)"Query::OID_802_11_STATISTICS\n"[iVar3 + 0x18];
    if (uVar1 == 0) goto LAB_0009fc28;
    pcVar2 = *(char **)("Query::OID_802_11_STATISTICS(mem alloc failed)\n" + iVar3);
    pcVar4 = *(char **)pcVar2;
    if (pcVar2 != "Query::OID_802_11_STATISTICS(mem alloc failed)\n" + param_1 + param_2 * 0x5834) {
      do {
        if (pcVar2 != (char *)0x0) {
          a4_ap_peer_disable(param_1,(uint)*(ushort *)(pcVar2 + 10) * 0x14c0 + param_1 + 0xa1d20,
                             param_4);
        }
        bVar5 = pcVar4 != "Query::OID_802_11_STATISTICS(mem alloc failed)\n" +
                          param_1 + param_2 * 0x5834;
        pcVar2 = pcVar4;
        pcVar4 = *(char **)pcVar4;
      } while (bVar5);
      uVar1 = (uint)(byte)"Query::OID_802_11_STATISTICS\n"[param_2 * 0x5834 + param_1 + 0x18];
    }
    uVar1 = uVar1 & ~(1 << (param_4 & 0xff));
    "Query::OID_802_11_STATISTICS\n"[param_2 * 0x5834 + param_1 + 0x18] = (char)uVar1;
    if (uVar1 != 0) goto LAB_0009fc28;
    RoutingTabDestory(param_1,param_2);
  }
  iVar3 = *(int *)(param_1 + 0xa7cbe0) + -1;
  *(int *)(param_1 + 0xa7cbe0) = iVar3;
  if (iVar3 == 0) {
    MtCmdSetA4Enable(param_1,2);
  }
LAB_0009fc28:
  if (DebugLevel < 2) {
    return 1;
  }
  printk("a4_interface_init a4_interface_count: %d\n",*(undefined4 *)(param_1 + 0xa7cbe0));
  return 1;
}

