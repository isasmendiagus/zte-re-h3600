// module: mt7915.ko
// function: HQA_SetRXVectorIdx @ 0x275d60
// size: 196 bytes
//

undefined4 HQA_SetRXVectorIdx(int param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar1 = *(uint *)(param_3 + 0xc);
  uVar2 = *(uint *)(param_3 + 0x10);
  uVar3 = *(uint *)(param_3 + 0x14);
  *(char *)(param_1 + 0xa3ae36) = (char)(uVar1 >> 0x18);
  MtCmdSetRxvIndex(param_1,uVar2 >> 0x18,uVar3 >> 0x18);
  if (2 < DebugLevel) {
    printk("%s: band_idx:%d, G1:%d, G2:%d\n","HQA_SetRXVectorIdx",
           uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 | uVar1 >> 0x18
           ,uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
            uVar2 >> 0x18,
           uVar3 << 0x18 | (uVar3 >> 8 & 0xff) << 0x10 | (uVar3 >> 0x10 & 0xff) << 8 | uVar3 >> 0x18
          );
  }
  FUN_0026cdd0(param_3,param_2,2,0);
  return 0;
}

