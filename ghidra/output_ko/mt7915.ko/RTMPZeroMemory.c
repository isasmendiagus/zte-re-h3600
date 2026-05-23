// module: mt7915.ko
// function: RTMPZeroMemory @ 0x13a4e0
// size: 32 bytes
//

void RTMPZeroMemory(undefined1 *param_1,int param_2)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  
  if (param_2 == 0) {
    return;
  }
  puVar2 = param_1;
  do {
    puVar1 = puVar2 + 1;
    *puVar2 = 0;
    puVar2 = puVar1;
  } while (puVar1 != param_1 + param_2);
  return;
}

