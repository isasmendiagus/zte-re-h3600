// module: mt7915.ko
// function: a4_delete_entry @ 0x9f304
// size: 200 bytes
//

void a4_delete_entry(int param_1,int param_2,uint param_3)

{
  int iVar1;
  int *piVar2;
  char *pcVar3;
  
  iVar1 = a4_get_entry_count();
  if (iVar1 == 0) {
    return;
  }
  pcVar3 = "Query::OID_802_11_STATISTICS\n" + param_1 + param_2 * 0x5834 + 0x1c;
  _raw_spin_lock_bh(pcVar3);
  piVar2 = *(int **)("Query::OID_802_11_STATISTICS(mem alloc failed)\n" + param_1 + param_2 * 0x5834
                    );
  while( true ) {
    if ((int *)(pcVar3 + 4) == piVar2) {
      _raw_spin_unlock_bh(pcVar3);
      return;
    }
    if (((piVar2 != (int *)0x0) && ((char)piVar2[2] != '\0')) &&
       (*(ushort *)((int)piVar2 + 10) == param_3)) break;
    piVar2 = (int *)*piVar2;
  }
  if (*piVar2 != 0) {
    *(int *)(*piVar2 + 4) = piVar2[1];
  }
  if ((int *)piVar2[1] != (int *)0x0) {
    *(int *)piVar2[1] = *piVar2;
  }
  *piVar2 = 0;
  piVar2[1] = 0;
  os_free_mem(piVar2);
  _raw_spin_unlock_bh(pcVar3);
  return;
}

