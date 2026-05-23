// module: mt7915.ko
// function: HQA_CalibrationTestMode @ 0x2748d8
// size: 428 bytes
//

undefined4 HQA_CalibrationTestMode(int param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  if (DebugLevel < 3) {
    uVar1 = *(uint *)(param_3 + 0xc);
    uVar2 = *(uint *)(param_3 + 0x10);
    uVar3 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 |
            uVar1 >> 0x18;
    uVar4 = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
            uVar2 >> 0x18;
    uVar1 = uVar3;
    uVar2 = uVar4;
  }
  else {
    printk(&_LC11,"HQA_CalibrationTestMode",param_3,0,0,0);
    uVar1 = *(uint *)(param_3 + 0xc);
    uVar2 = *(uint *)(param_3 + 0x10);
    uVar3 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 |
            uVar1 >> 0x18;
    uVar4 = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
            uVar2 >> 0x18;
    uVar1 = uVar3;
    uVar2 = uVar4;
    if (2 < DebugLevel) {
      printk("%s: mode = %X ICapLen= %X\n","HQA_CalibrationTestMode",uVar3,uVar4,uVar3,uVar4);
    }
  }
  if (uVar3 == 0) {
    uVar3 = 0;
    uVar1 = *(uint *)(param_1 + 0xa3ac14);
    if ((uVar1 & 0x280) != 0) {
      uVar1 = uVar1 & 0xfffffd7f;
    }
    *(uint *)(param_1 + 0xa3ac14) = uVar1 & 0xfffffdff;
  }
  else if ((uVar3 == 1) || (uVar3 == 2)) {
    *(uint *)(param_1 + 0xa3ac14) = *(uint *)(param_1 + 0xa3ac14) | 0x200;
  }
  else if (uVar3 == 3) {
    *(uint *)(param_1 + 0xa3ac14) = *(uint *)(param_1 + 0xa3ac14) | 0xa00;
  }
  else if (DebugLevel < 2) {
    uVar3 = 0;
  }
  else {
    printk("%s: Mode = %d error!!!\n","HQA_CalibrationTestMode",uVar3,DebugLevel,uVar1,uVar2);
    uVar3 = 0;
  }
  MtCmdRfTestSwitchMode(param_1,uVar3,uVar4 & 0xff,8);
  msleep(100);
  RcUpdateBandCtrl(*(undefined4 *)(param_1 + 0xa797a0));
  FUN_0026cdd0(param_3,param_2,2,0);
  return 0;
}

