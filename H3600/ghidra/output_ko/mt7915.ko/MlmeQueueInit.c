// module: mt7915.ko
// function: MlmeQueueInit @ 0x12cf90
// size: 80 bytes
//

undefined4 MlmeQueueInit(undefined4 param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  param_2[3] = 0;
  *param_2 = 0;
  param_2[1] = 0;
  param_2[2] = 0;
  puVar1 = param_2 + 4;
  do {
    *(undefined1 *)((int)puVar1 + 0x922) = 0;
    puVar1[0x242] = 0;
    puVar2 = puVar1 + 0x24c;
    __memzero(puVar1,0x900);
    puVar1 = puVar2;
  } while (puVar2 != param_2 + 0x24c04);
  return 0;
}

