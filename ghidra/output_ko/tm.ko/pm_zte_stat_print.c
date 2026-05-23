// module: tm.ko
// function: pm_zte_stat_print @ 0x6e17c
// size: 940 bytes
//

undefined4 pm_zte_stat_print(void)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 *puVar4;
  int *piVar5;
  int *piVar6;
  undefined4 local_f8;
  undefined1 auStack_f4 [4];
  int local_f0;
  undefined4 local_ec;
  undefined4 local_e8;
  undefined4 local_e4;
  undefined4 local_e0 [2];
  undefined4 local_d8;
  undefined4 uStack_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  int iStack_ac;
  int local_a8 [33];
  
  memset(local_a8,0,0x80);
  local_f8 = 0;
  __memzero(local_e0,0x38);
  piVar6 = &iStack_ac;
  __memzero(auStack_f4,0x14);
  printk("|-----------------------------------|\n");
  printk("|------ pm zte statistics info -----|\n");
  printk("|-----------------------------------|\n");
  printk("| %-6s| %-6s| %-4s| %-5s| %-5s|\n","index","valid",&_LC45,&_LC46,&_LC65);
  printk("|-----------------------------------|\n");
  uVar2 = 0;
  piVar5 = piVar6;
  do {
    while( true ) {
      iVar1 = pm_get_zte_index_cfg(uVar2,auStack_f4);
      puVar4 = &local_f8;
      if (iVar1 != 0) goto LAB_0006e4b4;
      piVar5 = piVar5 + 1;
      *piVar5 = local_f0;
      pm_port_name_get(local_e8,puVar4);
      if (uVar2 < 0x10) break;
      uVar3 = uVar2 + 1;
      printk("| %-6d| %-6d| %-4d| %-5s| %-5s|\n",uVar2,local_f0,local_ec,local_f8,&_LC57);
      uVar2 = uVar3;
      if (uVar3 == 0x20) goto LAB_0006e2c0;
    }
    uVar3 = uVar2 + 1;
    printk("| %-6d| %-6d| %-4d| %-5s| %-5d|\n",uVar2,local_f0,local_ec,local_f8,local_e4);
    uVar2 = uVar3;
  } while (uVar3 != 0x20);
LAB_0006e2c0:
  printk(
        "|-----------------------------------------------------------------------------------------------------------------------------------------------------|\n"
        );
  printk(
        "|--------------------------------------------------- pm zte statistics info --------------------------------------------------------------------------|\n"
        );
  printk(
        "|-----------------------------------------------------------------------------------------------------------------------------------------------------|\n"
        );
  puVar4 = (undefined4 *)0x0;
  printk("| %-6s| %-10s| %-20s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s|\n",
         "index","packets","octets",&_LC72,"adm_drop","bp_drop","pppoe_drop","brg_drop","age_drop",
         "cla_drop","spa_drop","total_fwd");
  printk(
        "|-----------------------------------------------------------------------------------------------------------------------------------------------------|\n"
        );
  do {
    piVar6 = piVar6 + 1;
    if (*piVar6 == 0) {
      printk("| %-6d| %-10s| %-20s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s|\n"
             ,puVar4,&_LC57,&_LC57,&_LC57,&_LC57,&_LC57,&_LC57,&_LC57,&_LC57,&_LC57,&_LC57,&_LC57);
    }
    else {
      iVar1 = pm_get_zte_statistics(puVar4,local_e0);
      if (iVar1 != 0) {
LAB_0006e4b4:
        if (6 < g_tm_debug_level) {
          printk("pm_zte_stat_print failed!\n",puVar4);
        }
        return 0xffffffff;
      }
      if (puVar4 < (undefined4 *)0x10) {
        printk("| %-6d| %-10d| %-20lld| %-10d| %-10d| %-10d| %-10d| %-10d| %-10d| %-10d| %-10d| %-10d|\n"
               ,puVar4,local_e0[0],local_bc,local_d8,uStack_d4,local_d0,local_cc,local_c8,local_c4,
               local_c0,local_bc,local_b8,local_b4,local_b0);
      }
      else {
        printk("| %-6d| %-10d| %-20lld| %-10d| %-10d| %-10d| %-10s| %-10s| %-10d| %-10d| %-10d| %-10d|\n"
               ,puVar4,local_e0[0],local_b4,local_d8,uStack_d4,local_d0,local_cc,local_c8,&_LC57,
               &_LC57,local_bc,local_b8,local_b4,local_b0);
      }
    }
    puVar4 = (undefined4 *)((int)puVar4 + 1);
    if (puVar4 == (undefined4 *)0x20) {
      printk(
            "|-----------------------------------------------------------------------------------------------------------------------------------------------------|\n"
            );
      return 0;
    }
  } while( true );
}

