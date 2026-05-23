// module: tm.ko
// function: pm_add_g988_rule @ 0x34730
// size: 128 bytes
//

undefined4 pm_add_g988_rule(int *param_1,undefined4 param_2)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = *param_1;
  uVar1 = param_1[1] << 0x14 | param_1[3] << 0x12 | param_1[4] << 0xf |
          (uint)*(byte *)(param_1 + 2) << 0x13;
  if (iVar2 == 1) {
    uVar1 = uVar1 | param_1[6];
  }
  else if (iVar2 == 2) {
    uVar1 = uVar1 | param_1[5] << 0xc;
  }
  else if (iVar2 == 3) {
    uVar1 = uVar1 | param_1[6] | param_1[5] << 0xc;
  }
  tmOnuRegWrite(0xd,uVar1,param_2,pmRegTable);
  return 0;
}

