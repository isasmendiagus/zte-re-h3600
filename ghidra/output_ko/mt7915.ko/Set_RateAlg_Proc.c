// module: mt7915.ko
// function: Set_RateAlg_Proc @ 0x1da948
// size: 164 bytes
//

undefined4 Set_RateAlg_Proc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  uint uVar4;
  bool bVar5;
  
  uVar1 = simple_strtol(param_2,0,10,param_4,param_4);
  if (uVar1 < 5) {
    if (*(uint *)(param_1 + 0x794ae0) != uVar1) {
      *(uint *)(param_1 + 0x794ae0) = uVar1;
      uVar4 = 0;
      puVar3 = (uint *)(param_1 + 0xa2898);
      while( true ) {
        uVar2 = HcGetMaxStaNum(param_1);
        bVar5 = uVar2 <= uVar4;
        uVar4 = uVar4 + 1;
        if (bVar5) break;
        *puVar3 = uVar1;
        puVar3 = puVar3 + 0x530;
      }
    }
  }
  if (-1 < DebugLevel) {
    printk("%s: Set Alg = %d\n","Set_RateAlg_Proc",uVar1);
  }
  return 1;
}

