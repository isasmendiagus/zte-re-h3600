// module: mt7915.ko
// function: a4_interface_init @ 0x9eee8
// size: 368 bytes
//

undefined4 a4_interface_init(int param_1,uint param_2,int param_3,uint param_4)

{
  char *pcVar1;
  uint uVar2;
  byte bVar3;
  int iVar4;
  bool bVar5;
  uint uVar6;
  
  uVar6 = param_4;
  if (param_3 == 0) {
    if (param_2 < 2) {
      iVar4 = param_1 + param_2 * 0x2137b0;
      bVar3 = (&DAT_00580ee9)[iVar4];
      (&DAT_00580ee9)[iVar4] = bVar3 | (byte)(1 << (param_4 & 0xff));
      bVar5 = bVar3 == 0;
LAB_0009ef44:
      if (bVar5) {
        iVar4 = *(int *)(param_1 + 0xa7cbe0);
        if (iVar4 == 0) {
          MtCmdSetA4Enable(param_1,2,1,0,uVar6);
          iVar4 = *(int *)(param_1 + 0xa7cbe0);
        }
        *(int *)(param_1 + 0xa7cbe0) = iVar4 + 1;
      }
      if (1 < DebugLevel) {
        printk("a4_interface_init a4_interface_count: %d\n",*(undefined4 *)(param_1 + 0xa7cbe0));
        return 1;
      }
      return 1;
    }
  }
  else {
    uVar2 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    if (uVar2 > param_2 && 0x1f >= param_2) {
      iVar4 = param_1 + param_2 * 0x5834;
      bVar3 = "Query::OID_802_11_STATISTICS\n"[iVar4 + 0x18];
      bVar5 = bVar3 == 0;
      if (bVar5) {
        pcVar1 = "Query::OID_802_11_STATISTICS\n" + iVar4 + 0x1c;
        pcVar1[0] = '\0';
        pcVar1[1] = '\0';
        pcVar1[2] = '\0';
        pcVar1[3] = '\0';
        *(char **)("Query::OID_802_11_STATISTICS(mem alloc failed)\n" + iVar4) =
             "Query::OID_802_11_STATISTICS(mem alloc failed)\n" + iVar4;
        *(char **)("Query::OID_802_11_STATISTICS(mem alloc failed)\n" + iVar4 + 4) =
             "Query::OID_802_11_STATISTICS(mem alloc failed)\n" + iVar4;
        RoutingTabInit(param_1,param_2,1);
        bVar3 = "Query::OID_802_11_STATISTICS\n"[iVar4 + 0x18];
      }
      bVar5 = bVar5 || (uVar2 <= param_2 || 0x1f < param_2);
      "Query::OID_802_11_STATISTICS\n"[param_2 * 0x5834 + param_1 + 0x18] =
           bVar3 | (byte)(1 << (param_4 & 0xff));
      goto LAB_0009ef44;
    }
  }
  return 0;
}

