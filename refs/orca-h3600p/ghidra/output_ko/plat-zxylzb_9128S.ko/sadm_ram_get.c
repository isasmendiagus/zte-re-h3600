// module: plat-zxylzb_9128S.ko
// function: sadm_ram_get @ 0x17d34
// size: 168 bytes
//

undefined4 sadm_ram_get(uint param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 5;
  do {
    if ((*(uint *)(pp_base + 0x4018) & 1) != 0) {
      *(uint *)(pp_base + 0x4014) = param_1 | 0x8000000 | param_3 << 0x16;
      iVar2 = 5;
      do {
        if ((*(uint *)(pp_base + 0x4018) & 1) != 0) {
          *param_2 = *(undefined4 *)(pp_base + 0x401c);
          return 0;
        }
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  printk("sadm ram get timeout\n");
  return 0xfffffff5;
}

