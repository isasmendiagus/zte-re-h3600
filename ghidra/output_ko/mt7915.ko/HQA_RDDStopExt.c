// module: mt7915.ko
// function: HQA_RDDStopExt @ 0x26d174
// size: 172 bytes
//

undefined4 HQA_RDDStopExt(int param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  
  uVar1 = *(uint *)(param_3 + 0xc);
  uVar2 = *(uint *)(param_3 + 0x10);
  uVar4 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 | uVar1 >> 0x18;
  uVar1 = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 | uVar2 >> 0x18;
  uVar3 = (**(code **)(*(int *)(param_1 + 0xa39fd4) + 0xe0))(param_1,uVar4,uVar1,0,uVar4,uVar1);
  FUN_0026cdd0(param_3,param_2,2,uVar3);
  if (2 < DebugLevel) {
    printk("%s: %x\n","HQA_RDDStopExt",uVar4);
  }
  return uVar3;
}

