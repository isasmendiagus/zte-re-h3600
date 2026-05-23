// module: mt7915.ko
// function: AsicRcpiReset @ 0x1331c4
// size: 68 bytes
//

void AsicRcpiReset(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 extraout_r2;
  undefined4 extraout_r2_00;
  undefined4 uVar2;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  uVar2 = extraout_r2;
  if (*(code **)(iVar1 + 0x98) != (code *)0x0) {
    (**(code **)(iVar1 + 0x98))(param_1,param_2);
    uVar2 = extraout_r2_00;
  }
  AsicNotSupportFunc(param_1,"AsicRcpiReset",uVar2,param_4);
  return;
}

