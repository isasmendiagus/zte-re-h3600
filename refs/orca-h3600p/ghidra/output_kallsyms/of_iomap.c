// kallsyms symbol: of_iomap
// string @ 0xc06038c6, .value @ 0xc05e98c0 = 0xc02c04a4
// Function: FUN_c02c04a4 @ 0xc02c04a4
//

undefined4 FUN_c02c04a4(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iStack_24;
  int iStack_20;
  
  iVar1 = FUN_c02c0424(param_1,param_2,&iStack_24);
  if (iVar1 == 0) {
    uVar2 = FUN_c00126c4(iStack_24,(iStack_20 + 1) - iStack_24);
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

