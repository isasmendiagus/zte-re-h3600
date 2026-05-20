// module: mt7915.ko
// function: HQA_SetPerPktBW @ 0x26f7a0
// size: 140 bytes
//

undefined4 HQA_SetPerPktBW(int param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  
  uVar1 = *(uint *)(param_3 + 0xc);
  uVar2 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 | uVar1 >> 0x18;
  if (2 < DebugLevel) {
    printk("%s: %u\n","HQA_SetPerPktBW",uVar2);
  }
  bVar3 = *(byte *)(param_1 + 0xa3ad65);
  if (uVar2 <= bVar3) {
    bVar3 = (byte)(uVar1 >> 0x18);
  }
  *(byte *)(param_1 + 0xa3ad66) = bVar3;
  FUN_0026cdd0(param_3,param_2,2,0);
  return 0;
}

