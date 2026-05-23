// module: tm.ko
// function: tm_pon_npp_pm_initial @ 0x4eee8
// size: 264 bytes
//

uint tm_pon_npp_pm_initial(void)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  iVar4 = 0;
  uVar5 = 0;
  do {
    uVar1 = pm_set_in_port_rule_valid(iVar4,iVar4,0);
    uVar2 = pm_set_out_port_rule_valid(iVar4,iVar4,0);
    iVar4 = iVar4 + 1;
    uVar5 = uVar5 | uVar2 | uVar1;
  } while (iVar4 != 8);
  if (uVar5 == 0) {
    uVar1 = pm_set_g988_mode(0,0);
    uVar2 = pm_set_g988_mode(1,1);
    uVar3 = pm_set_g988_mode(2,3);
    uVar3 = uVar2 | uVar1 | uVar3;
    if (uVar3 == 0) {
      __memzero(&local_1c,0xc);
      local_14 = 5;
      local_1c = 1;
      local_18 = 1;
      zte_api_set_port_rule(&local_1c);
      zte_api_set_g988_cpu_not_drop_staen(0);
      zte_api_set_g988_inport_equal_outport_staen(1);
    }
    else {
      printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x3be);
      uVar5 = uVar3;
    }
  }
  else {
    printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x3b9);
  }
  return uVar5;
}

