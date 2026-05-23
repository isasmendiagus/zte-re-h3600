// module: plat-zxylzb_9128S.ko
// function: get_usyms_lib @ 0x1cf54
// size: 196 bytes
//

int get_usyms_lib(int param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined1 auStack_110 [260];
  
  iVar1 = rb_first(*(int *)(param_1 + 0x18c) + 4);
  while( true ) {
    if (iVar1 == 0) {
      return 0;
    }
    if ((*(uint *)(iVar1 + -0x10) <= param_2) && (param_2 < *(uint *)(iVar1 + -0xc))) break;
    iVar1 = rb_next(iVar1);
  }
  uVar3 = ((*(uint *)(iVar1 + 0x18) ^ 4) << 0x1d) >> 0x1f;
  if (*(int *)(iVar1 + 0x40) == 0) {
    uVar3 = 1;
  }
  if (uVar3 != 0) {
    return 0;
  }
  iVar2 = d_path(*(int *)(iVar1 + 0x40) + 8,auStack_110,0x100);
  if (iVar2 == 0) {
    return 0;
  }
  iVar2 = usyms_lookup_addr(iVar2,param_2 - *(int *)(iVar1 + -0x10));
  if (iVar2 != 0) {
    *(int *)(iVar2 + 0xc) = *(int *)(iVar2 + 0xc) + *(int *)(iVar1 + -0x10);
    return iVar2;
  }
  return 0;
}

