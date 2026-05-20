// module: mt7915.ko
// function: query_tx_burst_prio @ 0xc7c30
// size: 172 bytes
//

uint query_tx_burst_prio(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  if ((param_2 == 0) || (iVar2 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0)), iVar2 != 2))
  {
    uVar5 = 0;
  }
  else {
    uVar4 = 0;
    uVar5 = 0;
    do {
      uVar1 = uVar4 & 0xff;
      uVar3 = uVar4 & 0xff;
      uVar4 = uVar4 + 1;
      if ((*(uint *)(param_2 + 0x9b0) & 1 << uVar1) != 0) {
        uVar5 = uVar3;
      }
    } while (uVar4 != 10);
    if (2 < DebugLevel) {
      printk("%s, curr: prio=%d, txop=0x%x, <caller: %pS>\n","query_tx_burst_prio",uVar5,
             *(undefined2 *)(param_2 + (uVar5 + 0x4d8) * 2 + 4));
    }
  }
  return uVar5;
}

