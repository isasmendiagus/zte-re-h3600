// module: plat-zxylzb_9128S.ko
// function: brg_ram_set @ 0x1643c
// size: 164 bytes
//

undefined4 brg_ram_set(uint param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  
  iVar1 = 0x32;
  do {
    if ((*(uint *)(pp_base + 0x8018) & 1) != 0) {
      *(uint *)(pp_base + 0x8014) = param_1 | param_3 << 0x16;
      *(undefined4 *)(pp_base + 0x8024) = param_2[2];
      *(undefined4 *)(pp_base + 0x8020) = param_2[1];
      *(undefined4 *)(pp_base + 0x801c) = *param_2;
      return 0;
    }
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  printk("brg ram set timeout\n");
  return 0xfffffff5;
}

