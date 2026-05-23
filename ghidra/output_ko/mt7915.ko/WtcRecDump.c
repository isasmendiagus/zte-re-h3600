// module: mt7915.ko
// function: WtcRecDump @ 0xae040
// size: 328 bytes
//

void WtcRecDump(int param_1)

{
  char cVar1;
  undefined2 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  char *pcVar6;
  int iVar7;
  char *apcStack_24 [3];
  
  iVar7 = *(int *)(param_1 + 0x4328);
  iVar3 = hc_get_chip_wtbl_max_num(*(undefined4 *)(iVar7 + 0xa797a0));
  apcStack_24[0] = "None";
  apcStack_24[1] = "Ucast";
  apcStack_24[2] = "Mcast";
  if (0 < DebugLevel) {
    printk("\tWtblRecDump:\n");
    if (0 < DebugLevel) {
      uVar4 = hc_get_chip_wtbl_max_num(*(undefined4 *)(iVar7 + 0xa797a0));
      uVar5 = hc_get_chip_wtbl_no_matched_idx(*(undefined4 *)(iVar7 + 0xa797a0));
      printk("\t  ChipCap MaxEntries:%d, NoMatched:%x\n",uVar4,uVar5);
      if (0 < DebugLevel) {
        printk("\t  WtblCfg MaxUcEntryNum:%d, MinMcWcid:%d, MAX_MAC_TABLE:%d\n",
               *(undefined2 *)(param_1 + 0x1a28),*(undefined2 *)(param_1 + 0x1a2a),0x120);
      }
    }
  }
  if (iVar3 != 0) {
    pcVar6 = (char *)(param_1 + 0x1a30);
    do {
      if ((*pcVar6 == '\x01') && (0 < DebugLevel)) {
        uVar2 = *(undefined2 *)(pcVar6 + 4);
        cVar1 = pcVar6[1];
        uVar4 = wdev_type2str(pcVar6[2]);
        printk("\tWcid[%03d] used by OM:%02x(%s), Type:%s\n",uVar2,cVar1,uVar4,
               apcStack_24[(byte)pcVar6[6]]);
      }
      pcVar6 = pcVar6 + 0x10;
    } while (pcVar6 != (char *)(param_1 + ((iVar3 - 1U & 0xffff) + 0x1a4) * 0x10));
  }
  return;
}

