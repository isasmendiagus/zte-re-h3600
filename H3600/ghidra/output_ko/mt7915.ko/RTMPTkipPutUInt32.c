// module: mt7915.ko
// function: RTMPTkipPutUInt32 @ 0x1173d4
// size: 24 bytes
//

void RTMPTkipPutUInt32(undefined1 *param_1,uint param_2)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  
  puVar2 = param_1;
  do {
    puVar1 = puVar2 + 1;
    *puVar2 = (char)param_2;
    param_2 = param_2 >> 8;
    puVar2 = puVar1;
  } while (puVar1 != param_1 + 4);
  return;
}

