// module: mt7915.ko
// function: ZTE_clear_pkt_stat @ 0x15b6f4
// size: 124 bytes
//

undefined4 ZTE_clear_pkt_stat(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  byte bVar1;
  undefined4 extraout_r1;
  undefined4 extraout_r2;
  undefined4 extraout_r2_00;
  int *piVar2;
  int *extraout_r3;
  int *extraout_r3_00;
  int *piVar3;
  uint uVar4;
  bool bVar5;
  undefined8 uVar6;
  
  piVar2 = (int *)*param_1;
  piVar3 = param_1 + 0x28748;
  uVar4 = 0;
  bVar1 = *(byte *)(piVar2 + 0xf);
  while( true ) {
    uVar6 = HcGetMaxStaNum(param_1,param_2,param_3,piVar2,param_4);
    param_2 = (undefined4)((ulonglong)uVar6 >> 0x20);
    bVar5 = (uint)uVar6 <= uVar4;
    uVar4 = uVar4 + 1;
    if (bVar5) break;
    piVar2 = extraout_r3;
    param_3 = extraout_r2;
    if (((piVar3 != (int *)0x0) && (piVar2 = (int *)0x0, *piVar3 != 0)) &&
       (piVar2 = (int *)(uint)*(byte *)((int)piVar3 + 0xe5), piVar2 == (int *)(uint)bVar1)) {
      piVar2 = piVar3 + 0x520;
      param_2 = 0x1040;
      if (piVar3[0x52c] != 0) {
        __memzero();
        param_2 = extraout_r1;
        piVar2 = extraout_r3_00;
        param_3 = extraout_r2_00;
      }
    }
    piVar3 = piVar3 + 0x530;
  }
  return 1;
}

