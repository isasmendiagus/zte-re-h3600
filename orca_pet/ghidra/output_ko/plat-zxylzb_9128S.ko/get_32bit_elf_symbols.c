// module: plat-zxylzb_9128S.ko
// function: get_32bit_elf_symbols @ 0x11b7c
// size: 192 bytes
//

uint * get_32bit_elf_symbols(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  uint *puVar1;
  uint *puVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  
  if (*(int *)(param_2 + 0x24) == 0x10) {
    puVar2 = (uint *)get_data(param_1,*(undefined4 *)(param_2 + 0x10),
                              *(undefined4 *)(param_2 + 0x14),"symtab shndx");
    if (puVar2 != (uint *)0x0) {
      if ((is_big_endian != 0) &&
         (iVar3 = __aeabi_uidiv(*(undefined4 *)(param_2 + 0x14),*(undefined4 *)(param_2 + 0x24)),
         0 < iVar3)) {
        iVar5 = 0;
        puVar1 = puVar2;
        do {
          iVar5 = iVar5 + 1;
          uVar7 = *puVar1;
          uVar6 = puVar1[1];
          uVar4 = puVar1[2];
          *puVar1 = uVar7 << 0x18 | (uVar7 >> 8 & 0xff) << 0x10 | (uVar7 >> 0x10 & 0xff) << 8 |
                    uVar7 >> 0x18;
          puVar1[1] = uVar6 << 0x18 | (uVar6 >> 8 & 0xff) << 0x10 | (uVar6 >> 0x10 & 0xff) << 8 |
                      uVar6 >> 0x18;
          puVar1[2] = uVar4 << 0x18 | (uVar4 >> 8 & 0xff) << 0x10 | (uVar4 >> 0x10 & 0xff) << 8 |
                      uVar4 >> 0x18;
          *(ushort *)((int)puVar1 + 0xe) =
               *(ushort *)((int)puVar1 + 0xe) << 8 | *(ushort *)((int)puVar1 + 0xe) >> 8;
          puVar1 = puVar1 + 4;
        } while (iVar3 != iVar5);
      }
    }
    return puVar2;
  }
  printk("Invalid entsize of section, %d, should be %d\n",*(int *)(param_2 + 0x24),0x10,param_4,
         param_4);
  return (uint *)0x0;
}

