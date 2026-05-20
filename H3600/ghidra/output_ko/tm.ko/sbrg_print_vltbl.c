// module: tm.ko
// function: sbrg_print_vltbl @ 0x1d2dc
// size: 608 bytes
//

undefined4 sbrg_print_vltbl(void)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  bool bVar8;
  int local_3c;
  int local_38;
  uint local_34;
  undefined1 auStack_30 [4];
  undefined1 auStack_2c [8];
  
  uVar6 = 0;
  local_38 = 0;
  printk("field instruction\n");
  printk("valid note 0:invalid,1:valid\n");
  printk("value note 0:not member,1:untag,2:tag,3:unmodify\n");
  local_3c = 1;
  printk("%-6s%-7s%-7s%-7s%-5s%-6s%-6s%-6s%-6s%-6s%-6s\n",&_LC308,"valid","wifi2","wifi1",&_LC0,
         &_LC349,&_LC350,&_LC351,&_LC352,&_LC1,&_LC312);
  iVar7 = 0;
  do {
    uVar1 = tmOnuRegWrite(0x13,iVar7 + 0x9000000,0,&sbragRegTable);
    if (local_38 == 0) {
      do {
        uVar6 = uVar6 + 1;
        uVar2 = tmOnuRegRead(0x14,&local_38,0,&sbragRegTable);
        uVar1 = uVar2 | uVar1;
        bVar8 = uVar6 == 9;
        if (uVar6 < 10) {
          bVar8 = local_38 == 0;
        }
      } while (bVar8);
      if (9 < uVar6) {
        if (g_tm_debug_level < 7) {
          return 0xffffffff;
        }
        printk("[TM][sbrg_print_mactable]indirect access time out\n");
        return 0xffffffff;
      }
    }
    iVar3 = tmOnuRegRead(0x4c,&local_34,0,&sbragRegTable);
    iVar4 = tmOnuRegRead(0x4d,auStack_30,0,&sbragRegTable);
    iVar5 = tmOnuRegRead(0x4e,auStack_2c,0,&sbragRegTable);
    if (((iVar3 != 0 || iVar4 != 0) || uVar1 != 0) || iVar5 != 0) {
      if (g_tm_debug_level != 0) {
        printk("[TM][sbrg_print_mactable] reg read failed\n");
      }
      return 0xffffffff;
    }
    if ((local_34 & 1) != 0) {
      printk("%-6d%-7d%-7d%-7d%-5d%-6d%-6d%-6d%-6d%-6d%-6d\n",local_3c,local_34 & 1,
             (local_34 << 0xf) >> 0x1e,(local_34 << 0x11) >> 0x1e,(local_34 << 0x1d) >> 0x1e,
             (local_34 << 0x13) >> 0x1e,(local_34 << 0x15) >> 0x1e,(local_34 << 0x17) >> 0x1e,
             (local_34 << 0x19) >> 0x1e,(local_34 << 0x1b) >> 0x1e,iVar7);
      local_3c = local_3c + 1;
    }
    iVar7 = iVar7 + 1;
  } while (iVar7 != 0x1000);
  return 0;
}

