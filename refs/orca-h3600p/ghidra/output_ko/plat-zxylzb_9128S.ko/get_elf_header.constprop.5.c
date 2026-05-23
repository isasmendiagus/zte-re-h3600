// module: plat-zxylzb_9128S.ko
// function: get_elf_header.constprop.5 @ 0x119a0
// size: 264 bytes
//

undefined4
get_elf_header_constprop_5
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  myfile_lseek_constprop_14(param_1,0,param_3,param_4,param_4);
  iVar1 = myfile_read(param_1,Ehdr32,0x34);
  if (iVar1 != 0x34) {
    return 0xffffffff;
  }
  is_big_endian = (uint)(Ehdr32[5] == '\x02');
  is_32bit_elf = (uint)(Ehdr32[4] != '\x02');
  if ((Ehdr32[5] == '\x02') == 0) {
    return 0;
  }
  Ehdr32._16_2_ = Ehdr32._16_2_ << 8 | (ushort)Ehdr32._16_2_ >> 8;
  Ehdr32._18_2_ = Ehdr32._18_2_ << 8 | (ushort)Ehdr32._18_2_ >> 8;
  Ehdr32._20_4_ =
       Ehdr32._20_4_ << 0x18 | ((uint)Ehdr32._20_4_ >> 8 & 0xff) << 0x10 |
       ((uint)Ehdr32._20_4_ >> 0x10 & 0xff) << 8 | (uint)Ehdr32._20_4_ >> 0x18;
  Ehdr32._24_4_ =
       Ehdr32._24_4_ << 0x18 | ((uint)Ehdr32._24_4_ >> 8 & 0xff) << 0x10 |
       ((uint)Ehdr32._24_4_ >> 0x10 & 0xff) << 8 | (uint)Ehdr32._24_4_ >> 0x18;
  Ehdr32._28_4_ =
       Ehdr32._28_4_ << 0x18 | ((uint)Ehdr32._28_4_ >> 8 & 0xff) << 0x10 |
       ((uint)Ehdr32._28_4_ >> 0x10 & 0xff) << 8 | (uint)Ehdr32._28_4_ >> 0x18;
  Ehdr32._32_4_ =
       Ehdr32._32_4_ << 0x18 | ((uint)Ehdr32._32_4_ >> 8 & 0xff) << 0x10 |
       ((uint)Ehdr32._32_4_ >> 0x10 & 0xff) << 8 | (uint)Ehdr32._32_4_ >> 0x18;
  Ehdr32._36_4_ =
       Ehdr32._36_4_ << 0x18 | ((uint)Ehdr32._36_4_ >> 8 & 0xff) << 0x10 |
       ((uint)Ehdr32._36_4_ >> 0x10 & 0xff) << 8 | (uint)Ehdr32._36_4_ >> 0x18;
  Ehdr32._40_2_ = Ehdr32._40_2_ << 8 | (ushort)Ehdr32._40_2_ >> 8;
  Ehdr32._42_2_ = Ehdr32._42_2_ << 8 | (ushort)Ehdr32._42_2_ >> 8;
  Ehdr32._44_2_ = Ehdr32._44_2_ << 8 | (ushort)Ehdr32._44_2_ >> 8;
  Ehdr32._46_2_ = Ehdr32._46_2_ << 8 | (ushort)Ehdr32._46_2_ >> 8;
  Ehdr32._48_2_ = Ehdr32._48_2_ << 8 | (ushort)Ehdr32._48_2_ >> 8;
  Ehdr32._50_2_ = Ehdr32._50_2_ << 8 | (ushort)Ehdr32._50_2_ >> 8;
  return 0;
}

