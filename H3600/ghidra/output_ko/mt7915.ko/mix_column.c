// module: mt7915.ko
// function: mix_column @ 0xb634c
// size: 484 bytes
//

void mix_column(byte *param_1,int param_2)

{
  byte bVar1;
  byte *pbVar2;
  byte bVar3;
  byte *pbVar4;
  byte *pbVar5;
  int iVar6;
  byte local_48 [4];
  byte local_44 [4];
  byte local_40;
  byte local_3f;
  byte local_3e;
  byte local_3d;
  byte local_3c;
  byte local_3b;
  byte local_3a;
  byte local_39;
  byte local_38;
  byte local_37;
  byte local_36 [6];
  byte local_30 [4];
  byte local_2c [8];
  
  pbVar5 = param_1 + -1;
  pbVar2 = local_48;
  pbVar4 = pbVar5;
  do {
    pbVar4 = pbVar4 + 1;
    if ((char)*pbVar4 < '\0') {
      *pbVar2 = 0x1b;
    }
    else {
      *pbVar2 = 0;
    }
    pbVar2 = pbVar2 + 1;
  } while (pbVar4 != param_1 + 3);
  local_3c = param_1[2];
  local_3b = param_1[3];
  iVar6 = 3;
  local_3a = *param_1;
  local_39 = param_1[1];
  bVar3 = local_3b & 0x7f;
  local_3d = local_3c;
  local_36[0] = local_3c & 0x7f;
  local_40 = local_3b;
  local_36[1] = bVar3;
  local_3f = local_3a;
  local_38 = local_3a & 0x7f;
  local_3e = local_39;
  local_37 = local_39 & 0x7f;
  pbVar2 = &local_38;
  while( true ) {
    iVar6 = iVar6 + -1;
    pbVar2[3] = bVar3 << 1;
    if ((char)pbVar2[2] < '\0') {
      pbVar2[3] = bVar3 << 1 | 1;
    }
    if (iVar6 == 0) break;
    bVar3 = pbVar2[2];
    pbVar2 = pbVar2 + -1;
  }
  local_38 = (local_3a & 0x7f) << 1;
  local_44[0] = local_48[0] ^ local_38;
  local_44[1] = local_39 & 0x7f ^ local_48[1];
  local_44[2] = local_3c & 0x7f ^ local_48[2];
  local_44[3] = local_36[1] ^ local_48[3];
  pbVar2 = local_44;
  pbVar4 = local_36 + 2;
  do {
    pbVar5 = pbVar5 + 1;
    *pbVar4 = *pbVar5 ^ *pbVar2;
    bVar1 = local_36[5];
    bVar3 = local_36[4];
    pbVar2 = pbVar2 + 1;
    pbVar4 = pbVar4 + 1;
  } while (pbVar5 != param_1 + 3);
  pbVar5 = (byte *)(param_2 + -1);
  local_2c[0] = local_3c ^ local_3b;
  local_30[3] = local_36[1] ^ local_48[3] ^ local_36[2];
  local_30[0] = local_36[3] ^ local_44[0];
  local_30[2] = local_44[2] ^ local_36[5];
  local_30[1] = local_44[1] ^ local_36[4];
  local_36[5] = local_36[2];
  local_36[4] = bVar1;
  local_36[3] = bVar3;
  local_2c[1] = local_3b ^ local_3a;
  local_2c[2] = local_39 ^ local_3a;
  local_2c[3] = local_39 ^ local_3c;
  pbVar2 = local_2c;
  pbVar4 = local_30;
  do {
    pbVar5 = pbVar5 + 1;
    *pbVar5 = *pbVar4 ^ *pbVar2;
    pbVar2 = pbVar2 + 1;
    pbVar4 = pbVar4 + 1;
  } while (pbVar5 != (byte *)(param_2 + 3));
  return;
}

