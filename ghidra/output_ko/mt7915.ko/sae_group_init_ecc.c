// module: mt7915.ko
// function: sae_group_init_ecc @ 0x207504
// size: 132 bytes
//

void sae_group_init_ecc(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (4 < DebugLevel) {
    printk("==> %s()\n","sae_group_init_ecc");
  }
  iVar1 = get_ecc_group_info(param_2);
  iVar2 = get_ecc_group_info_bi(param_2);
  if (iVar1 == 0 || iVar2 == 0) {
    return;
  }
  *(int *)(param_1 + 0x6c) = iVar1;
  *(int *)(param_1 + 0x70) = iVar2;
  *(undefined4 *)(param_1 + 0x74) = *(undefined4 *)(iVar2 + 4);
  *(undefined4 *)(param_1 + 100) = *(undefined4 *)(iVar1 + 8);
  *(undefined4 *)(param_1 + 0x78) = *(undefined4 *)(iVar2 + 8);
  uVar3 = *(undefined4 *)(iVar1 + 0x10);
  *(short *)(param_1 + 0x2c) = (short)param_2;
  *(undefined4 *)(param_1 + 0x68) = uVar3;
  return;
}

