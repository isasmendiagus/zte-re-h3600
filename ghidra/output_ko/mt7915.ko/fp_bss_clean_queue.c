// module: mt7915.ko
// function: fp_bss_clean_queue @ 0xd5284
// size: 132 bytes
//

undefined4 fp_bss_clean_queue(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar4 = param_1 + 0x285b4c;
  iVar5 = param_1 + 0x285b3c;
  do {
    fp_qm_leave_queue_pkt(param_2,iVar4,iVar4 + 0x20,iVar5,iVar5 + 8);
    iVar6 = iVar5 + -8;
    iVar1 = iVar4 + -0x60;
    iVar2 = iVar4 + -0x40;
    iVar3 = iVar5 + -0x10;
    iVar4 = iVar4 + 0x10;
    iVar5 = iVar5 + 4;
    fp_qm_leave_queue_pkt(param_2,iVar1,iVar2,iVar3,iVar6);
  } while (iVar4 != param_1 + 0x285b6c);
  return 0;
}

