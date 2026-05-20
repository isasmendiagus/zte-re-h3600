// module: mt7915.ko
// function: HQA_CMDHandler @ 0x27b6d8
// size: 280 bytes
//

undefined4 HQA_CMDHandler(undefined4 param_1,undefined4 param_2,int *param_3)

{
  ushort uVar1;
  undefined *puVar2;
  code *pcVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;
  uint *puVar7;
  int *piVar8;
  
  if (*param_3 != -0x7fd7ebe8) {
    return 1;
  }
  uVar1 = *(ushort *)((int)param_3 + 6);
  uVar4 = (uVar1 & 0xff) << 8 | (uint)(uVar1 >> 8);
  if (3 < DebugLevel) {
    printk("%s: --> Command_Id = 0x%04x, testmode_ioctl\n","HQA_CMDHandler",uVar4);
  }
  puVar2 = &UNK_002a6a5c;
  iVar6 = 0;
  do {
    puVar7 = (uint *)(puVar2 + 4);
    piVar8 = (int *)(puVar2 + 8);
    puVar2 = puVar2 + 0xc;
    if (uVar4 - *piVar8 < *puVar7) {
      pcVar3 = *(code **)(*(int *)(&UNK_002a6a5c + iVar6 * 0xc) + (uVar4 - *piVar8) * 4);
      if (pcVar3 == (code *)0x0) {
        uVar5 = 0;
      }
      else {
        uVar5 = (*pcVar3)(param_1,param_2,param_3);
      }
      goto LAB_0027b750;
    }
    iVar6 = iVar6 + 1;
  } while (iVar6 != 0xf);
  uVar5 = 0;
LAB_0027b750:
  if (uVar4 == 5) {
    *(char *)(param_3 + 1) = (char)(uVar1 >> 8);
  }
  *(undefined1 *)((int)param_3 + 5) = 0x80;
  iVar6 = DebugLevel;
  if (uVar4 != 5) {
    *(undefined1 *)(param_3 + 1) = 8;
  }
  if (2 < iVar6) {
    printk("%s: Command_Id = 0x%04x, testmode_ioctl <--\n","HQA_CMDHandler",uVar4);
    return uVar5;
  }
  return uVar5;
}

