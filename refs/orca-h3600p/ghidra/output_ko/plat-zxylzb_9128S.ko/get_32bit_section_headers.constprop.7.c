// module: plat-zxylzb_9128S.ko
// function: get_32bit_section_headers.constprop.7 @ 0x11c3c
// size: 292 bytes
//

undefined4 get_32bit_section_headers_constprop_7(undefined4 param_1)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  
  if (section_headers == (uint *)0x0) {
    if (Ehdr32._46_2_ != 0x28) {
      printk("Invalid size of section header %d, should be %d\n",Ehdr32._46_2_,0x34);
      return 0xffffffff;
    }
    section_headers =
         (uint *)get_data(param_1,Ehdr32._32_4_,(uint)(ushort)Ehdr32._48_2_ * 0x28,"section headers"
                         );
    if (section_headers == (uint *)0x0) {
      return 0xffffffff;
    }
    if ((is_big_endian != 0) && (Ehdr32._48_2_ != 0)) {
      iVar4 = 0;
      puVar1 = section_headers;
      do {
        uVar10 = *puVar1;
        iVar4 = iVar4 + 1;
        uVar9 = puVar1[1];
        uVar8 = puVar1[2];
        uVar7 = puVar1[3];
        uVar6 = puVar1[4];
        uVar5 = puVar1[5];
        uVar12 = puVar1[6];
        uVar11 = puVar1[7];
        uVar2 = puVar1[8];
        uVar3 = puVar1[9];
        *puVar1 = uVar10 << 0x18 | (uVar10 >> 8 & 0xff) << 0x10 | (uVar10 >> 0x10 & 0xff) << 8 |
                  uVar10 >> 0x18;
        puVar1[1] = uVar9 << 0x18 | (uVar9 >> 8 & 0xff) << 0x10 | (uVar9 >> 0x10 & 0xff) << 8 |
                    uVar9 >> 0x18;
        puVar1[2] = uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 |
                    uVar8 >> 0x18;
        puVar1[3] = uVar7 << 0x18 | (uVar7 >> 8 & 0xff) << 0x10 | (uVar7 >> 0x10 & 0xff) << 8 |
                    uVar7 >> 0x18;
        puVar1[4] = uVar6 << 0x18 | (uVar6 >> 8 & 0xff) << 0x10 | (uVar6 >> 0x10 & 0xff) << 8 |
                    uVar6 >> 0x18;
        puVar1[5] = uVar5 << 0x18 | (uVar5 >> 8 & 0xff) << 0x10 | (uVar5 >> 0x10 & 0xff) << 8 |
                    uVar5 >> 0x18;
        puVar1[6] = uVar12 << 0x18 | (uVar12 >> 8 & 0xff) << 0x10 | (uVar12 >> 0x10 & 0xff) << 8 |
                    uVar12 >> 0x18;
        puVar1[7] = uVar11 << 0x18 | (uVar11 >> 8 & 0xff) << 0x10 | (uVar11 >> 0x10 & 0xff) << 8 |
                    uVar11 >> 0x18;
        puVar1[9] = uVar3 << 0x18 | (uVar3 >> 8 & 0xff) << 0x10 | (uVar3 >> 0x10 & 0xff) << 8 |
                    uVar3 >> 0x18;
        puVar1[8] = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
                    uVar2 >> 0x18;
        puVar1 = puVar1 + 10;
      } while (iVar4 < (int)(uint)(ushort)Ehdr32._48_2_);
      return 0;
    }
  }
  return 0;
}

