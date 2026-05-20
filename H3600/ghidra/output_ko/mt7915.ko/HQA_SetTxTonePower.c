// module: mt7915.ko
// function: HQA_SetTxTonePower @ 0x26e484
// size: 180 bytes
//

bool HQA_SetTxTonePower(int param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  code *pcVar3;
  uint uVar4;
  int iVar5;
  bool bVar6;
  
  uVar1 = *(uint *)(param_3 + 0xc);
  uVar2 = *(uint *)(param_3 + 0x10);
  iVar5 = *(int *)(param_1 + 0xa39fd4);
  uVar4 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 | uVar1 >> 0x18;
  uVar1 = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 | uVar2 >> 0x18;
  if (2 < DebugLevel) {
    printk("%s: pwr1:%d, pwr2:%d\n","HQA_SetTxTonePower",uVar4,uVar1);
  }
  pcVar3 = *(code **)(iVar5 + 0x8c);
  bVar6 = pcVar3 == (code *)0x0;
  if (!bVar6) {
    (*pcVar3)(param_1,uVar4,uVar1);
  }
  FUN_0026cdd0(param_3,param_2,2,bVar6);
  return bVar6;
}

