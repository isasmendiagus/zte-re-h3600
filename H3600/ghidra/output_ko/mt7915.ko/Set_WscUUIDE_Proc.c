// module: mt7915.ko
// function: Set_WscUUIDE_Proc @ 0x590ac
// size: 680 bytes
//

undefined4 Set_WscUUIDE_Proc(int *param_1,char *param_2)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  size_t sVar5;
  int iVar6;
  int iVar7;
  byte *pbVar8;
  char *pcVar9;
  int iVar10;
  undefined4 local_84;
  uint uStack_80;
  uint uStack_7c;
  undefined4 uStack_78;
  byte local_74 [37];
  char acStack_4f [43];
  
  iVar10 = *(int *)(*param_1 + 0x3c);
  sVar5 = strlen(param_2);
  if (sVar5 == 0x20) {
    memcpy(local_74,param_2,0x20);
    iVar7 = 0;
    pbVar8 = (byte *)((int)&uStack_78 + 3);
    do {
      pbVar8 = pbVar8 + 1;
      if (((&_ctype)[*pbVar8] & 0x44) == 0) {
        if (DebugLevel < 0) {
          return 0;
        }
        printk("Input %d not Hex Value\n");
        return 0;
      }
      iVar7 = iVar7 + 1;
    } while (iVar7 != 0x20);
    AtoH(local_74,&local_84,0x10);
    uVar4 = uStack_78;
    uVar3 = uStack_7c;
    uVar2 = uStack_80;
    uVar1 = local_84;
    __memzero(acStack_4f,0x27);
    sprintf(acStack_4f,"%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",uVar1,uVar2 & 0xffff,
            uVar2 >> 0x10,uVar3 & 0xff,uVar3 >> 8 & 0xff,uVar3 >> 0x10 & 0xff,uVar3 >> 0x18,
            uVar4 & 0xff,uVar4 >> 8 & 0xff,uVar4 >> 0x10 & 0xff,uVar4 >> 0x18);
    sVar5 = strlen(acStack_4f);
    if ((0x25 < sVar5) && (-1 < DebugLevel)) {
      printk("ERROR:UUID String size too large!\n");
    }
    iVar7 = iVar10 * 0x2137b0;
    strncpy((char *)(param_1 + iVar10 * 0x84dec + 0xdc61c),acStack_4f,0x25);
    *(undefined1 *)(param_1 + iVar10 * 0x84dec + 0xdc625) = 0;
    *(undefined4 *)((int)param_1 + (int)(s_QUEUE_INFO_00371858 + iVar7 + 8)) = local_84;
    iVar6 = DebugLevel;
    *(uint *)((int)param_1 + (int)(s_QUEUE_INFO_00371858 + iVar7 + 0xc)) = uStack_80;
    *(uint *)((int)param_1 + (int)(s_QUEUE_INFO_00371858 + iVar7 + 0x10)) = uStack_7c;
    *(uint *)((int)param_1 + (int)(s_QUEUE_INFO_00371858 + iVar7 + 0x14)) = uStack_78;
    if (2 < iVar6) {
      printk("The UUID Hex string is:");
      iVar6 = DebugLevel;
    }
    pcVar9 = (char *)((int)param_1 + (int)(s_QUEUE_INFO_00371858 + iVar10 * 0x2137b0 + 8));
    do {
      if (2 < iVar6) {
        printk(&_LC51,*pcVar9);
        iVar6 = DebugLevel;
      }
      pcVar9 = pcVar9 + 1;
    } while (pcVar9 != (char *)((int)param_1 +
                               (int)(s_QUE_SIZE_PEAK_CURR_00371864 + iVar10 * 0x2137b0 + 0xc)));
    if ((2 < iVar6) && (printk(&_LC52), 2 < DebugLevel)) {
      printk("The UUID ASCII string is:%s!\n",param_1 + iVar10 * 0x84dec + 0xdc61c);
    }
  }
  else if (-1 < DebugLevel) {
    printk("Length of UUID key is wrong length=%d\n",sVar5);
  }
  return 0;
}

