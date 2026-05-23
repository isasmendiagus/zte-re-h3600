// module: tm.ko
// function: sbrg_print_mactable @ 0x1c928
// size: 812 bytes
//

undefined4 sbrg_print_mactable(void)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  bool bVar10;
  int local_44;
  int local_3c;
  int local_38;
  uint local_34;
  uint local_30;
  uint local_2c [2];
  
  local_3c = 0;
  tmOnuRegRead(0x1d,&local_38,0,&sbragRegTable);
  if (local_38 == 0) {
    iVar7 = 0x400;
  }
  else if (local_38 == 1) {
    iVar7 = 0x100;
  }
  else if (local_38 == 2) {
    iVar7 = 0x200;
  }
  else {
    iVar7 = 0;
    if (g_tm_debug_level != 0) {
      printk("[TM][sbrg_print_mactable] this scheme not support mac and ip ram!\n");
      iVar7 = 0;
    }
  }
  printk("field instruction\n");
  uVar6 = 0;
  iVar9 = 0;
  local_44 = 1;
  printk("status note 0:invalid entry,0001-1110:valid entry,1111:static entry\n");
  printk("ctrl   note 0:whitelist ,1:blacklist\n");
  printk("%-6s%-6s%-6s%-19s%-6s%-10s%-10s%-11s%-9s%9s\n",&_LC308,"ramid",&_LC310,&_LC311,&_LC312,
         "portmask","status","smac_ctrl","dmac_ctrl",&_LC317);
  do {
    if (iVar7 != 0) {
      iVar8 = 0;
      do {
        uVar1 = tmOnuRegWrite(0x13,iVar9 * 0x400000 + 0x8000000 + iVar8,0,&sbragRegTable);
        bVar10 = uVar6 == 9;
        if (uVar6 < 10) {
          bVar10 = local_3c == 0;
        }
        if (bVar10) {
          do {
            uVar6 = uVar6 + 1;
            uVar2 = tmOnuRegRead(0x14,&local_3c,0,&sbragRegTable);
            uVar1 = uVar2 | uVar1;
            bVar10 = uVar6 == 9;
            if (uVar6 < 10) {
              bVar10 = local_3c == 0;
            }
          } while (bVar10);
        }
        if (9 < uVar6) {
          if (6 < g_tm_debug_level) {
            printk("[TM][sbrg_print_mactable]indirect access time out\n");
            return 0xffffffff;
          }
          return 0xffffffff;
        }
        iVar3 = tmOnuRegRead(0x4c,&local_34,0,&sbragRegTable);
        iVar4 = tmOnuRegRead(0x4d,&local_30,0,&sbragRegTable);
        iVar5 = tmOnuRegRead(0x4e,local_2c,0,&sbragRegTable);
        if (((iVar3 != 0 || iVar4 != 0) || uVar1 != 0) || iVar5 != 0) {
          if (g_tm_debug_level != 0) {
            printk("[TM][sbrg_print_mactable] reg read failed\n");
            return 0xffffffff;
          }
          return 0xffffffff;
        }
        uVar1 = (local_2c[0] << 0x18) >> 0x1c;
        if (uVar1 != 0) {
          printk("%-6d%-6d%-6x%-2x:%-2x:%-2x:%-2x:%-2x:%-4x%-6d0x%-8x%-10d%-11d%-9d%-9d\n",local_44,
                 iVar9,iVar8,(local_30 << 8) >> 0x18,(local_30 << 0x10) >> 0x18,local_30 & 0xff,
                 local_34 >> 0x18,(local_34 << 8) >> 0x18,(local_34 << 0x10) >> 0x18,
                 (local_2c[0] & 0xf) << 8 | local_30 >> 0x18,
                 local_34 & 0xc0 | (local_34 & 1) << 5 | (local_34 << 0x1a) >> 0x1b,uVar1,
                 (local_2c[0] << 0x17) >> 0x1f,(local_2c[0] << 0x16) >> 0x1f,0);
          local_44 = local_44 + 1;
        }
        iVar8 = iVar8 + 1;
      } while (iVar8 != iVar7);
    }
    iVar9 = iVar9 + 1;
    if (iVar9 == 4) {
      return 0;
    }
  } while( true );
}

