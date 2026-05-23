// module: mt7915.ko
// function: HQA_CA53RegRead @ 0x275400
// size: 172 bytes
//

undefined4 HQA_CA53RegRead(undefined4 param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint local_14;
  
  uVar1 = *(uint *)(param_3 + 0xc);
  uVar2 = __arm_ioremap(uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 |
                        uVar1 >> 0x18,0x10,0);
  uVar3 = uVar2;
  sys_io_read32(uVar2,&local_14);
  __arm_iounmap(uVar2);
  if (2 < DebugLevel) {
    printk("%s: offset = %lx, value = %x\n","HQA_CA53RegRead",uVar2,local_14,uVar3);
  }
  local_14 = local_14 << 0x18 | (local_14 >> 8 & 0xff) << 0x10 | (local_14 >> 0x10 & 0xff) << 8 |
             local_14 >> 0x18;
  *(uint *)(param_3 + 0xe) = local_14;
  FUN_0026cdd0(param_3,param_2,6,0);
  return 0;
}

