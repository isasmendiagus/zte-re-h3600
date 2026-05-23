// module: idmfdb.ko
// function: idm_fdb_idm_isolate_handle @ 0x1054c
// size: 296 bytes
//

void idm_fdb_idm_isolate_handle(void)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  int iVar5;
  uint uVar6;
  int iStack_4c;
  int local_48 [17];
  
  pcVar4 = &fdb_list;
  uVar6 = 0;
  iVar2 = 0;
  do {
    if (((*pcVar4 != '\0') && (iVar5 = *(int *)(pcVar4 + 0x14), pcVar4[1] == '\0')) &&
       (*(uint *)(pcVar4 + 8) = *(uint *)(pcVar4 + 8) & 0xfffffffe, iVar5 != 0)) {
      if (((*(uint *)(iVar5 + 0x30) & 1) == 0) || (pcVar4[4] != '\x02')) {
        if (((*(uint *)(iVar5 + 0x30) & 1) != 0) && (pcVar4[4] == '\0')) {
          local_48[uVar6] = (int)pcVar4;
          uVar6 = uVar6 + 1;
        }
      }
      else {
        iVar2 = iVar2 + 1;
      }
    }
    pcVar4 = pcVar4 + 0x128;
  } while (pcVar4 != &__this_module);
  if (uVar6 != 0 || iVar2 == 0) {
    if ((iVar2 == 0 && uVar6 != 0) || (uVar6 == 0 || iVar2 == 0)) {
      sw_set_idm_isolate(0,0);
      return;
    }
    piVar1 = &iStack_4c;
    uVar3 = 0;
    do {
      piVar1 = piVar1 + 1;
      uVar3 = uVar3 + 1;
      *(uint *)(*piVar1 + 8) = *(uint *)(*piVar1 + 8) | 1;
    } while (uVar3 < uVar6);
  }
  sw_set_idm_isolate(0,1);
  return;
}

