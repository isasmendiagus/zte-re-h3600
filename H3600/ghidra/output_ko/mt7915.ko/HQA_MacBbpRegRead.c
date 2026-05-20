// module: mt7915.ko
// function: HQA_MacBbpRegRead @ 0x26f5cc
// size: 168 bytes
//

undefined4 HQA_MacBbpRegRead(int param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  uint local_14;
  
  uVar1 = *(uint *)(param_3 + 0xc);
  uVar1 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 | uVar1 >> 0x18;
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar1,&local_14,param_1 + 0xa79000,uVar1);
  if (2 < DebugLevel) {
    printk("%s: Offset = %x, Value = %x\n","HQA_MacBbpRegRead",uVar1,local_14);
  }
  local_14 = local_14 << 0x18 | (local_14 >> 8 & 0xff) << 0x10 | (local_14 >> 0x10 & 0xff) << 8 |
             local_14 >> 0x18;
  *(uint *)(param_3 + 0xe) = local_14;
  FUN_0026cdd0(param_3,param_2,6,0);
  return 0;
}

