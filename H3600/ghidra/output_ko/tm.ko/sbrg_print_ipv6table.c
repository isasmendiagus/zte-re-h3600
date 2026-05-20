// module: tm.ko
// function: sbrg_print_ipv6table @ 0x1cf54
// size: 904 bytes
//

undefined4 sbrg_print_ipv6table(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint *puVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  bool bVar12;
  int local_60;
  int local_5c;
  uint local_58;
  uint local_54;
  int local_50;
  uint local_4c;
  uint local_48;
  int local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_34;
  undefined4 local_30;
  uint uStack_28;
  
  local_5c = 0;
  iVar1 = sbrg_get_table_sel(&local_60);
  if (iVar1 == 0) {
    if (local_60 != 0 && local_60 != 3) {
      uVar5 = 0;
      if (local_60 == 1) {
        iVar1 = 0x80;
      }
      else {
        iVar1 = 0x40;
      }
      printk("field instruction\n");
      printk("valid note 0:invalid,1:valid\n");
      printk("age   note 0:not age,1:halfage\n");
      printk("mode  note 0:include,1:exclude\n");
      printk("action note 0:unchange,1:remove a tag,2:replace,3:add a tag\n");
      iVar10 = 1;
      printk("%-5s%-5s%-36s%-36s%-9s%-5s%-4s%-7s\n",&_LC308,&_LC312,&_LC329,&_LC330,"portmask",
             &_LC331,&_LC332,"valid");
      uVar9 = uVar5;
      do {
        iVar8 = 0;
        iVar11 = iVar10;
        do {
          puVar7 = &local_58;
          iVar6 = iVar8 * 4 + uVar9 * 0x400000 + 0x8000300;
          iVar10 = ((iVar8 * 4 & 0x1fcU) + uVar9 * 0x400000 + 0x8000200) - iVar6;
          do {
            iVar2 = iVar6;
            if (iVar1 == 0x80) {
              iVar2 = iVar10 + iVar6;
            }
            tmOnuRegWrite(0x13,iVar2,0,&sbragRegTable);
            if (local_5c == 0) {
              do {
                uVar5 = uVar5 + 1;
                tmOnuRegRead(0x14,&local_5c,0,&sbragRegTable);
                bVar12 = uVar5 == 9;
                if (uVar5 < 10) {
                  bVar12 = local_5c == 0;
                }
              } while (bVar12);
              if (9 < uVar5) {
                if (g_tm_debug_level < 7) {
                  return 0xffffffff;
                }
                printk("[TM][sbrg_print_ipv6table]indirect access time out\n");
                return 0xffffffff;
              }
            }
            iVar2 = tmOnuRegRead(0x4c,puVar7,0,&sbragRegTable);
            iVar3 = tmOnuRegRead(0x4d,puVar7 + 1,0,&sbragRegTable);
            iVar4 = tmOnuRegRead(0x4e,puVar7 + 2,0,&sbragRegTable);
            if ((iVar3 != 0 || iVar2 != 0) || iVar4 != 0) {
              if (g_tm_debug_level == 0) {
                return 0xffffffff;
              }
              printk("[TM][sbrg_lookup_ipv6table] reg read failed\n");
              return 0xffffffff;
            }
            puVar7 = puVar7 + 3;
            iVar6 = iVar6 + 1;
          } while (puVar7 != &uStack_28);
          iVar10 = iVar11;
          if ((local_58 & 1) != 0) {
            iVar10 = iVar11 + 1;
            printk("%-5d%-5d%-8x:%-8x:%-8x:%-9x%-8x:%-8x:%-8x:%-9x0x%-7x%-5d%-4d%-7d\n",iVar11,
                   (local_58 << 0x11) >> 0x14,local_54 >> 0xf | local_50 << 0x11,
                   local_58 >> 0xf | local_54 << 0x11,local_48 >> 8 | local_44 << 0x18,
                   local_4c >> 8 | local_48 << 0x18,local_3c,local_40,local_30,local_34,
                   local_4c & 0xc0 | (local_4c & 1) << 5 | (local_4c << 0x1a) >> 0x1b,
                   (local_58 << 0x1d) >> 0x1f,(local_58 << 0x1e) >> 0x1f,1);
          }
          iVar8 = iVar8 + 1;
          iVar11 = iVar10;
        } while (iVar8 != iVar1);
        uVar9 = uVar9 + 1;
        if (uVar9 == 4) {
          return 0;
        }
      } while( true );
    }
    if (g_tm_debug_level != 0) {
      printk("[TM][sbrg_print_ipv6table] ipv6 multicast address table is zero\n");
      return 0xffffffff;
    }
  }
  else if (g_tm_debug_level != 0) {
    printk("[TM][sbrg_print_ipv6table] reg read failed\n");
    return 0xffffffff;
  }
  return 0xffffffff;
}

