// module: plat-zxylzb_9128S.ko
// function: brg_ram_get @ 0x1636c
// size: 208 bytes
//

undefined4 brg_ram_get(uint param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0x32;
  do {
    if ((*(uint *)(pp_base + 0x8018) & 1) != 0) {
      *(uint *)(pp_base + 0x8014) = param_1 | 0x8000000 | param_3 << 0x16;
      iVar1 = pp_base;
      iVar3 = 0x32;
      do {
        if ((*(uint *)(pp_base + 0x8018) & 1) != 0) {
          param_2[2] = *(undefined4 *)(pp_base + 0x8024);
          iVar2 = pp_base;
          param_2[1] = *(undefined4 *)(iVar1 + 0x8020);
          *param_2 = *(undefined4 *)(iVar2 + 0x801c);
          return 0;
        }
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  printk("brg ram get timeout\n");
  return 0xfffffff5;
}

