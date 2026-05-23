// module: mt7915.ko
// function: Show_sta_tr_proc @ 0xe1840
// size: 112 bytes
//

undefined4 Show_sta_tr_proc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  bool bVar5;
  
  piVar4 = (int *)(param_1 + 0x2f6a0);
  iVar3 = 0;
  while( true ) {
    iVar2 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    bVar5 = SBORROW4(iVar3,0x120);
    iVar1 = iVar3 + -0x120;
    if (iVar3 != 0x120) {
      bVar5 = SBORROW4(iVar3,iVar2);
      iVar1 = iVar3 - iVar2;
    }
    if (iVar1 < 0 == bVar5) break;
    if ((piVar4 != (int *)0x0) && (*piVar4 != 0)) {
      TRTableEntryDump(param_1,iVar3,"Show_sta_tr_proc",0x21e1,param_4);
    }
    iVar3 = iVar3 + 1;
    piVar4 = piVar4 + 0x188;
  }
  return 1;
}

