// module: plat-zxylzb_9128S.ko
// function: cla_ram_get @ 0x17a60
// size: 236 bytes
//

undefined4 cla_ram_get(uint param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 5;
  do {
    if ((*(uint *)(pp_base + 0xc018) & 1) != 0) {
      *(uint *)(pp_base + 0xc014) = param_1 | 0x8000000 | param_3 << 0x16;
      iVar1 = pp_base;
      iVar3 = 5;
      do {
        if ((*(uint *)(pp_base + 0xc018) & 1) != 0) {
          param_2[3] = *(undefined4 *)(pp_base + 0xc028);
          iVar2 = pp_base;
          param_2[2] = *(undefined4 *)(iVar1 + 0xc024);
          iVar1 = pp_base;
          param_2[1] = *(undefined4 *)(iVar2 + 0xc020);
          *param_2 = *(undefined4 *)(iVar1 + 0xc01c);
          return 0;
        }
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  printk("get cla ram %d/%d failed\n",param_3,param_1);
  return 0xfffffff5;
}

