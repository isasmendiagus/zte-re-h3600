// module: mt7915.ko
// function: UpdateBasicRateBitmap @ 0x12a084
// size: 292 bytes
//

void UpdateBasicRateBitmap(int param_1,int param_2)

{
  byte *pbVar1;
  uint uVar2;
  byte *pbVar3;
  uint uVar4;
  uint uVar5;
  byte local_2c [16];
  
  local_2c[0] = 2;
  local_2c[1] = 4;
  local_2c[2] = 0xb;
  local_2c[3] = 0x16;
  local_2c[4] = 0xc;
  local_2c[5] = 0x12;
  local_2c[6] = 0x18;
  local_2c[7] = 0x24;
  local_2c[8] = '0';
  local_2c[9] = 'H';
  local_2c[10] = '`';
  local_2c[0xb] = 'l';
  if (*(byte *)(param_2 + 0x1a) < 0xf) {
    uVar4 = *(uint *)(param_1 + 0x794ca0);
    *(uint *)(param_1 + 0x794c9c) = uVar4;
  }
  else {
    uVar4 = *(uint *)(param_1 + 0x794c9c);
    if ((uVar4 & 0xf) != 0) {
      *(uint *)(param_1 + 0x794ca0) = uVar4;
      uVar4 = uVar4 & 0xfffffff0;
    }
    uVar4 = uVar4 | 0x150;
    *(uint *)(param_1 + 0x794c9c) = uVar4;
  }
  if (uVar4 < 0x1000) {
    pbVar1 = (byte *)(param_2 + 0xaeb);
    pbVar3 = (byte *)(param_2 + 0xade);
    do {
      pbVar3 = pbVar3 + 1;
      *pbVar3 = *pbVar3 & 0x7f;
      pbVar1 = pbVar1 + 1;
      *pbVar1 = *pbVar1 & 0x7f;
    } while (pbVar3 != (byte *)(param_2 + 0xaea));
    uVar5 = 0;
    do {
      if ((uVar4 & 1 << (uVar5 & 0xff)) != 0) {
        uVar2 = (uint)local_2c[uVar5];
        pbVar1 = (byte *)(param_2 + 0xade);
        do {
          pbVar1 = pbVar1 + 1;
          if (*pbVar1 == uVar2) {
            *pbVar1 = ~((byte)~(byte)((uVar2 << 0x19) >> 0x18) >> 1);
          }
        } while ((byte *)(param_2 + 0xaea) != pbVar1);
        pbVar1 = (byte *)(param_2 + 0xaeb);
        do {
          pbVar1 = pbVar1 + 1;
          if (*pbVar1 == uVar2) {
            *pbVar1 = ~((byte)~(byte)((uVar2 << 0x19) >> 0x18) >> 1);
          }
        } while (pbVar1 != (byte *)(param_2 + 0xaf7));
      }
      uVar5 = uVar5 + 1;
    } while (uVar5 != 0xc);
  }
  return;
}

