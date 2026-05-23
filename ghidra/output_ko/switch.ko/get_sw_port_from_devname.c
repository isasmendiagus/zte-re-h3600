// module: switch.ko
// function: get_sw_port_from_devname @ 0x167f8
// size: 412 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 get_sw_port_from_devname(char *param_1,uint *param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  uint local_20 [4];
  
  local_20[0] = 0;
  local_20[1] = 0;
  local_20[2] = 0;
  local_20[3] = 0;
  if (param_2 == (uint *)0x0 || param_1 == (char *)0x0) {
    if (g_switch_debug_level != 0) {
      printk("ERROR  argument !!!!\n");
    }
LAB_00016834:
    uVar1 = 0xffffffff;
  }
  else {
    strcpy((char *)local_20,param_1);
    iVar2 = strncmp((char *)local_20,"eth",3);
    if (iVar2 == 0) {
      uVar3 = (local_20[0] >> 0x18) - 0x30;
      if (((int)uVar3 < 0) || (_tm_port_unknwn_multicast_floodport_set < uVar3)) goto LAB_00016834;
      *param_2 = (uint)(byte)zte_api_fast_l3_session_del[local_20[0] >> 0x18];
    }
    else {
      iVar2 = strcmp((char *)local_20,"pon");
      if (((iVar2 == 0) || (iVar2 = strcmp((char *)local_20,"ptm0"), iVar2 == 0)) ||
         (iVar2 = strcmp((char *)local_20,"CPU"), iVar2 == 0)) {
        *param_2 = _tm_vlan_check_ena_set;
      }
      else {
        iVar2 = IfName2WlanIdmMap(local_20);
        if (iVar2 == 0) goto LAB_00016834;
        if (*(char *)(iVar2 + 0x25) == '\0') {
          if (param_3 == 1) {
            uVar3 = 6;
          }
          else {
            uVar3 = *(byte *)(iVar2 + 0x26) + 0x10;
          }
          *param_2 = uVar3;
        }
        else if (*(char *)(iVar2 + 0x25) == '\x01') {
          if (param_3 == 1) {
            uVar3 = 7;
          }
          else {
            uVar3 = *(byte *)(iVar2 + 0x26) + 0x18;
          }
          *param_2 = uVar3;
        }
      }
    }
    if (g_switch_debug_level < 3) {
      uVar1 = 0;
    }
    else {
      printk("devname = %s,port = %d!!\n",param_1,*param_2);
      uVar1 = 0;
    }
  }
  return uVar1;
}

