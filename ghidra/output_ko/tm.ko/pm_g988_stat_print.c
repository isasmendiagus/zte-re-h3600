// module: tm.ko
// function: pm_g988_stat_print @ 0x6ddc4
// size: 952 bytes
//

undefined4 pm_g988_stat_print(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int *piVar5;
  int *piVar6;
  undefined4 local_188;
  undefined1 auStack_184 [4];
  int local_180;
  undefined4 local_178;
  undefined4 local_174;
  undefined4 local_170;
  undefined4 local_16c;
  undefined4 local_168 [2];
  undefined4 local_160;
  undefined4 uStack_15c;
  undefined4 local_158;
  undefined4 local_154;
  undefined4 local_150;
  undefined4 local_14c;
  undefined4 local_148;
  undefined4 local_144;
  undefined4 local_140;
  undefined4 local_13c;
  undefined4 local_138;
  undefined4 local_134;
  undefined4 local_130;
  int iStack_12c;
  int local_128 [65];
  
  memset(local_128,0,0x100);
  local_188 = 0;
  __memzero(local_168,0x40);
  piVar6 = &iStack_12c;
  __memzero(auStack_184,0x1c);
  printk("|-----------------------------------------|\n");
  printk("|--------- pm g988 statistics info -------|\n");
  printk("|-----------------------------------------|\n");
  printk("| %-6s| %-6s| %-4s| %-5s| %-4s| %-5s|\n","index","valid",&_LC45,&_LC46,&_LC64,&_LC65);
  printk("|-----------------------------------------|\n");
  uVar3 = 0;
  piVar5 = piVar6;
  do {
    while( true ) {
      iVar1 = pm_get_g988_index_cfg(uVar3,auStack_184);
      if (iVar1 != 0) goto LAB_0006e040;
      piVar5 = piVar5 + 1;
      *piVar5 = local_180;
      pm_port_name_get(local_174,&local_188);
      if (7 < uVar3) break;
      printk("| %-6d| %-6d| %-4d| %-5s| %-4s| %-5d|\n",uVar3,local_180,local_178,local_188,&_LC57,
             local_16c);
LAB_0006dea0:
      uVar3 = uVar3 + 1;
      if (uVar3 == 0x40) goto LAB_0006df28;
    }
    if (0xf < uVar3) {
      printk("| %-6d| %-6d| %-4d| %-5s| %-4d| %-5d|\n",uVar3,local_180,local_178,local_188,local_170
             ,local_16c);
      goto LAB_0006dea0;
    }
    uVar4 = uVar3 + 1;
    printk("| %-6d| %-6d| %-4d| %-5s| %-4d| %-5s|\n",uVar3,local_180,local_178,local_188,local_170,
           &_LC57);
    uVar3 = uVar4;
  } while (uVar4 != 0x40);
LAB_0006df28:
  printk(
        "|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------|\n"
        );
  printk("| %-6s| %-10s| %-20s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s|\n"
         ,"index",&_LC72,"octets","packets","broadcast","multicast","undersize",&_LC78,"65to127",
         "128to255","256to511","512to1023","1024to1518","oversize");
  printk(
        "|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------|\n"
        );
  iVar1 = 0;
  do {
    piVar6 = piVar6 + 1;
    if (*piVar6 == 0) {
      printk("| %-6d| %-10s| %-20s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s|\n"
             ,iVar1,&_LC57,&_LC57,&_LC57,&_LC57,&_LC57,&_LC57,&_LC57,&_LC57,&_LC57,&_LC57,&_LC57,
             &_LC57,&_LC57);
    }
    else {
      iVar2 = pm_get_g988_statistics(iVar1,local_168);
      if (iVar2 != 0) {
LAB_0006e040:
        if (6 < g_tm_debug_level) {
          printk("pm_g988_stat_print failed!\n");
        }
        return 0xffffffff;
      }
      printk("| %-6d| %-10d| %-20lld| %-10d| %-10d| %-10d| %-10d| %-10d| %-10d| %-10d| %-10d| %-10d| %-10d| %-10d|\n"
             ,iVar1,local_168[0],local_150,local_160,uStack_15c,local_158,local_154,local_150,
             local_14c,local_148,local_144,local_140,local_13c,local_138,local_134,local_130);
    }
    iVar1 = iVar1 + 1;
    if (iVar1 == 0x40) {
      printk(
            "|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------|\n"
            );
      return 0;
    }
  } while( true );
}

