// module: mt7915.ko
// function: HQA_MacBbpRegWrite @ 0x275bec
// size: 164 bytes
//

undefined4 HQA_MacBbpRegWrite(int param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar1 = *(uint *)(param_3 + 0xc);
  uVar2 = *(uint *)(param_3 + 0x10);
  uVar3 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 | uVar1 >> 0x18;
  uVar1 = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 | uVar2 >> 0x18;
  if (2 < DebugLevel) {
    printk("%s: Offset = %x, Value = %x\n","HQA_MacBbpRegWrite",uVar3,uVar1,uVar3,uVar1);
  }
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),uVar3,uVar1);
  FUN_0026cdd0(param_3,param_2,2,0);
  return 0;
}

