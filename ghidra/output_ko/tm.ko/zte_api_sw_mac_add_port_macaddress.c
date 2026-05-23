// module: tm.ko
// function: zte_api_sw_mac_add_port_macaddress @ 0x62168
// size: 336 bytes
//

undefined4
zte_api_sw_mac_add_port_macaddress(uint param_1,byte *param_2,undefined4 param_3,int param_4)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  int iVar7;
  undefined4 uVar8;
  int local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  bVar6 = *param_2;
  bVar1 = param_2[4];
  uVar8 = 0;
  bVar2 = param_2[5];
  bVar3 = param_2[1];
  bVar4 = param_2[2];
  bVar5 = param_2[3];
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  if ((bVar6 & 1) == 0) {
    __memzero(&local_3c);
    local_38 = (uint)CONCAT11(bVar1,bVar2) << 0x10;
    local_34 = CONCAT13(bVar6,CONCAT12(bVar3,CONCAT11(bVar4,bVar5)));
    local_38 = CONCAT31(local_38._1_3_,bVar6) & 0xffffff01;
    local_38 = CONCAT22(local_38._2_2_,CONCAT11(bVar6,(undefined1)local_38)) & 0xffff01ff;
    local_30 = param_3;
    if (param_4 == 0) {
      local_3c = 0xe;
      local_2c = CONCAT31(local_2c._1_3_,(char)(1 << (param_1 & 0xff)));
    }
    else {
      iVar7 = tm_mactable_lookup_get(&local_3c);
      if (iVar7 != 0) {
        printk("%s %d tm sdk failed!\n","zte_api_sw_mac_add_port_macaddress",0x8f3);
        return 0xffffffff;
      }
      if (local_3c == 0xf) {
        bVar6 = (byte)local_2c | (byte)(1 << (param_1 & 0xff));
      }
      else {
        bVar6 = (byte)(1 << (param_1 & 0xff));
      }
      local_2c = CONCAT31(local_2c._1_3_,bVar6);
      local_3c = 0xf;
    }
    iVar7 = tm_mactable_add_set(&local_3c);
    uVar8 = 0;
    if (iVar7 != 0) {
      printk("%s %d tm sdk failed!\n","zte_api_sw_mac_add_port_macaddress",0x905);
      uVar8 = 0xffffffff;
    }
  }
  else {
    printk("[%s] not support now!\n","zte_api_sw_mac_add_port_macaddress");
  }
  return uVar8;
}

