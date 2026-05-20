// module: tm.ko
// function: zte_api_sw_mac_add_port_macfilterentry @ 0x6251c
// size: 440 bytes
//

undefined4
zte_api_sw_mac_add_port_macfilterentry(uint param_1,byte *param_2,undefined4 param_3,uint param_4)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  int iVar6;
  uint uVar7;
  byte bVar8;
  undefined4 uVar9;
  char local_3d;
  int local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  bVar8 = *param_2;
  bVar1 = param_2[5];
  bVar2 = param_2[4];
  uVar9 = 0;
  bVar3 = param_2[1];
  bVar4 = param_2[2];
  bVar5 = param_2[3];
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  if ((bVar8 & 1) == 0) {
    __memzero(&local_3c,0x14);
    local_38 = CONCAT13(bVar2,CONCAT12(bVar1,(undefined2)local_38));
    local_34 = CONCAT13(bVar8,CONCAT12(bVar3,CONCAT11(bVar4,bVar5)));
    iVar6 = tm_mac_exchange_mode_get(&local_3d);
    if (iVar6 == 0) {
      if (local_3d == '\0') {
        param_3 = 0;
      }
      local_30 = param_3;
      iVar6 = tm_mactable_lookup_get(&local_3c);
      if (iVar6 == 0) {
        if (local_3c == 0xf) {
          uVar7 = local_38 >> 8 & 0xff;
          bVar8 = (byte)local_2c | (byte)(1 << (param_1 & 0xff));
        }
        else {
          bVar8 = (byte)(1 << (param_1 & 0xff));
          uVar7 = 0;
        }
        local_2c = CONCAT31(local_2c._1_3_,bVar8);
        local_3c = 0xf;
        if (param_4 == 4 || (param_4 & 0xfd) == 0) {
          local_38 = local_38 & 0xffff0000;
        }
        else if (param_4 == 3) {
          if (uVar7 == 1) {
            printk("not support:config \'smac_ctrl=1\' and \'dmac_ctrl=1\' at the same time\n");
            return 0xffffffff;
          }
          uVar7 = local_38 >> 8;
          local_38 = CONCAT31((uint3)uVar7 & 0xffff00,1);
        }
        iVar6 = tm_mactable_add_set(&local_3c);
        uVar9 = 0;
        if (iVar6 != 0) {
          printk("%s %d tm sdk failed!\n","zte_api_sw_mac_add_port_macfilterentry",0x9c0);
          uVar9 = 0xffffffff;
        }
      }
      else {
        printk("%s %d tm sdk failed!\n","zte_api_sw_mac_add_port_macfilterentry",0x99e);
        uVar9 = 0xffffffff;
      }
    }
    else {
      printk("%s %d tm sdk failed!\n","zte_api_sw_mac_add_port_macfilterentry",0x98e);
      uVar9 = 0xffffffff;
    }
  }
  else {
    printk("[%s] multicast not support now!\n","zte_api_sw_mac_add_port_macfilterentry");
  }
  return uVar9;
}

