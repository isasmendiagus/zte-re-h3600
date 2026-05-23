// module: mt7915.ko
// function: a4_lookup_entry_by_addr @ 0x9f168
// size: 188 bytes
//

undefined4 a4_lookup_entry_by_addr(int param_1,int param_2,void *param_3)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  char *pcVar5;
  
  iVar2 = a4_get_entry_count();
  if (param_3 != (void *)0x0 && iVar2 != 0) {
    iVar2 = param_1 + param_2 * 0x5834;
    for (pcVar5 = *(char **)("Query::OID_802_11_STATISTICS(mem alloc failed)\n" + iVar2);
        pcVar5 != "Query::OID_802_11_STATISTICS(mem alloc failed)\n" + iVar2;
        pcVar5 = *(char **)pcVar5) {
      if ((((pcVar5 != (char *)0x0) && (pcVar5[8] != '\0')) &&
          (uVar1 = *(ushort *)(pcVar5 + 10),
          uVar3 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0)), uVar1 < uVar3)) &&
         (iVar4 = memcmp(param_3,(void *)((uint)*(ushort *)(pcVar5 + 10) * 0x14c0 + param_1 +
                                         0xa1e0c),6), iVar4 == 0)) {
        return 1;
      }
    }
  }
  return 0;
}

