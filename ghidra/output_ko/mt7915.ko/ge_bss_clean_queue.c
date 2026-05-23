// module: mt7915.ko
// function: ge_bss_clean_queue @ 0xd36f8
// size: 168 bytes
//

undefined4 ge_bss_clean_queue(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  bool bVar6;
  
  qm_leave_queue_pkt(param_2,param_1 + 0x285b4c,param_1 + 0x285b3c);
  iVar3 = param_1 + 0x2f6c4;
  iVar2 = 0;
  while( true ) {
    iVar1 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    bVar6 = SBORROW4(iVar2,0x120);
    iVar4 = iVar2 + -0x120;
    if (iVar2 != 0x120) {
      bVar6 = SBORROW4(iVar2,iVar1);
      iVar4 = iVar2 - iVar1;
    }
    if (iVar4 < 0 == bVar6) break;
    if (*(int *)(iVar3 + -0x20) == param_2) {
      iVar1 = iVar3 + 0x70;
      iVar4 = iVar3;
      do {
        iVar5 = iVar4 + 0x10;
        qm_leave_queue_pkt(param_2,iVar4,iVar1);
        iVar1 = iVar1 + 4;
        iVar4 = iVar5;
      } while (iVar5 != iVar3 + 0x40);
    }
    iVar2 = iVar2 + 1;
    iVar3 = iVar3 + 0x620;
  }
  return 0;
}

