// module: mt7915.ko
// function: HQA_GetTxTransmitted @ 0x26f678
// size: 128 bytes
//

undefined4 HQA_GetTxTransmitted(int param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = *(uint *)(param_1 + 0xa3ad80);
  if (2 < DebugLevel) {
    printk("%s(): TxDoneCount = %d\n","HQA_GetTxTransmitted",uVar1);
  }
  *(uint *)(param_3 + 0xe) =
       uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 | uVar1 >> 0x18;
  FUN_0026cdd0(param_3,param_2,6,0);
  return 0;
}

