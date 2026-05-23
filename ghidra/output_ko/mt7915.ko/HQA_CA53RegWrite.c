// module: mt7915.ko
// function: HQA_CA53RegWrite @ 0x275350
// size: 172 bytes
//

undefined4 HQA_CA53RegWrite(undefined4 param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  
  uVar1 = *(uint *)(param_3 + 0xc);
  uVar2 = *(uint *)(param_3 + 0x10);
  uVar4 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 | uVar1 >> 0x18;
  uVar1 = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 | uVar2 >> 0x18;
  if (2 < DebugLevel) {
    printk("%s: offset = %lx, value = %x\n","HQA_CA53RegWrite",uVar4,uVar1,uVar4,uVar1);
  }
  uVar3 = __arm_ioremap(uVar4,0x10,0);
  sys_io_write32(uVar3,uVar1);
  __arm_iounmap(uVar3);
  FUN_0026cdd0(param_3,param_2,2,0);
  return 0;
}

