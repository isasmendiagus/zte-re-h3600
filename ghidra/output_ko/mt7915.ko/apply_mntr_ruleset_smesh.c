// module: mt7915.ko
// function: apply_mntr_ruleset_smesh @ 0x197368
// size: 112 bytes
//

void apply_mntr_ruleset_smesh(int param_1,int param_2)

{
  byte bVar1;
  
  bVar1 = *(byte *)(param_1 + 0xa376a4) & 1;
  if ((*(byte *)(param_1 + 0xa376a4) & 1) != 0) {
    bVar1 = 1;
  }
  *(byte *)(param_2 + 7) = bVar1;
  bVar1 = *(byte *)(param_1 + 0xa376a4) & 2;
  if ((*(byte *)(param_1 + 0xa376a4) & 2) != 0) {
    bVar1 = 1;
  }
  *(byte *)(param_2 + 6) = bVar1;
  bVar1 = *(byte *)(param_1 + 0xa376a4) & 4;
  if ((*(byte *)(param_1 + 0xa376a4) & 4) != 0) {
    bVar1 = 1;
  }
  *(byte *)(param_2 + 5) = bVar1;
  bVar1 = *(byte *)(param_1 + 0xa376a4) & 8;
  if ((*(byte *)(param_1 + 0xa376a4) & 8) != 0) {
    bVar1 = 1;
  }
  *(byte *)(param_2 + 4) = bVar1;
  bVar1 = *(byte *)(param_1 + 0xa376a4) & 0x10;
  if ((*(byte *)(param_1 + 0xa376a4) & 0x10) != 0) {
    bVar1 = 1;
  }
  *(byte *)(param_2 + 3) = bVar1;
  return;
}

