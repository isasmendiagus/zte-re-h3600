// module: plat-zxylzb_9128S.ko
// function: sadm_ram_set @ 0x17cb8
// size: 124 bytes
//

undefined4 sadm_ram_set(uint param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  
  iVar1 = 5;
  do {
    if ((*(uint *)(pp_base + 0x4018) & 1) != 0) {
      *(uint *)(pp_base + 0x4014) = param_1 | param_3 << 0x16;
      *(undefined4 *)(pp_base + 0x401c) = *param_2;
      return 0;
    }
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  printk("sadm ram set timeout\n");
  return 0xfffffff5;
}

