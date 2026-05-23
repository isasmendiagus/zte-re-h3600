// module: mt7915.ko
// function: mt_op_reset_txrx_counter @ 0x257a1c
// size: 332 bytes
//

int mt_op_reset_txrx_counter(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar6;
  int iVar7;
  undefined4 *puVar5;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    return 0x503;
  }
  iVar7 = 0;
  puVar6 = (undefined4 *)(iVar1 + 0xa7c010);
  iVar2 = hc_get_chip_dbg(*(undefined4 *)(iVar1 + 0xa797a0));
  while( true ) {
    iVar3 = MtCmdSetPhyCounter(iVar1,0,iVar7);
    if ((iVar3 != 0) || (iVar3 = MtCmdSetPhyCounter(iVar1,1,iVar7), iVar3 != 0)) {
      printk("%s: reset tx rx phy counter fail(0x%08x).\n","mt_op_reset_txrx_counter",iVar3);
      return iVar3;
    }
    puVar4 = puVar6;
    do {
      puVar5 = puVar4 + 1;
      *puVar5 = 0;
      puVar4[-0x33] = 0;
      puVar4[-0x1f] = 0;
      puVar4 = puVar5;
    } while (puVar5 != puVar6 + 0x10);
    if (iVar2 != 0) {
      (**(code **)(iVar2 + 0xa4))(iVar1,iVar7,0,0);
      (**(code **)(iVar2 + 0xa4))(iVar1,iVar7,0,1);
      (**(code **)(iVar2 + 0xa4))(iVar1,iVar7,0,2);
      (**(code **)(iVar2 + 0xa4))(iVar1,iVar7,0,3);
      (**(code **)(iVar2 + 0xa4))(iVar1,iVar7,0xb,0);
    }
    puVar6 = puVar6 + 0x5a;
    if (iVar7 == 1) break;
    iVar7 = 1;
  }
  return 0;
}

