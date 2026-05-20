// module: mt7915.ko
// function: HQA_MACBbpRegBulkRead @ 0x27b458
// size: 208 bytes
//

undefined4 HQA_MACBbpRegBulkRead(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  
  uVar1 = DebugLevel;
  DebugLevel = 1;
  uVar4 = (*(ushort *)(param_3 + 0x10) & 0xff) << 8 | (uint)(*(ushort *)(param_3 + 0x10) >> 8);
  uVar2 = *(uint *)(param_3 + 0xc);
  uVar2 = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 | uVar2 >> 0x18;
  if (uVar4 < 0x174) {
    RTMP_IO_READ_BULK(param_1,param_3 + 0xe,uVar2,uVar4 * 4);
    FUN_0026cdd0(param_3,param_2,uVar4 * 4 + 2,0);
    uVar3 = 0;
    DebugLevel = uVar1;
  }
  else {
    printk("%s: length requested is too large, make it smaller\n","HQA_MACBbpRegBulkRead",uVar2,
           uVar4,(short)uVar4,uVar2);
    uVar3 = 0xfffffff2;
    *(undefined1 *)(param_3 + 8) = 0;
    *(undefined1 *)(param_3 + 9) = 2;
    *(undefined2 *)(param_3 + 0xc) = 0x100;
  }
  return uVar3;
}

