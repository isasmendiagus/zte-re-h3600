// module: mt7915.ko
// function: a4_get_entry_count @ 0x9f058
// size: 144 bytes
//

int a4_get_entry_count(int param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  char *pcVar3;
  
  uVar1 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (uVar1 <= param_2 || 0x1f < param_2) {
    return 0;
  }
  iVar2 = param_1 + param_2 * 0x5834;
  if ("Query::OID_802_11_STATISTICS\n"[iVar2 + 0x18] != '\0') {
    pcVar3 = *(char **)("Query::OID_802_11_STATISTICS(mem alloc failed)\n" + iVar2);
    iVar2 = 0;
    if ("Query::OID_802_11_STATISTICS(mem alloc failed)\n" + param_1 + param_2 * 0x5834 == pcVar3) {
      return 0;
    }
    do {
      pcVar3 = *(char **)pcVar3;
      iVar2 = iVar2 + 1;
    } while ("Query::OID_802_11_STATISTICS(mem alloc failed)\n" + param_1 + param_2 * 0x5834 !=
             pcVar3);
    return iVar2;
  }
  return 0;
}

