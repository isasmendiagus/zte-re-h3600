// module: mt7915.ko
// function: Clear_All_PROXY_TABLE @ 0x228b50
// size: 376 bytes
//

void Clear_All_PROXY_TABLE(int *param_1)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  int *piVar4;
  int *piVar5;
  
  uVar3 = (uint)*(byte *)(*param_1 + 0x3c);
  _raw_spin_lock_bh(param_1 + uVar3 * 0x160d + 0xaefba);
  piVar4 = param_1 + uVar3 * 0x160d + 0xaefbc;
  piVar2 = *(int **)param_1[uVar3 * 0x160d + 0xaefbc];
  piVar1 = (int *)param_1[uVar3 * 0x160d + 0xaefbc];
  while (piVar5 = piVar2, piVar1 != piVar4) {
    if (piVar5 != (int *)0x0) {
      piVar5[1] = piVar1[1];
    }
    if ((int *)piVar1[1] != (int *)0x0) {
      *(int *)piVar1[1] = *piVar1;
    }
    *piVar1 = 0;
    piVar1[1] = 0;
    os_free_mem(piVar1);
    piVar2 = (int *)*piVar5;
    piVar1 = piVar5;
  }
  piVar5 = param_1 + uVar3 * 0x160d + 0xaefbe;
  param_1[uVar3 * 0x160d + 0xaefbc] = (int)piVar4;
  param_1[uVar3 * 0x160d + 0xaefbd] = (int)piVar4;
  _raw_spin_unlock_bh(param_1 + uVar3 * 0x160d + 0xaefba);
  _raw_spin_lock_bh(param_1 + uVar3 * 0x160d + 0xaefbb);
  piVar2 = *(int **)param_1[uVar3 * 0x160d + 0xaefbe];
  piVar1 = (int *)param_1[uVar3 * 0x160d + 0xaefbe];
  while (piVar4 = piVar2, piVar1 != piVar5) {
    if (piVar4 != (int *)0x0) {
      piVar4[1] = piVar1[1];
    }
    if ((int *)piVar1[1] != (int *)0x0) {
      *(int *)piVar1[1] = *piVar1;
    }
    *piVar1 = 0;
    piVar1[1] = 0;
    os_free_mem(piVar1);
    piVar2 = (int *)*piVar4;
    piVar1 = piVar4;
  }
  param_1[uVar3 * 0x160d + 0xaefbe] = (int)piVar5;
  param_1[uVar3 * 0x160d + 0xaefbf] = (int)piVar5;
  _raw_spin_unlock_bh(param_1 + uVar3 * 0x160d + 0xaefbb);
  return;
}

