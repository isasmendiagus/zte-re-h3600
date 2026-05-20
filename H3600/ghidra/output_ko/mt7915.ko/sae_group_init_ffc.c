// module: mt7915.ko
// function: sae_group_init_ffc @ 0x2073b4
// size: 204 bytes
//

/* WARNING: Removing unreachable block (ram,0x002073f0) */

void sae_group_init_ffc(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  
  if (4 < DebugLevel) {
    printk("==> %s()\n","sae_group_init_ffc",param_3,DebugLevel,param_4);
  }
  iVar1 = _LANCHOR1;
  if (_LANCHOR1 == param_2) {
    uVar5 = (uint)bRam005dfeed;
    if (uVar5 == 0) {
      uRam005dfee0 = uVar5;
      uRam005dfee4 = uVar5;
      uRam005dfee8 = uVar5;
      Bignum_Bin2BI(uRam005dfec8,uRam005dfecc,0x5dfee4);
      Bignum_Bin2BI(uRam005dfed0,uRam005dfed4,0x5dfee8);
      Bignum_Bin2BI(uRam005dfec0,uRam005dfec4,0x5dfee0);
    }
    uVar4 = uRam005dfee8;
    uVar5 = uRam005dfee4;
    uVar3 = uRam005dfed4;
    uVar2 = uRam005dfecc;
    *(int **)(param_1 + 0x6c) = &_LANCHOR1;
    *(undefined4 *)(param_1 + 0x70) = 0x5dfedc;
    *(short *)(param_1 + 0x2c) = (short)iVar1;
    *(uint *)(param_1 + 0x74) = uVar5;
    *(undefined4 *)(param_1 + 100) = uVar2;
    *(uint *)(param_1 + 0x78) = uVar4;
    *(undefined4 *)(param_1 + 0x68) = uVar3;
    return;
  }
  return;
}

