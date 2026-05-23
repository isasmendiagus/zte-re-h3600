// module: mt7915.ko
// function: mt_ate_tx @ 0x2847c4
// size: 196 bytes
//

void mt_ate_tx(int param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  undefined4 *puVar5;
  undefined1 auStack_54 [60];
  
  uVar1 = HcGetBandByWdev(param_2);
  iVar2 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  piVar4 = *(int **)(param_3 + 0x40);
  puVar5 = *(undefined4 **)(param_1 + 0xa39fd0);
  if (piVar4 != (int *)0x0) {
    iVar3 = *piVar4;
    *piVar4 = 0;
    *(int *)(param_3 + 0x40) = iVar3;
    if (iVar3 == 0) {
      *(undefined4 *)(param_3 + 0x44) = 0;
    }
    *(int *)(param_3 + 0x48) = *(int *)(param_3 + 0x48) + -1;
  }
  *(int **)(param_3 + 0xc) = piVar4;
  *(undefined2 *)((int)piVar4 + 0x42) = 0;
  (*(code *)*puVar5)(param_1,param_2,param_3);
  iVar3 = mt_ate_set_tmac_info(param_1,auStack_54,uVar1);
  if (iVar3 == 0) {
    (**(code **)(iVar2 + 0x188))(param_1,auStack_54,param_3);
  }
  return;
}

