// module: mt7915.ko
// function: HQA_WriteEEPROM @ 0x2757c8
// size: 308 bytes
//

undefined4 HQA_WriteEEPROM(int param_1,undefined4 param_2,int param_3)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  int iVar4;
  ushort uVar5;
  ushort uVar6;
  
  if (2 < DebugLevel) {
    printk(&_LC11,"HQA_WriteEEPROM");
  }
  uVar2 = *(ushort *)(param_3 + 0xc) >> 8;
  uVar5 = *(ushort *)(param_3 + 0xc) << 8 | uVar2;
  uVar1 = *(ushort *)(param_3 + 0xe) & 0xff;
  uVar3 = *(ushort *)(param_3 + 0xe) >> 8;
  uVar6 = uVar1 << 8 | uVar3;
  iVar4 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar4 + 0xc) != (code *)0x0) {
    (**(code **)(iVar4 + 0xc))(param_1,uVar5,uVar6);
  }
  if (1 < DebugLevel) {
    printk("e2p w 0x%04X = 0x%04X\n",uVar5,uVar6);
    if (1 < DebugLevel) {
      printk("e2p w %02Xh = 0x%02X\n",uVar2,uVar3);
      if (1 < DebugLevel) {
        printk("e2p w %02Xh = 0x%02X\n",uVar2 + 1,uVar1);
      }
    }
  }
  FUN_0026cdd0(param_3,param_2,2,0);
  return 0;
}

