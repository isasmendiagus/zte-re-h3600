// module: switch.ko
// function: sw_alarm_scanforalarm @ 0x16bdc
// size: 980 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: ram */

int sw_alarm_scanforalarm(void)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  undefined1 *puVar7;
  uint uVar8;
  byte *pbVar9;
  byte local_4b;
  undefined1 local_4a;
  byte local_49;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  uVar6 = 0;
  local_4b = 0;
  local_4a = 0;
  local_49 = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  if (l_firstTime_48801 != '\0') {
    local_38 = 0;
    local_34 = 0;
    local_30 = 0;
    local_2c = 0;
    if (_tm_port_unknwn_multicast_floodport_set != 0) {
      do {
        sprintf((char *)&local_38,"eth%d",uVar6);
        iVar1 = dev_get_by_name(&init_net,&local_38);
        if (iVar1 == 0) {
          if (g_switch_debug_level != 0) {
            printk("sw_get_port_linkStatus@sw_alarm_scanforalarm the dev is null!\n");
          }
        }
        else {
          disableIRQinterrupts();
          iVar3 = coproc_movefrom_Privileged_only_Thread_and_Process_ID();
          *(int *)(iVar3 + *(int *)(iVar1 + 0x280)) = *(int *)(iVar3 + *(int *)(iVar1 + 0x280)) + -1
          ;
          netif_carrier_off();
        }
        uVar6 = uVar6 + 1;
      } while (uVar6 < _tm_port_unknwn_multicast_floodport_set);
    }
    l_firstTime_48801 = '\0';
  }
  if (_tm_port_unknwn_multicast_floodport_set == 0) {
    iVar1 = -1;
  }
  else {
    puVar7 = portalarmstat;
    pbVar9 = (byte *)((int)&proc_create_data + 3);
    uVar6 = 0;
    do {
      pbVar9 = pbVar9 + 1;
      uVar8 = (uint)*pbVar9;
      iVar1 = zte_api_sw_port_get_port_linkstate(uVar8,&local_4b,&local_4a,&local_49);
      if (iVar1 == 0) {
        local_4a = sw_ztespeed_to_cspplatspeed(local_4a);
        uVar2 = sw_zteduplex_to_cspplatduplex(local_49);
        uVar4 = (uint)local_4b;
        local_49 = (byte)uVar2;
        if ((int)*(short *)(puVar7 + 2) != uVar4) {
          if (g_LinkStateChangeCount == -1) {
            g_LinkStateChangeCount = 0;
          }
          else {
            g_LinkStateChangeCount = g_LinkStateChangeCount + 1;
          }
          if (3 < g_switch_debug_level) {
            printk("sw_alarm_scanforalarm alarm port%d state change!link=%d speed=%d duplex=%d\n",
                   uVar6,uVar4,local_4a,uVar2);
            uVar4 = (uint)local_4b;
            uVar2 = (uint)local_49;
          }
          iVar1 = Alarm_Msg(0,uVar4,local_4a,uVar2,uVar6 & 0xffff);
          if ((iVar1 != 0) && (g_switch_debug_level != 0)) {
            printk("Alarm_Msg@sw_alarm_scanforalarm return error!\nerror code=%d\n",iVar1);
          }
          *(ushort *)(puVar7 + 2) = (ushort)local_4b;
          sprintf((char *)&local_48,"eth%d",uVar6);
          iVar3 = dev_get_by_name(&init_net,&local_48);
          if (iVar3 == 0) {
            if (g_switch_debug_level != 0) {
              printk("sw_get_port_linkStatus@sw_alarm_scanforalarm the dev is null!\n");
            }
            goto LAB_00016c48;
          }
          disableIRQinterrupts();
          iVar5 = coproc_movefrom_Privileged_only_Thread_and_Process_ID();
          *(int *)(iVar5 + *(int *)(iVar3 + 0x280)) = *(int *)(iVar5 + *(int *)(iVar3 + 0x280)) + -1
          ;
          if (local_4b == 0) {
            netif_carrier_off();
            if (uVar8 == _zte_api_sw_mac_set_port_learnlimit) {
              LedActionSet(0xb200,uVar6);
            }
            else {
              g_LAN_LEDON_COUNT = g_LAN_LEDON_COUNT + -1;
              if (g_LAN_LEDON_COUNT == 0) {
                LedActionSet(0xb200,uVar6);
                g_LAN_ON_Flag = 0;
                goto LAB_00016c48;
              }
            }
          }
          else {
            netif_carrier_on();
            if (uVar8 == _zte_api_sw_mac_set_port_learnlimit) {
              LedActionSet(0xb100,uVar6);
            }
            else {
              turn_on_led_green(uVar6);
            }
          }
        }
        if ((((g_LAN_ON_Flag == 1) && (local_4b == 1)) &&
            (uVar8 != _zte_api_sw_mac_set_port_learnlimit)) &&
           (iVar3 = msecs_to_jiffies(1000),
           last_flash_jif == 0 || (last_flash_jif - jiffies) + iVar3 < 0)) {
          last_flash_jif = jiffies;
          turn_flash_led(uVar6,uVar8);
        }
      }
LAB_00016c48:
      uVar6 = uVar6 + 1;
      puVar7 = puVar7 + 8;
    } while (uVar6 < _tm_port_unknwn_multicast_floodport_set);
  }
  return iVar1;
}

