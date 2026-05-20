// module: plat-zxylzb_9128S.ko
// function: func_insert @ 0x11dcc
// size: 120 bytes
//

undefined4 func_insert(int *param_1,int *param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  piVar1 = param_1;
  iVar3 = 0;
  do {
    while( true ) {
      iVar2 = *piVar1;
      if (iVar2 == 0) {
        *param_2 = iVar3;
        param_2[1] = 0;
        param_2[2] = 0;
        *piVar1 = (int)param_2;
        rb_insert_color(param_2,param_1);
        return 0;
      }
      piVar1 = (int *)(iVar2 + 4);
      iVar3 = iVar2;
      if (*(uint *)(iVar2 + 0xc) < (uint)param_2[4]) break;
      piVar1 = (int *)(iVar2 + 8);
    }
  } while (*(uint *)(iVar2 + 0x10) <= (uint)param_2[3]);
  return 0xffffffff;
}

