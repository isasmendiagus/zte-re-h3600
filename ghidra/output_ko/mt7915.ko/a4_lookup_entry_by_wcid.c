// module: mt7915.ko
// function: a4_lookup_entry_by_wcid @ 0x9f0e8
// size: 128 bytes
//

undefined4 a4_lookup_entry_by_wcid(int param_1,int param_2,uint param_3)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = a4_get_entry_count();
  if (iVar1 == 0) {
    return 0;
  }
  param_1 = param_1 + param_2 * 0x5834;
  piVar2 = *(int **)("Query::OID_802_11_STATISTICS(mem alloc failed)\n" + param_1);
  while( true ) {
    if ((int *)("Query::OID_802_11_STATISTICS(mem alloc failed)\n" + param_1) == piVar2) {
      return 0;
    }
    if (((piVar2 != (int *)0x0) && (*(char *)(piVar2 + 2) != '\0')) &&
       (*(ushort *)((int)piVar2 + 10) == param_3)) break;
    piVar2 = (int *)*piVar2;
  }
  return 1;
}

