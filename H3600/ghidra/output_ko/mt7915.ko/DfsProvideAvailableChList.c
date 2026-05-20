// module: mt7915.ko
// function: DfsProvideAvailableChList @ 0x2373a4
// size: 324 bytes
//

void DfsProvideAvailableChList(int param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  undefined1 *puVar3;
  char cVar4;
  byte *pbVar5;
  byte *pbVar6;
  int iVar7;
  undefined1 *puVar8;
  
  iVar1 = hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  cVar4 = '\x04';
  iVar7 = (short)param_2 * 0xda;
  puVar3 = (undefined1 *)(param_1 + iVar7 + 0x795136);
  do {
    puVar8 = puVar3 + 0x1e;
    do {
      puVar3 = puVar3 + 1;
      *puVar3 = 0xff;
    } while (puVar3 != puVar8);
    cVar4 = cVar4 + -1;
  } while (cVar4 != '\0');
  if ((*(char *)(param_1 + 0xa37728) != '\x01') && (*(char *)(param_1 + 0xa37748) != '\x01')) {
    DfsBwChQueryAllList(param_1,2,param_1 + 0x795130,1,param_2);
    pbVar6 = (byte *)(param_1 + iVar7 + 0x795154);
    iVar7 = 0;
    do {
      if (0 < DebugLevel) {
        printk("Bw: %d\n",iVar7);
      }
      pbVar5 = pbVar6 + -0x1e;
      do {
        pbVar5 = pbVar5 + 1;
        uVar2 = (uint)*pbVar5;
        if ((uVar2 != 0xff) && (0 < DebugLevel)) {
          printk("ChannelList[%d], Ch %d, RadarHitCnt: %d\n",uVar2,
                 *(undefined1 *)(iVar1 + uVar2 * 0x14),*(undefined1 *)(iVar1 + uVar2 * 0x14 + 7));
        }
      } while (pbVar5 != pbVar6);
      iVar7 = iVar7 + 1;
      pbVar6 = pbVar6 + 0x1e;
    } while (iVar7 != 4);
  }
  return;
}

