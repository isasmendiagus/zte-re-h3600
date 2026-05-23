// module: mt7915.ko
// function: MecInfoAmsduEnPrint @ 0x1a7490
// size: 328 bytes
//

void MecInfoAmsduEnPrint(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  
  iVar1 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (DebugLevel < 1) {
    uVar4 = (uint)(iVar1 << 0xb) >> 0x10;
    if (uVar4 == 0) goto LAB_001a74f4;
LAB_001a74d0:
    uVar3 = 0;
    iVar1 = DebugLevel;
    do {
      if (0 < iVar1) {
        printk("     au4MecAlgoEnSta[%u]: 0x%08X\n",uVar3,*(undefined4 *)(param_2 + uVar3 * 4));
        iVar1 = DebugLevel;
      }
      uVar3 = uVar3 + 1;
    } while ((uVar3 & 0xffff) < uVar4);
  }
  else {
    uVar4 = (uint)(iVar1 << 0xb) >> 0x10;
    uVar2 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    printk("[+] AMSDU Algo Enable Status for all %u STAs (sync %u)\n",uVar2,0x120);
    iVar1 = DebugLevel;
    if (uVar4 != 0) goto LAB_001a74d0;
  }
  if (0 < iVar1) {
    printk("[+] Connected STA AMSDU Algo Enable Status\n");
  }
LAB_001a74f4:
  uVar4 = 1;
  while( true ) {
    uVar3 = HcGetMaxStaNum(param_1);
    iVar1 = uVar4 * 0x14c0 + param_1;
    if (uVar3 <= uVar4) break;
    if ((*(int *)(iVar1 + 0xa1d20) != 0) && (0 < DebugLevel)) {
      printk("     WlanIdx %2u, AID %2u, AMSDU Algo Enable: %u\n",uVar4,
             *(undefined2 *)(iVar1 + 0xa1e18),
             (*(uint *)(param_2 + (uVar4 >> 5) * 4) & 1 << (uVar4 & 0x1f)) >> (uVar4 & 0xff) & 0xff,
             param_4);
    }
    uVar4 = uVar4 + 1 & 0xffff;
  }
  return;
}

