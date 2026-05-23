// module: mt7915.ko
// function: aes128k128d @ 0xb676c
// size: 384 bytes
//

void aes128k128d(int param_1,int param_2,int param_3)

{
  byte *pbVar1;
  byte *pbVar2;
  byte *pbVar3;
  byte *pbVar4;
  byte *pbVar5;
  undefined1 *puVar6;
  int iVar7;
  int iVar8;
  byte *pbVar9;
  undefined4 local_5c;
  byte local_58 [16];
  byte local_48 [16];
  byte local_38 [20];
  
  pbVar4 = (byte *)(param_1 + -1);
  pbVar3 = local_48 + 0xf;
  pbVar1 = pbVar3;
  do {
    pbVar4 = pbVar4 + 1;
    pbVar1 = pbVar1 + 1;
    *pbVar1 = *pbVar4;
  } while (pbVar4 != (byte *)(param_1 + 0xf));
  pbVar4 = (byte *)(param_3 + -1);
  pbVar1 = local_58 + 0xf;
  iVar8 = 1;
  iVar7 = 0;
  local_5c = param_2;
  do {
    if (iVar7 == 0) {
      pbVar5 = local_48 + 0xf;
      pbVar9 = (byte *)(local_5c + -1);
      pbVar2 = pbVar4;
      do {
        pbVar9 = pbVar9 + 1;
        pbVar5 = pbVar5 + 1;
        pbVar2 = pbVar2 + 1;
        *pbVar2 = *pbVar5 ^ *pbVar9;
      } while (pbVar9 != (byte *)(local_5c + 0xf));
      next_key(local_38,0);
    }
    else {
      if (iVar7 == 10) {
        puVar6 = (undefined1 *)((int)&local_5c + 3);
        pbVar2 = pbVar4;
        do {
          pbVar2 = pbVar2 + 1;
          puVar6 = puVar6 + 1;
          *puVar6 = SboxTable[*pbVar2];
        } while (pbVar2 != (byte *)(param_3 + 0xf));
        shift_row(local_58,local_48);
        do {
          pbVar1 = pbVar1 + 1;
          pbVar3 = pbVar3 + 1;
          pbVar4 = pbVar4 + 1;
          *pbVar4 = *pbVar1 ^ *pbVar3;
        } while (pbVar1 != local_48 + 0xf);
        return;
      }
      pbVar9 = (byte *)((int)&local_5c + 3);
      pbVar2 = pbVar9;
      pbVar5 = pbVar4;
      do {
        pbVar5 = pbVar5 + 1;
        pbVar2 = pbVar2 + 1;
        *pbVar2 = SboxTable[*pbVar5];
      } while (pbVar5 != (byte *)(param_3 + 0xf));
      shift_row(local_58,local_48);
      mix_column(local_48,local_58);
      mix_column(local_48 + 4,local_58 + 4);
      mix_column(local_48 + 8,local_58 + 8);
      mix_column(local_48 + 0xc,local_58 + 0xc);
      pbVar5 = local_48 + 0xf;
      pbVar2 = pbVar4;
      do {
        pbVar9 = pbVar9 + 1;
        pbVar5 = pbVar5 + 1;
        pbVar2 = pbVar2 + 1;
        *pbVar2 = *pbVar9 ^ *pbVar5;
      } while (pbVar9 != pbVar1);
      next_key(local_38,iVar7);
      if (iVar8 == 0xb) {
        return;
      }
    }
    iVar7 = iVar7 + 1;
    iVar8 = iVar8 + 1;
  } while( true );
}

