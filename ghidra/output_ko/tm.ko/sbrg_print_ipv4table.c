// module: tm.ko
// function: sbrg_print_ipv4table @ 0x1cc54
// size: 768 bytes
//

undefined4 sbrg_print_ipv4table(void)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  bool bVar10;
  int local_3c;
  int local_38;
  uint local_34;
  uint local_30;
  uint local_2c [2];
  
  local_38 = 0;
  iVar1 = sbrg_get_table_sel(&local_3c);
  if (iVar1 == 0) {
    if (local_3c != 0 && local_3c != 3) {
      uVar6 = 0;
      printk("field  instruction\n");
      printk("valid  note 0:invalid, 1:valid\n");
      printk("age    note 0:not age, 1:halfage\n");
      printk("mode   note 0:include, 1:exclude\n");
      printk("action note 0:unchange,1:remove a tag,2:replace,3:add a tag\n");
      iVar1 = 1;
      printk("%-6s%-6s%-17s%-17s%-10s%-6s%-5s%-7s\n",&_LC308,&_LC312,&_LC329,&_LC330,"portmask",
             &_LC331,&_LC332,"valid");
      uVar8 = uVar6;
      do {
        iVar7 = uVar8 * 0x400000 + 0x8000100;
        iVar9 = iVar1;
        do {
          uVar2 = tmOnuRegWrite(0x13,iVar7,0,&sbragRegTable);
          if (local_38 == 0) {
            do {
              uVar6 = uVar6 + 1;
              uVar3 = tmOnuRegRead(0x14,&local_38,0,&sbragRegTable);
              uVar2 = uVar3 | uVar2;
              bVar10 = uVar6 == 9;
              if (uVar6 < 10) {
                bVar10 = local_38 == 0;
              }
            } while (bVar10);
            if (9 < uVar6) {
              if (g_tm_debug_level < 7) {
                return 0xffffffff;
              }
              printk("[TM][sbrg_print_ipv4table]indirect access time out\n");
              return 0xffffffff;
            }
          }
          iVar1 = tmOnuRegRead(0x4c,&local_34,0,&sbragRegTable);
          iVar4 = tmOnuRegRead(0x4d,&local_30,0,&sbragRegTable);
          iVar5 = tmOnuRegRead(0x4e,local_2c,0,&sbragRegTable);
          if (((iVar1 != 0 || iVar4 != 0) || uVar2 != 0) || iVar5 != 0) goto LAB_0001cc74;
          iVar1 = iVar9;
          if ((local_34 & 1) != 0) {
            uVar2 = local_2c[0] >> 0xf;
            iVar1 = iVar9 + 1;
            printk("%-6d%-6d%-3d.%-3d.%-3d.%-5d%-3d.%-3d.%-3d.%-5d0x%-8x%-6d%-5d%-7d\n",iVar9,
                   (local_2c[0] << 0x11) >> 0x14,local_30 >> 0x1b | (local_2c[0] & 7) << 5,
                   (local_30 << 5) >> 0x18,(local_30 << 0xd) >> 0x18,(local_30 << 0x15) >> 0x18,
                   local_34 >> 0x1b | (local_30 & 7) << 5,(local_34 << 5) >> 0x18,
                   (local_34 << 0xd) >> 0x18,(local_34 << 0x15) >> 0x18,
                   uVar2 & 0xc0 | (uVar2 & 1) << 5 | (uVar2 << 0x1a) >> 0x1b,
                   (local_34 << 0x1d) >> 0x1f,(local_34 << 0x1e) >> 0x1f,1);
          }
          iVar7 = iVar7 + 1;
          iVar9 = iVar1;
        } while (iVar7 != uVar8 * 0x400000 + 0x8000200);
        uVar8 = uVar8 + 1;
        if (uVar8 == 4) {
          return 0;
        }
      } while( true );
    }
    if (g_tm_debug_level != 0) {
      printk("[TM][sbrg_print_ipv4table] ipv4 multicast address table is zero\n");
      return 0xffffffff;
    }
  }
  else {
LAB_0001cc74:
    if (g_tm_debug_level != 0) {
      printk("[TM][sbrg_print_ipv4table] reg read failed\n");
      return 0xffffffff;
    }
  }
  return 0xffffffff;
}

