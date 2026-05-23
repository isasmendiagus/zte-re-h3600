// module: mt7915.ko
// function: update_peer_he_sr_ies @ 0x20546c
// size: 200 bytes
//

undefined4 update_peer_he_sr_ies(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  byte bVar3;
  
  bVar1 = *(byte *)(param_2 + 0xa0);
  bVar3 = bVar1 & 4;
  if (*(byte *)(param_1 + 0x1499) != bVar1) {
    *(byte *)(param_1 + 0x1499) = bVar1;
  }
  if (((bVar1 & 4) == 0) ||
     (bVar3 = *(byte *)(param_2 + 0xa1), *(byte *)(param_1 + 0x149a) != bVar3)) {
    *(byte *)(param_1 + 0x149a) = bVar3;
  }
  if ((bVar1 & 8) != 0) {
    if (*(char *)(param_1 + 0x149b) != *(char *)(param_2 + 0xa8)) {
      *(char *)(param_1 + 0x149b) = *(char *)(param_2 + 0xa8);
    }
    if (*(char *)(param_1 + 0x149c) != *(char *)(param_2 + 0xa9)) {
      *(char *)(param_1 + 0x149c) = *(char *)(param_2 + 0xa9);
    }
    iVar2 = *(int *)(param_2 + 0xb4);
    if (*(int *)(param_1 + 0x14a4) != iVar2 ||
        *(int *)(param_1 + 0x14a0) != *(int *)(param_2 + 0xb0)) {
      *(int *)(param_1 + 0x14a0) = *(int *)(param_2 + 0xb0);
      *(int *)(param_1 + 0x14a4) = iVar2;
    }
    iVar2 = *(int *)(param_2 + 0xbc);
    if (*(int *)(param_1 + 0x14ac) != iVar2 ||
        *(int *)(param_1 + 0x14a8) != *(int *)(param_2 + 0xb8)) {
      *(int *)(param_1 + 0x14a8) = *(int *)(param_2 + 0xb8);
      *(int *)(param_1 + 0x14ac) = iVar2;
    }
    return 1;
  }
  *(byte *)(param_1 + 0x149b) = bVar1 & 8;
  *(byte *)(param_1 + 0x149c) = bVar1 & 8;
  *(undefined4 *)(param_1 + 0x14a0) = 0;
  *(undefined4 *)(param_1 + 0x14a4) = 0;
  *(undefined4 *)(param_1 + 0x14a8) = 0;
  *(undefined4 *)(param_1 + 0x14ac) = 0;
  return 1;
}

