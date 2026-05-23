// module: mt7915.ko
// function: ZTE_tx_ctrl_rate_insert @ 0x15bcd8
// size: 212 bytes
//

void ZTE_tx_ctrl_rate_insert(uint *param_1,uint param_2,uint param_3)

{
  uint *puVar1;
  uint uVar2;
  int iVar3;
  
  uVar2 = *param_1;
  if (uVar2 == 0x200) {
    if (1 < DebugLevel) {
      printk("%s, ratesData has no more place\n","ZTE_tx_ctrl_rate_insert");
      return;
    }
    return;
  }
  if (uVar2 < param_3) {
    if (1 < DebugLevel) {
      printk("%s, index error\n","ZTE_tx_ctrl_rate_insert");
      return;
    }
    return;
  }
  if (uVar2 == param_3) {
    param_1[uVar2 * 2 + 2] = param_2;
    param_1[uVar2 * 2 + 1] = 1;
    *param_1 = uVar2 + 1;
    return;
  }
  iVar3 = uVar2 - 1;
  if ((int)param_3 <= iVar3) {
    puVar1 = param_1 + uVar2 * 2;
    do {
      iVar3 = iVar3 + -1;
      puVar1[2] = *puVar1;
      puVar1[1] = puVar1[-1];
      puVar1 = puVar1 + -2;
    } while ((int)param_3 <= iVar3);
  }
  param_1[param_3 * 2 + 2] = param_2;
  param_1[param_3 * 2 + 1] = 1;
  *param_1 = uVar2 + 1;
  return;
}

