// module: mt7915.ko
// function: DfsBuildChannelList @ 0x232418
// size: 500 bytes
//

void DfsBuildChannelList(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined1 uVar8;
  
  if (param_2 == 0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("[%s]: wdev is NULL.\n","DfsBuildChannelList");
    return;
  }
  if ((*(ushort *)(param_2 + 0x18) & 0xb1) != 0) {
    iVar2 = HcGetBandByWdev(param_2);
    iVar3 = hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),iVar2);
    if ((*(char *)(param_1 + 0x790000 + iVar2 + 0x53e9) == '\x01') &&
       (cVar1 = *(char *)(iVar3 + 0x49c), cVar1 != '\0')) {
      iVar7 = iVar3 + 8;
      iVar6 = iVar3;
      do {
        *(undefined1 *)(iVar6 + 8) = 0;
        uVar8 = *(undefined1 *)(iVar7 + -8);
        iVar4 = FUN_0022f884(uVar8,0,iVar3);
        if (iVar4 != 0) {
          *(undefined1 *)(iVar6 + 8) = 1;
          uVar8 = *(undefined1 *)(iVar7 + -8);
        }
        iVar4 = FUN_0022f884(uVar8,1,iVar3);
        if (iVar4 != 0) {
          *(byte *)(iVar6 + 8) = *(byte *)(iVar6 + 8) | 2;
          uVar8 = *(undefined1 *)(iVar7 + -8);
        }
        iVar4 = FUN_0022f884(uVar8,2,iVar3);
        if ((iVar4 != 0) || (iVar4 = FUN_0022f884(uVar8,6,iVar3), iVar4 != 0)) {
          *(byte *)(iVar6 + 8) = *(byte *)(iVar6 + 8) | 4;
          uVar8 = *(undefined1 *)(iVar7 + -8);
        }
        iVar5 = iVar6 + 0x14;
        iVar4 = FUN_0022f884(uVar8,3,iVar3);
        iVar7 = iVar7 + 0x14;
        if (iVar4 != 0) {
          *(byte *)(iVar6 + 8) = *(byte *)(iVar6 + 8) | 8;
        }
        iVar6 = iVar5;
      } while (iVar5 != iVar3 + ((byte)(cVar1 - 1) + 1) * 0x14);
    }
    DfsBuildChannelGroupByBw(param_1,param_2);
    if (0 < DebugLevel) {
      printk("%s(): Done\n","DfsBuildChannelList");
    }
    *(undefined1 *)(param_1 + 0x790000 + iVar2 + 0x53e9) = 0;
    return;
  }
  if (DebugLevel < 3) {
    return;
  }
  printk("[%s]: wdev is not 5G \n","DfsBuildChannelList");
  return;
}

