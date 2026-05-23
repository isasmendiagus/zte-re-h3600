// module: mt7915.ko
// function: token_tx_record_free_notify @ 0x1d401c
// size: 100 bytes
//

void token_tx_record_free_notify(int param_1,uint param_2)

{
  ushort *puVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  
  if (param_2 < *(ushort *)(param_1 + 0x48)) {
    uVar4 = 0;
  }
  else {
    uVar2 = 1;
    iVar3 = param_1;
    do {
      uVar4 = uVar2;
      puVar1 = (ushort *)(iVar3 + 0x50);
      iVar3 = iVar3 + 8;
      uVar2 = uVar4 + 1;
    } while (*puVar1 <= param_2 && (uVar4 & 0xff) != 0xb);
  }
  param_1 = param_1 + uVar4 * 8;
  *(int *)(param_1 + 0x4c) = *(int *)(param_1 + 0x4c) + 1;
  return;
}

