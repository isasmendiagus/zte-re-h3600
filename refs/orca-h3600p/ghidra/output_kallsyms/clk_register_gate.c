// kallsyms symbol: clk_register_gate
// string @ 0xc04ce498, .value @ 0xc04f15d4 = 0xc04ce448
// Function: FUN_c04738ac @ 0xc04738ac
//

undefined4 FUN_c04738ac(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = (**(code **)(param_1 + 0x24))();
  if (iVar1 == 0) {
    uVar2 = 2;
  }
  else {
    uVar2 = FUN_c04708bc(param_2,iVar1,param_3);
  }
  return uVar2;
}

