// module: mt7915.ko
// function: ChangeToCellPowerLimit @ 0x103140
// size: 208 bytes
//

void ChangeToCellPowerLimit(int param_1,uint param_2)

{
  byte bVar1;
  
  if (param_2 != 0xff) {
    if (param_2 < 6) {
      bVar1 = 6;
      *(undefined1 *)(param_1 + 0x794cd8) = 6;
      *(undefined1 *)(param_1 + 0x794cd9) = 6;
    }
    else if (param_2 < 9) {
      bVar1 = 10;
      *(undefined1 *)(param_1 + 0x794cd8) = 10;
      *(undefined1 *)(param_1 + 0x794cd9) = 10;
    }
    else if (param_2 < 0xc) {
      bVar1 = 0x19;
      *(undefined1 *)(param_1 + 0x794cd8) = 0x19;
      *(undefined1 *)(param_1 + 0x794cd9) = 0x19;
    }
    else if (param_2 < 0xe) {
      bVar1 = 0x32;
      *(undefined1 *)(param_1 + 0x794cd8) = 0x32;
      *(undefined1 *)(param_1 + 0x794cd9) = 0x32;
    }
    else {
      if (param_2 == 0xe) {
        bVar1 = 0x4b;
      }
      else {
        bVar1 = 100;
      }
      *(byte *)(param_1 + 0x794cd8) = bVar1;
      *(byte *)(param_1 + 0x794cd9) = bVar1;
    }
    if (*(byte *)(param_1 + 0x795041) < bVar1) {
      *(byte *)(param_1 + 0x794cd8) = *(byte *)(param_1 + 0x795041);
    }
    if (*(byte *)(param_1 + 0x795042) < bVar1) {
      *(byte *)(param_1 + 0x794cd9) = *(byte *)(param_1 + 0x795042);
    }
    return;
  }
  return;
}

