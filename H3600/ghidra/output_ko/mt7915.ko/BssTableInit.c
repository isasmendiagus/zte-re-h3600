// module: mt7915.ko
// function: BssTableInit @ 0x10e464
// size: 100 bytes
//

void BssTableInit(undefined4 *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = param_1 + 2;
  *param_1 = 0;
  *(undefined1 *)(param_1 + 1) = 0;
  do {
    iVar2 = puVar1[0x13c];
    __memzero(puVar1,0xaf4);
    *(undefined1 *)((int)puVar1 + 0x71) = 0x81;
    if (iVar2 != 0) {
      RTMPZeroMemory(iVar2,0x400);
      puVar1[0x13c] = iVar2;
    }
    puVar1 = puVar1 + 0x2bd;
  } while (puVar1 != param_1 + 0x2bd02);
  return;
}

