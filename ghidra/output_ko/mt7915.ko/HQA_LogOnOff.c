// module: mt7915.ko
// function: HQA_LogOnOff @ 0x26cf54
// size: 536 bytes
//

undefined4 HQA_LogOnOff(int param_1,undefined4 param_2,int param_3)

{
  undefined1 uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined4 uVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  
  uVar2 = *(uint *)(param_3 + 0xc);
  uVar3 = *(uint *)(param_3 + 0x10);
  uVar4 = *(uint *)(param_3 + 0x14);
  uVar9 = uVar3 << 0x18 | (uVar3 >> 8 & 0xff) << 0x10 | (uVar3 >> 0x10 & 0xff) << 8 | uVar3 >> 0x18;
  uVar5 = *(uint *)(param_3 + 0x18);
  *(char *)(param_1 + 0xa3ae36) = (char)(uVar2 >> 0x18);
  uVar8 = uVar4 << 0x18 | (uVar4 >> 8 & 0xff) << 0x10 | (uVar4 >> 0x10 & 0xff) << 8 | uVar4 >> 0x18;
  uVar5 = uVar5 << 0x18 | (uVar5 >> 8 & 0xff) << 0x10 | (uVar5 >> 0x10 & 0xff) << 8 | uVar5 >> 0x18;
  if ((*(char *)(param_1 + 0xa3b889) == '\0') || (uVar9 != 3)) {
    *(undefined4 *)(param_1 + 0xa3ba98) = 2;
    uVar6 = (**(code **)(*(int *)(param_1 + 0xa39fd4) + 0x100))(param_1,uVar9,uVar8,uVar5);
    if (0 < DebugLevel) {
      printk("%s: band_idx:%x, log_type:%x, log_ctrl:%x, en_log:%x, log_size:%u\n","HQA_LogOnOff",
             uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
             uVar2 >> 0x18,uVar9,uVar8,*(undefined4 *)(param_1 + 0xa39ffc),uVar5);
    }
    if (uVar8 == 1) {
      uVar1 = (undefined1)(uVar4 >> 0x18);
      if (uVar9 == 2) {
        *(undefined1 *)(param_1 + 0xa3ba95) = uVar1;
      }
      else if (uVar9 == 3) {
        *(undefined1 *)(param_1 + 0xa3ba94) = uVar1;
      }
      else if (uVar9 == 1) {
        *(char *)(param_1 + 0xa3ba97) = (char)(uVar3 >> 0x18);
      }
    }
  }
  else {
    if (uVar8 == 1) {
      *(undefined4 *)(param_1 + 0xa3ba98) = 1;
      iVar7 = DebugLevel;
    }
    else if (uVar8 == 0) {
      *(undefined4 *)(param_1 + 0xa3ba98) = 0;
      *(undefined4 *)(param_1 + 0xa3ba9c) = 3;
      *(undefined4 *)(param_1 + 0xa3baa0) = 0;
      *(uint *)(param_1 + 0xa3baa4) = uVar5;
      iVar7 = DebugLevel;
    }
    else {
      if (0 < DebugLevel) {
        printk("%s: Shouldn\'t happen ! log_ctrl:%d\n","checkRecalInDumpStatus",uVar8);
      }
      iVar7 = DebugLevel;
      *(undefined4 *)(param_1 + 0xa3ba98) = 0;
    }
    if (0 < iVar7) {
      printk("%s: Recal Log dumping, log_ctrl:%d, log_type:%d, reCalInDumpSts:%d\n",
             "checkRecalInDumpStatus",uVar8,3,*(undefined4 *)(param_1 + 0xa3ba98));
    }
    uVar6 = 0;
  }
  FUN_0026cdd0(param_3,param_2,2,uVar6);
  return uVar6;
}

