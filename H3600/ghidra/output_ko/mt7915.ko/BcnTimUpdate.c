// module: mt7915.ko
// function: BcnTimUpdate @ 0xb5270
// size: 248 bytes
//

int BcnTimUpdate(int param_1,int param_2,undefined1 *param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined1 *puVar6;
  byte *pbVar7;
  undefined1 *puVar8;
  
  *param_3 = 5;
  uVar1 = 0;
  pbVar7 = (byte *)(param_2 + 0x95a);
  uVar3 = 0;
  param_3[2] = (&DAT_0036b89f)[param_1];
  uVar2 = 0;
  param_3[3] = (&DAT_0036b8a0)[param_1];
  uVar5 = 0;
LAB_000b52b4:
  do {
    uVar4 = uVar5;
    uVar1 = uVar1 + 1;
    pbVar7 = pbVar7 + 1;
    uVar5 = uVar1 & 0xff;
    if (uVar5 == 1) {
      if ((*pbVar7 & 0xfe) == 0) goto LAB_000b52b4;
LAB_000b52d4:
      uVar3 = uVar4;
      if (uVar2 == 0) {
        uVar2 = uVar4;
      }
    }
    else if (*pbVar7 != 0) goto LAB_000b52d4;
    if (uVar1 == 0x25) {
      if ((uVar2 & 1) != 0) {
        uVar2 = uVar2 - 1 & 0xff;
      }
      param_3[4] = (char)uVar2;
      uVar5 = (uVar3 + 4) - uVar2;
      uVar1 = uVar5 & 0xff;
      param_3[1] = (char)uVar5;
      if (uVar2 <= uVar3) {
        puVar6 = (undefined1 *)(param_2 + 0x95b + uVar2);
        puVar8 = param_3 + 5;
        do {
          uVar2 = uVar2 + 1;
          *puVar8 = *puVar6;
          puVar6 = puVar6 + 1;
          puVar8 = puVar8 + 1;
        } while ((int)uVar2 <= (int)uVar3);
        uVar1 = (uint)(byte)param_3[1];
      }
      if ((&DAT_0036b89f)[param_1] == '\0') {
        param_3[4] = param_3[4] | *(byte *)(param_2 + 0x95b) & 1;
      }
      return uVar1 + 2;
    }
  } while( true );
}

