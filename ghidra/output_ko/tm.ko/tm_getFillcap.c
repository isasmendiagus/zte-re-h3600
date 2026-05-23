// module: tm.ko
// function: tm_getFillcap @ 0x514a8
// size: 92 bytes
//

uint tm_getFillcap(uint param_1)

{
  uint uVar1;
  int iVar2;
  uint local_58 [20];
  
  memcpy(local_58,&DAT_0007abf8,0x50);
  iVar2 = 0;
  do {
    if (param_1 <= local_58[iVar2 * 2]) {
      return local_58[iVar2 * 2 + 1];
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 != 10);
  uVar1 = tm_getFillcap_part_44(param_1);
  return uVar1;
}

