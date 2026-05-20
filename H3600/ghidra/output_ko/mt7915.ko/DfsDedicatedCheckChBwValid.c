// module: mt7915.ko
// function: DfsDedicatedCheckChBwValid @ 0x233fbc
// size: 284 bytes
//

undefined4 DfsDedicatedCheckChBwValid(int param_1,uint param_2,uint param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  undefined1 *puVar3;
  uint uVar4;
  char cVar5;
  byte *pbVar6;
  undefined1 *puVar7;
  byte *pbVar8;
  
  iVar2 = hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),param_4);
  if (*(char *)(param_1 + 0x7953fa) == '\0') {
    return 1;
  }
  cVar5 = '\x04';
  iVar1 = (short)param_4 * 0xda;
  puVar7 = (undefined1 *)(param_1 + iVar1 + 0x795136);
  do {
    puVar3 = puVar7 + 0x1e;
    do {
      puVar7 = puVar7 + 1;
      *puVar7 = 0xff;
    } while (puVar7 != puVar3);
    cVar5 = cVar5 + -1;
  } while (cVar5 != '\0');
  DfsBwChQueryAllList(param_1,2,param_1 + 0x795130,0,param_4);
  pbVar6 = (byte *)(param_1 + iVar1 + 0x795154);
  uVar4 = 0;
  do {
    pbVar8 = pbVar6 + -0x1e;
    do {
      pbVar8 = pbVar8 + 1;
      if ((*pbVar8 != 0xff) &&
         (param_3 == uVar4 && *(byte *)(iVar2 + (uint)*pbVar8 * 0x14) == param_2)) {
        return 1;
      }
    } while (pbVar6 != pbVar8);
    pbVar6 = pbVar6 + 0x1e;
    uVar4 = uVar4 + 1 & 0xff;
    if (uVar4 == 4) {
      return 0;
    }
  } while( true );
}

