// module: plat-zxylzb_9128S.ko
// function: cla_ram_set @ 0x179a0
// size: 192 bytes
//

undefined4 cla_ram_set(uint param_1,undefined4 *param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = 5;
  do {
    if ((*(uint *)(pp_base + 0xc018) & 1) != 0) {
      *(uint *)(pp_base + 0xc014) = param_1 | param_3 << 0x16;
      *(undefined4 *)(pp_base + 0xc028) = param_2[3];
      *(undefined4 *)(pp_base + 0xc024) = param_2[2];
      *(undefined4 *)(pp_base + 0xc020) = param_2[1];
      *(undefined4 *)(pp_base + 0xc01c) = *param_2;
      return 0;
    }
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  printk("set cla ram %d/%d failed\n",param_3,param_1,(uint *)(pp_base + 0xc018),param_4);
  return 0xfffffff5;
}

