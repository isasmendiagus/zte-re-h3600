// module: mt7915.ko
// function: TriEventInit @ 0x144be4
// size: 64 bytes
//

void TriEventInit(int param_1)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  
  puVar2 = (undefined1 *)(param_1 + 0x7956ba);
  do {
    puVar1 = puVar2 + 10;
    *puVar2 = 0;
    puVar2 = puVar1;
  } while (puVar1 != (undefined1 *)(param_1 + 0x79593a));
  *(undefined1 *)(param_1 + 0x7956b8) = 0;
  *(undefined4 *)(param_1 + 0x79593c) = 0;
  return;
}

