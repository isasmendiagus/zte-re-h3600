// module: mt7915.ko
// function: mtf_dump_dmac_amsdu_info @ 0x19d038
// size: 444 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4 mtf_dump_dmac_amsdu_info(int param_1)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  uint uVar5;
  char *pcVar6;
  undefined4 local_38 [8];
  
  puVar4 = local_38;
  local_38[0] = 0;
  local_38[1] = 0;
  local_38[2] = 0;
  local_38[3] = 0;
  local_38[4] = 0;
  local_38[5] = 0;
  local_38[6] = 0;
  local_38[7] = 0;
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x90e0,local_38);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x90e4,local_38 + 1);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x90e8,local_38 + 2);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x90ec,local_38 + 3);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x90f0,local_38 + 4);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x90f4,local_38 + 5);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x90f8,local_38 + 6);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x90fc,local_38 + 7);
  if (0 < DebugLevel) {
    printk("=== HW_AMSDU INFO.===\n");
  }
  iVar2 = 1;
  do {
    if (0 < DebugLevel) {
      printk("PACK_%d_MSDU_CNT=%d\n",iVar2,*puVar4);
    }
    iVar2 = iVar2 + 1;
    puVar4 = puVar4 + 1;
  } while (iVar2 != 9);
  piVar3 = (int *)(param_1 + 0xa1e1c);
  pcVar6 = (char *)(param_1 + 0x2f762);
  for (uVar5 = 0; uVar1 = HcGetMaxStaNum(param_1), uVar5 < uVar1; uVar5 = uVar5 + 1) {
    if ((((piVar3[-0x3f] != 0) && (*piVar3 == 2)) && (*pcVar6 == '\x01')) &&
       ((*(short *)((int)piVar3 + 0xbc6) != 0 && (0 < DebugLevel)))) {
      printk("Wcid%03d: %02x",uVar5);
    }
    piVar3 = piVar3 + 0x530;
    pcVar6 = pcVar6 + 0x620;
  }
  return 1;
}

