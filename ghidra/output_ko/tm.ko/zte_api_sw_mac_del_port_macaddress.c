// module: tm.ko
// function: zte_api_sw_mac_del_port_macaddress @ 0x622bc
// size: 580 bytes
//

undefined4 zte_api_sw_mac_del_port_macaddress(uint param_1,byte *param_2,undefined4 param_3)

{
  uint uVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  int iVar8;
  int local_3c;
  undefined2 local_38;
  byte bStack_36;
  byte bStack_35;
  undefined4 local_34;
  undefined4 local_30;
  uint local_2c;
  
  bVar2 = *param_2;
  bVar3 = param_2[1];
  bVar4 = param_2[2];
  bVar5 = param_2[3];
  bVar6 = param_2[4];
  bVar7 = param_2[5];
  local_3c = 0;
  _local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  if ((bVar2 & 1) != 0) {
    printk("[%s] not support now!\n","zte_api_sw_mac_del_port_macaddress");
    return 0;
  }
  __memzero(&local_3c,0x14);
  _local_38 = CONCAT13(bVar6,CONCAT12(bVar7,local_38));
  local_34 = CONCAT13(bVar2,CONCAT12(bVar3,CONCAT11(bVar4,bVar5)));
  local_30 = param_3;
  iVar8 = tm_mactable_lookup_get(&local_3c);
  if (iVar8 == 0) {
    if (local_3c == 0) {
      if ((g_tm_debug_level != 0) &&
         (iVar8 = ___ratelimit(_rs_30717,"zte_api_sw_mac_del_port_macaddress"), iVar8 != 0)) {
        printk("[%s] failed, return no this mac!\n","zte_api_sw_mac_del_port_macaddress");
        return 0xffffffff;
      }
    }
    else if (((int)(local_2c & 0xff) >> (param_1 & 0xff) & 1U) == 0) {
      if ((g_tm_debug_level != 0) &&
         (iVar8 = ___ratelimit(_rs_30719,"zte_api_sw_mac_del_port_macaddress"), iVar8 != 0)) {
        printk("[%s] failed, return this mac is not in this port=%d!\n",
               "zte_api_sw_mac_del_port_macaddress",param_1);
        return 0xffffffff;
      }
    }
    else {
      uVar1 = 1 << (param_1 & 0xff);
      if ((local_2c & 0xff) == uVar1) {
        iVar8 = tm_mactable_delete_set(&local_3c);
        if (iVar8 == 0) {
          return 0;
        }
        if ((g_tm_debug_level != 0) &&
           (iVar8 = ___ratelimit(_rs_30721,"zte_api_sw_mac_del_port_macaddress"), iVar8 != 0)) {
          printk("%s %d failed!\n","zte_api_sw_mac_del_port_macaddress",0x939);
          return 0xffffffff;
        }
      }
      else {
        local_2c = CONCAT31(local_2c._1_3_,(byte)local_2c & ~(byte)uVar1);
        iVar8 = tm_mactable_add_set();
        if (iVar8 == 0) {
          return 0;
        }
        if ((g_tm_debug_level != 0) &&
           (iVar8 = ___ratelimit(_rs_30723,"zte_api_sw_mac_del_port_macaddress"), iVar8 != 0)) {
          printk("%s %d failed!\n","zte_api_sw_mac_del_port_macaddress",0x942);
          return 0xffffffff;
        }
      }
    }
  }
  else if ((g_tm_debug_level != 0) &&
          (iVar8 = ___ratelimit(_rs_30713,"zte_api_sw_mac_del_port_macaddress"), iVar8 != 0)) {
    printk("%s %d failed!\n","zte_api_sw_mac_del_port_macaddress",0x927);
  }
  return 0xffffffff;
}

