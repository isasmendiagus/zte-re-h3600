// module: mt7915.ko
// function: HQA_AntennaSelExt @ 0x26dedc
// size: 236 bytes
//

undefined4 HQA_AntennaSelExt(int param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  
  uVar1 = *(uint *)(param_3 + 0xc);
  uVar2 = *(uint *)(param_3 + 0x10);
  uVar3 = *(uint *)(param_3 + 0x14);
  uVar6 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 | uVar1 >> 0x18;
  uVar5 = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 | uVar2 >> 0x18;
  uVar2 = *(uint *)(param_3 + 0x18);
  *(char *)(param_1 + 0xa3ae36) = (char)(uVar1 >> 0x18);
  uVar8 = uVar3 << 0x18 | (uVar3 >> 8 & 0xff) << 0x10 | (uVar3 >> 0x10 & 0xff) << 8 | uVar3 >> 0x18;
  uVar7 = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 | uVar2 >> 0x18;
  uVar1 = uVar5;
  uVar2 = uVar8;
  uVar3 = uVar7;
  uVar9 = uVar6;
  uVar4 = (**(code **)(*(int *)(param_1 + 0xa39fd4) + 0x114))(param_1,uVar5,uVar8,uVar7);
  if (0 < DebugLevel) {
    printk("%s: BandIdx:%x, RfModeMask:%x, RfPortMask:%x, AntPortMask:%x\n","HQA_AntennaSelExt",
           uVar6,uVar5,uVar8,uVar7,uVar1,uVar2,uVar3,uVar9);
  }
  FUN_0026cdd0(param_3,param_2,2,uVar4);
  return uVar4;
}

