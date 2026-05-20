// module: tm.ko
// function: red_info_store @ 0x75e94
// size: 3928 bytes
//

undefined4 red_info_store(undefined4 param_1,undefined4 *param_2,char *param_3,undefined4 param_4)

{
  int iVar1;
  char *pcVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int local_60;
  uint local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c [10];
  
  pcVar2 = (char *)*param_2;
  iVar1 = capable(0xc);
  if (iVar1 == 0) {
    return 0xffffffff;
  }
  sscanf(param_3,"%d %d %d",&local_60,&local_5c,&local_58);
  disableIRQinterrupts();
  iVar1 = strcmp(pcVar2,"bufUsed");
  if (iVar1 == 0) {
    if (local_60 == 0) {
      if (0x27 < local_5c) goto LAB_00075f9c;
      uVar4 = local_5c * 8;
      printk("\n|---red up inside queue used space info----|\n");
      uVar8 = uVar4 + 8;
      printk("| %-7s| %-6s| %-11s| %-11s|\n","Tcont","queId","guartSpace","shareSize");
      for (uVar5 = uVar4; uVar5 < uVar8; uVar5 = uVar5 + 1) {
        red_get_in_que_ram_used_space(uVar5,&local_50,local_4c);
        printk("| %-7d| %-6d| %-11d| %-11d|\n",local_5c,uVar5 & 7,local_50,local_4c[0]);
      }
      printk("|------------------------------------------|\n");
      printk("|---red up outside queue used space info---|\n");
      printk("|------------------------------------------|\n");
      printk("| %-7s| %-6s| %-11s| %-11s|\n","Tcont","queId","selfSize","shareSize");
      printk("|------------------------------------------|\n");
      for (uVar5 = uVar4 + 0x10; uVar5 < uVar4 + 0x18; uVar5 = uVar5 + 1) {
        red_get_out_que_ram_used_space(uVar5,&local_50,local_4c);
        printk("| %-7d| %-6d| %-11d| %-11d|\n",local_5c,uVar5 & 7,local_50,local_4c[0]);
      }
      printk("|------------------------------------------|\n");
      pcVar2 = "shareSize";
      printk("| %-7s  %-6s| %-11s| %-11s|\n","cpuUp",&_LC14,"selfSize","shareSize");
      printk("|------------------------------------------|\n");
      iVar1 = 0;
      do {
        red_get_out_que_ram_used_space(iVar1,&local_50,local_4c);
        iVar6 = iVar1 + 1;
        printk("| %-15d| %-11d| %-11d|\n",iVar1,local_50,local_4c[0],pcVar2);
        iVar1 = iVar6;
      } while (iVar6 != 8);
      printk("|------------------------------------------|\n");
      printk("|---- red up all queue used space info ----|\n");
      printk("|------------------------------------------|\n");
      printk("| %-7s| %-6s| %-24s|\n","Tcont","queId","allSize");
      printk("|------------------------------------------|\n");
      for (; uVar4 < uVar8; uVar4 = uVar4 + 1) {
        red_get_buffer_queue_used_space(uVar4,local_4c);
        printk("| %-7d| %-6d| %-24d|\n",local_5c,uVar4 & 7,local_4c[0]);
      }
    }
    else {
      printk("\n|---red dn inside queue used space info ---|\n");
      if (local_5c < 5) {
        printk("| %-7s| %-6s| %-11s| %-11s|\n",&_LC4,"queId","guartSpace","shareSize");
        uVar4 = (local_5c + 0x28) * 8;
        uVar8 = uVar4 + 8;
        for (uVar5 = uVar4; uVar5 < uVar8; uVar5 = uVar5 + 1) {
          red_get_in_que_ram_used_space(uVar5,&local_50,local_4c);
          printk("| %-7d| %-6d| %-11d| %-11d|\n",local_5c,uVar5 & 7,local_50,local_4c[0]);
        }
        printk("|------------------------------------------|\n");
        printk("|---red dn outside queue used space info---|\n");
        printk("|------------------------------------------|\n");
        printk("| %-7s| %-6s| %-11s| %-11s|\n",&_LC4,"queId","selfSize","shareSize");
        printk("|------------------------------------------|\n");
        for (uVar5 = uVar4 + 0x10; uVar5 < uVar4 + 0x18; uVar5 = uVar5 + 1) {
          red_get_out_que_ram_used_space(uVar5,&local_50,local_4c);
          printk("| %-7d| %-6d| %-11d| %-11d|\n",local_5c,uVar5 & 7,local_50,local_4c[0]);
        }
        printk("|------------------------------------------|\n");
        pcVar2 = "shareSize";
        printk("| %-7s  %-6s| %-11s| %-11s|\n","cpuDn",&_LC14,"selfSize","shareSize");
        printk("|------------------------------------------|\n");
        iVar1 = 8;
        do {
          red_get_out_que_ram_used_space(iVar1,&local_50,local_4c);
          iVar6 = iVar1 + 1;
          printk("| %-15d| %-11d| %-11d|\n",iVar1,local_50,local_4c[0],pcVar2);
          iVar1 = iVar6;
        } while (iVar6 != 0x10);
        printk("|---- red dn all queue used space info ----|\n");
        printk("|------------------------------------------|\n");
        printk("| %-7s| %-6s| %-24s|\n",&_LC4,"queId","allSize");
        printk("|------------------------------------------|\n");
        for (; uVar4 < uVar8; uVar4 = uVar4 + 1) {
          red_get_buffer_queue_used_space(uVar4,local_4c);
          printk("| %-7d| %-6d| %-24d|\n",local_5c,uVar4 & 7,local_4c[0]);
        }
      }
      else {
        if (6 < local_5c) goto LAB_00075f9c;
        iVar1 = local_5c - 5;
        printk("| %-7s| %-6s| %-11s| %-11s|\n",&_LC20,"queId","guartSpace","shareSize");
        uVar4 = (local_5c + 0x28) * 8;
        uVar8 = uVar4 + 8;
        for (uVar5 = uVar4; uVar5 != uVar8; uVar5 = uVar5 + 1) {
          red_get_in_que_ram_used_space(uVar5,&local_50,local_4c);
          printk("| %-7d| %-6d| %-11d| %-11d|\n",iVar1,uVar5 & 7,local_50,local_4c[0]);
        }
        printk("|------------------------------------------|\n");
        printk("|---red dn outside queue used space info---|\n");
        printk("|------------------------------------------|\n");
        printk("| %-7s| %-6s| %-11s| %-11s|\n",&_LC20,"queId","selfSize","shareSize");
        printk("|------------------------------------------|\n");
        for (uVar5 = uVar4 + 0x10; uVar5 != uVar4 + 0x18; uVar5 = uVar5 + 1) {
          red_get_out_que_ram_used_space(uVar5,&local_50,local_4c);
          printk("| %-7d| %-6d| %-11d| %-11d|\n",iVar1,uVar5 & 7,local_50,local_4c[0]);
        }
        printk("|------------------------------------------|\n");
        pcVar2 = "shareSize";
        printk("| %-7s  %-6s| %-11s| %-11s|\n","cpuDn",&_LC14,"selfSize","shareSize");
        printk("|------------------------------------------|\n");
        iVar6 = 8;
        do {
          red_get_out_que_ram_used_space(iVar6,&local_50,local_4c);
          iVar7 = iVar6 + 1;
          printk("| %-15d| %-11d| %-11d|\n",iVar6,local_50,local_4c[0],pcVar2);
          iVar6 = iVar7;
        } while (iVar7 != 0x10);
        printk("|---- red dn all queue used space info ----|\n");
        printk("|------------------------------------------|\n");
        printk("| %-7s| %-6s| %-24s|\n",&_LC4,"queId","allSize");
        printk("|------------------------------------------|\n");
        for (; uVar4 != uVar8; uVar4 = uVar4 + 1) {
          red_get_buffer_queue_used_space(uVar4,local_4c);
          printk("| %-7d| %-6d| %-24d|\n",iVar1,uVar4 & 7,local_4c[0]);
        }
      }
    }
  }
  else {
    iVar1 = strcmp(pcVar2,"bufCfg");
    if (iVar1 != 0) {
      iVar1 = strcmp(pcVar2,"sredoutquecfg");
      if (iVar1 == 0) {
        iVar1 = red_set_out_buffer_queue_cfg(local_60,local_5c,local_58);
        if (iVar1 != 0) {
          printk("red_set_out_buffer_queue_cfg fail, error code %d!\n");
          return param_4;
        }
        pcVar2 = "red_set_out_buffer_queue_cfg input:\n que_index = %d\n";
        uVar3 = local_58;
        uVar4 = local_5c;
      }
      else {
        iVar1 = strcmp(pcVar2,"sredinquecfg");
        if (iVar1 != 0) {
          printk("%s: illegal operation <%s>\n","red_info_store",*param_2);
          return param_4;
        }
        iVar1 = red_set_in_buffer_queue_cfg(local_60,local_5c,local_58);
        if (iVar1 != 0) {
          printk("red_set_in_buffer_queue_cfg fail, error code %d!\n");
          return param_4;
        }
        pcVar2 = "red_set_in_buffer_queue_cfg input:\n que_index = %d\n";
        uVar3 = local_58;
        uVar4 = local_5c;
      }
      printk(pcVar2,local_60);
      printk("guart_space = 0x%x max_space = 0x%x\n",uVar4,uVar3);
      return param_4;
    }
    if (local_60 == 0) {
      if (0x27 < local_5c) {
LAB_00075f9c:
        printk("\n|---- input invalid parameter ----|\n");
        return param_4;
      }
      uVar4 = local_5c * 8;
      printk("\n|---- red up inside queue buffer cfg ----|\n");
      uVar8 = uVar4 + 8;
      printk("| %-7s| %-6s| %-11s| %-11s|\n","Tcont","queId","guartSpace","shareSize");
      for (uVar5 = uVar4; uVar5 < uVar8; uVar5 = uVar5 + 1) {
        red_get_in_buffer_queue_cfg(uVar5,&local_54,&local_50);
        printk("| %-7d| %-6d| %-11d| %-11d|\n",local_5c,uVar5 & 7,local_54,local_50);
      }
      printk("|------------------------------------------|\n");
      printk("|---- red up outside queue buffer cfg  ----|\n");
      printk("|------------------------------------------|\n");
      printk("| %-7s| %-6s| %-11s| %-11s|\n","Tcont","queId","selfSize","shareSize");
      printk("|------------------------------------------|\n");
      for (uVar5 = uVar4 + 0x10; uVar5 < uVar4 + 0x18; uVar5 = uVar5 + 1) {
        red_get_out_buffer_queue_cfg(uVar5,&local_54,&local_50);
        printk("| %-7d| %-6d| %-11d| %-11d|\n",local_5c,uVar5 & 7,local_54,local_50);
      }
      printk("|------------------------------------------|\n");
      pcVar2 = "shareSize";
      printk("| %-7s  %-6s| %-11s| %-11s|\n","cpuUp",&_LC14,"selfSize","shareSize");
      printk("|------------------------------------------|\n");
      iVar1 = 0;
      do {
        red_get_out_buffer_queue_cfg(iVar1,&local_54,&local_50);
        iVar6 = iVar1 + 1;
        printk("| %-15d| %-11d| %-11d|\n",iVar1,local_54,local_50,pcVar2);
        iVar1 = iVar6;
      } while (iVar6 != 8);
      printk("|------------------------------------------|\n");
      printk("|------ red up all queue buffer cfg  ------|\n");
      printk("|------------------------------------------|\n");
      printk("| %-7s| %-6s| %-24s|\n","Tcont","queId","allSize");
      printk("|------------------------------------------|\n");
      for (; uVar4 < uVar8; uVar4 = uVar4 + 1) {
        red_get_buffer_queue_cfg(uVar4,local_4c);
        printk("| %-7d| %-6d| %-24d|\n",local_5c,uVar4 & 7,local_4c[0]);
      }
    }
    else {
      printk("\n|---- red dn inside queue buffer cfg ----|\n");
      if (local_5c < 5) {
        printk("| %-7s| %-6s| %-11s| %-11s|\n",&_LC4,"queId","guartSpace","shareSize");
        uVar4 = (local_5c + 0x28) * 8;
        uVar8 = uVar4 + 8;
        for (uVar5 = uVar4; uVar5 < uVar8; uVar5 = uVar5 + 1) {
          red_get_in_buffer_queue_cfg(uVar5,&local_54,&local_50);
          printk("| %-7d| %-6d| %-11d| %-11d|\n",local_5c,uVar5 & 7,local_54,local_50);
        }
        printk("|------------------------------------------|\n");
        printk("|---- red dn outside queue buffer cfg -----|\n");
        printk("|------------------------------------------|\n");
        printk("| %-7s| %-6s| %-11s| %-11s|\n",&_LC4,"queId","selfSize","shareSize");
        printk("|------------------------------------------|\n");
        for (uVar5 = uVar4 + 0x10; uVar5 < uVar4 + 0x18; uVar5 = uVar5 + 1) {
          red_get_out_buffer_queue_cfg(uVar5,&local_54,&local_50);
          printk("| %-7d| %-6d| %-11d| %-11d|\n",local_5c,uVar5 & 7,local_54,local_50);
        }
        printk("|------------------------------------------|\n");
        pcVar2 = "shareSize";
        printk("| %-7s  %-6s| %-11s| %-11s|\n","cpuDn",&_LC14,"selfSize","shareSize");
        printk("|------------------------------------------|\n");
        iVar1 = 8;
        do {
          red_get_out_buffer_queue_cfg(iVar1,&local_54,&local_50);
          iVar6 = iVar1 + 1;
          printk("| %-15d| %-11d| %-11d|\n",iVar1,local_54,local_50,pcVar2);
          iVar1 = iVar6;
        } while (iVar6 != 0x10);
        printk("|------ red dn all queue buffer cfg  ------|\n");
        printk("|------------------------------------------|\n");
        printk("| %-7s| %-6s| %-24s|\n",&_LC4,"queId","allSize");
        printk("|------------------------------------------|\n");
        for (; uVar4 < uVar8; uVar4 = uVar4 + 1) {
          red_get_buffer_queue_cfg(uVar4,local_4c);
          printk("| %-7d| %-6d| %-24d|\n",local_5c,uVar4 & 7,local_4c[0]);
        }
      }
      else {
        if (6 < local_5c) goto LAB_00075f9c;
        iVar1 = local_5c - 5;
        printk("| %-7s| %-6s| %-11s| %-11s|\n",&_LC20,"queId","guartSpace","shareSize");
        uVar4 = (local_5c + 0x28) * 8;
        uVar8 = uVar4 + 8;
        for (uVar5 = uVar4; uVar5 != uVar8; uVar5 = uVar5 + 1) {
          red_get_in_buffer_queue_cfg(uVar5,&local_54,&local_50);
          printk("| %-7d| %-6d| %-11d| %-11d|\n",iVar1,uVar5 & 7,local_54,local_50);
        }
        printk("|------------------------------------------|\n");
        printk("|---- red dn outside queue buffer cfg  ----|\n");
        printk("|------------------------------------------|\n");
        printk("| %-7s| %-6s| %-11s| %-11s|\n",&_LC20,"queId","selfSize","shareSize");
        printk("|------------------------------------------|\n");
        for (uVar5 = uVar4 + 0x10; uVar5 != uVar4 + 0x18; uVar5 = uVar5 + 1) {
          red_get_out_buffer_queue_cfg(uVar5,&local_54,&local_50);
          printk("| %-7d| %-6d| %-11d| %-11d|\n",iVar1,uVar5 & 7,local_54,local_50);
        }
        printk("|------------------------------------------|\n");
        pcVar2 = "shareSize";
        printk("| %-7s  %-6s| %-11s| %-11s|\n","cpuDn",&_LC14,"selfSize","shareSize");
        printk("|------------------------------------------|\n");
        iVar6 = 8;
        do {
          red_get_out_buffer_queue_cfg(iVar6,&local_54,&local_50);
          iVar7 = iVar6 + 1;
          printk("| %-15d| %-11d| %-11d|\n",iVar6,local_54,local_50,pcVar2);
          iVar6 = iVar7;
        } while (iVar7 != 0x10);
        printk("|------ red dn all queue buffer cfg  ------|\n");
        printk("|------------------------------------------|\n");
        printk("| %-7s| %-6s| %-24s|\n",&_LC4,"queId","allSize");
        printk("|------------------------------------------|\n");
        for (; uVar4 != uVar8; uVar4 = uVar4 + 1) {
          red_get_buffer_queue_cfg(uVar4,local_4c);
          printk("| %-7d| %-6d| %-24d|\n",iVar1,uVar4 & 7,local_4c[0]);
        }
      }
    }
  }
  printk("|------------------------------------------|\n");
  return param_4;
}

