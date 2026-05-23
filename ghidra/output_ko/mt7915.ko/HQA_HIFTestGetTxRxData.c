// module: mt7915.ko
// function: HQA_HIFTestGetTxRxData @ 0x274080
// size: 288 bytes
//

undefined4 HQA_HIFTestGetTxRxData(undefined4 param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint local_30;
  uint local_2c;
  
  local_30 = 0;
  LoopBack_RawData(param_1,&local_30,1,param_3 + 0x12);
  uVar1 = local_30;
  local_2c = local_30 << 0x18 | (local_30 >> 8 & 0xff) << 0x10 | (local_30 >> 0x10 & 0xff) << 8 |
             local_30 >> 0x18;
  iVar3 = local_30 + 4;
  iVar2 = param_3 + 0xe + iVar3;
  *(uint *)(param_3 + 0xe) = local_2c;
  if (DebugLevel < 1) {
    LoopBack_RawData(param_1,&local_30,0,iVar2 + 4);
  }
  else {
    printk("%s: tx_out_len:%u\n","HQA_HIFTestGetTxRxData",local_30);
    LoopBack_RawData(param_1,&local_30,0,iVar2 + 4);
  }
  local_2c = local_30 << 0x18 | (local_30 >> 8 & 0xff) << 0x10 | (local_30 >> 0x10 & 0xff) << 8 |
             local_30 >> 0x18;
  iVar2 = local_30 + uVar1;
  *(uint *)(param_3 + 0xe + iVar3) = local_2c;
  if (0 < DebugLevel) {
    printk("%s: rx_out_len:%u, total_len:%u\n","HQA_HIFTestGetTxRxData",local_30,iVar2);
  }
  FUN_0026cdd0(param_3,param_2,iVar2 + 10,0);
  return 0;
}

