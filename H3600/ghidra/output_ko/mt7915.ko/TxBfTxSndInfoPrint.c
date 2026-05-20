// module: mt7915.ko
// function: TxBfTxSndInfoPrint @ 0x87380
// size: 796 bytes
//

void TxBfTxSndInfoPrint(int param_1,undefined1 *param_2)

{
  int iVar1;
  uint uVar2;
  undefined1 *puVar3;
  uint uVar4;
  int iVar5;
  
  iVar1 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if ((DebugLevel < 1) ||
     (printk(
            "============================= Global Setting ========================================\n"
            ), DebugLevel < 1)) {
    uVar4 = (uint)(iVar1 << 0xb) >> 0x10;
    iVar1 = DebugLevel;
    if (uVar4 == 0) goto LAB_00087420;
LAB_000873c4:
    uVar2 = 0;
    iVar1 = DebugLevel;
    do {
      if (0 < iVar1) {
        printk("SuSta[%d] = 0x%08X, SuSta[%d] = 0x%08X, SuSta[%d] = 0x%08X, SuSta[%d] = 0x%08X\n",
               uVar2,*(undefined4 *)(param_2 + uVar2 * 4 + 4),uVar2 + 1,
               *(undefined4 *)(param_2 + uVar2 * 4 + 8),uVar2 + 2,
               *(undefined4 *)(param_2 + uVar2 * 4 + 0xc),uVar2 + 3,
               *(undefined4 *)(param_2 + uVar2 * 4 + 0x10));
        iVar1 = DebugLevel;
      }
      uVar2 = uVar2 + 4 & 0xffff;
    } while (uVar2 < uVar4);
    uVar2 = 0;
    do {
      if (0 < iVar1) {
        printk("VhtMuSta[%d] = 0x%08X, VhtMuSta[%d] = 0x%08X, VhtMuSta[%d] = 0x%08X, VhtMuSta[%d] = 0x%08X\n"
               ,uVar2,*(undefined4 *)(param_2 + uVar2 * 4 + 0x28),uVar2 + 1,
               *(undefined4 *)(param_2 + uVar2 * 4 + 0x2c),uVar2 + 2,
               *(undefined4 *)(param_2 + uVar2 * 4 + 0x30),uVar2 + 3,
               *(undefined4 *)(param_2 + uVar2 * 4 + 0x34));
        iVar1 = DebugLevel;
      }
      uVar2 = uVar2 + 4 & 0xffff;
    } while (uVar2 < uVar4);
    uVar2 = 0;
    do {
      if (0 < iVar1) {
        printk("HeTBSta[%d] = 0x%08X, HeTBSta[%d] = 0x%08X, HeTBSta[%d] = 0x%08X, HeTBSta[%d] = 0x%08X\n"
               ,uVar2,*(undefined4 *)(param_2 + uVar2 * 4 + 0x4c),uVar2 + 1,
               *(undefined4 *)(param_2 + uVar2 * 4 + 0x50),uVar2 + 2,
               *(undefined4 *)(param_2 + uVar2 * 4 + 0x54),uVar2 + 3,
               *(undefined4 *)(param_2 + uVar2 * 4 + 0x58));
        iVar1 = DebugLevel;
      }
      uVar2 = uVar2 + 4 & 0xffff;
    } while (uVar2 < uVar4);
  }
  else {
    uVar4 = (uint)(iVar1 << 0xb) >> 0x10;
    printk("VhtOpt = 0x%02X, HeOpt = 0x%02X, GloOpt = 0x%02X\n",*param_2,param_2[1],param_2[2]);
    iVar1 = DebugLevel;
    if (uVar4 != 0) goto LAB_000873c4;
  }
  if ((0 < iVar1) &&
     (printk("ULLen = %d, ULMcs = %d, ULLDCP = %d\n",*(undefined2 *)(param_2 + 0x70),param_2[0x72],
             param_2[0x73]), iVar1 = DebugLevel, 0 < DebugLevel)) {
    printk("============================= STA Info ========================================\n");
    iVar1 = DebugLevel;
  }
LAB_00087420:
  iVar5 = 1;
  puVar3 = param_2;
  do {
    if (0 < iVar1) {
      printk("AID%2u Interval = %d, CountDown = %d, TxCnt = %d, StopReason = 0x%02X\n",iVar5,
             puVar3[0x84],puVar3[0x85],puVar3[0x86],puVar3[0x87]);
      iVar1 = DebugLevel;
    }
    puVar3 = puVar3 + 4;
    iVar5 = iVar5 + 1;
  } while (puVar3 != param_2 + 0x10);
  if (0 < iVar1) {
    printk("============================= STA Info Connected ==============================\n");
  }
  uVar4 = 1;
  while( true ) {
    uVar2 = HcGetMaxStaNum(param_1);
    iVar1 = uVar4 * 0x14c0 + param_1;
    if (uVar2 <= uVar4) break;
    if ((*(int *)(iVar1 + 0xa1d20) != 0) && (0 < DebugLevel)) {
      printk("AID%2u Interval = %d, CountDown = %d, TxCnt = %d, StopReason = 0x%02X\n",
             *(undefined2 *)(iVar1 + 0xa1e18),param_2[uVar4 * 4 + 0x80],param_2[uVar4 * 4 + 0x81],
             param_2[uVar4 * 4 + 0x82],param_2[uVar4 * 4 + 0x83]);
    }
    uVar4 = uVar4 + 1 & 0xffff;
  }
  if (0 < DebugLevel) {
    printk("=====================================================================================\n"
          );
    return;
  }
  return;
}

