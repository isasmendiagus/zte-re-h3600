// module: plat-zxylzb_9128S.ko
// function: func_search @ 0x11e44
// size: 68 bytes
//

void func_search(int *param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = *param_1;
  if (iVar1 == 0) {
    return;
  }
  do {
    while (param_2 < *(uint *)(iVar1 + 0xc)) {
      iVar1 = *(int *)(iVar1 + 8);
      if (iVar1 == 0) {
        return;
      }
    }
    if (param_2 < *(uint *)(iVar1 + 0x10)) {
      return;
    }
    iVar1 = *(int *)(iVar1 + 4);
  } while (iVar1 != 0);
  return;
}

