// module: mt7915.ko
// function: dumpTxRing @ 0x1ca434
// size: 172 bytes
//

void dumpTxRing(int param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  uint uVar6;
  
  iVar1 = hif_get_tx_res_num(*(undefined4 *)(param_1 + 0xa797a0));
  iVar2 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar1 <= (int)param_2) {
    printk(&_LC16,0x50f);
    dump_stack();
  }
  iVar1 = *(int *)(*(int *)(iVar2 + 8) + (param_2 & 0xff) * 4);
  uVar6 = (uint)*(ushort *)(iVar1 + 0x5a);
  if (uVar6 == 0) {
    return;
  }
  iVar2 = 0;
  uVar4 = 0;
  do {
    iVar3 = *(int *)(iVar1 + 0xc) + iVar2;
    uVar4 = uVar4 + 1;
    iVar2 = iVar2 + 0x24;
    uVar5 = *(undefined4 *)(iVar3 + 4);
    hex_dump("Dump TxDesc",uVar5,0xc,iVar3,param_4);
    dump_txd(param_1,uVar5);
  } while (uVar6 != uVar4);
  return;
}

