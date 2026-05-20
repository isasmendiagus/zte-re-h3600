// module: switch.ko
// function: sw_alarm_scanforalarm @ 0x16b0c
// size: 992 bytes
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
  int iVar9;
  byte *pbVar10;
  byte local_4b;
  undefined1 local_4a;
  byte local_49;
  char local_48 [16];
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  uVar6 = 0;
  local_4b = 0;
  local_4a = 0;
  local_49 = 0;
  local_48[0] = '\0';
  local_48[1] = '\0';
  local_48[2] = '\0';
  local_48[3] = '\0';
  local_48[4] = '\0';
  local_48[5] = '\0';
  local_48[6] = '\0';
  local_48[7] = '\0';
  local_48[8] = '\0';
  local_48[9] = '\0';
  local_48[10] = '\0';
  local_48[0xb] = '\0';
  local_48[0xc] = '\0';
  local_48[0xd] = '\0';
  local_48[0xe] = '\0';
  local_48[0xf] = '\0';
  if (l_firstTime_48678 != '\0') {
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
          iVar9 = coproc_movefrom_Privileged_only_Thread_and_Process_ID();
          *(int *)(iVar9 + *(int *)(iVar1 + 0x280)) = *(int *)(iVar9 + *(int *)(iVar1 + 0x280)) + -1
          ;
          netif_carrier_off();
        }
        uVar6 = uVar6 + 1;
      } while (uVar6 < _tm_port_unknwn_multicast_floodport_set);
    }
    l_firstTime_48678 = '\0';
  }
  if (_tm_port_unknwn_multicast_floodport_set == 0) {
    iVar1 = -1;
  }
  else {
    puVar7 = portalarmstat;
    pbVar10 = (byte *)((int)&tm_set_p2pmode + 3);
    iVar9 = -1;
    uVar6 = 0;
    do {
      pbVar10 = pbVar10 + 1;
      uVar8 = (uint)*pbVar10;
      iVar1 = zte_api_sw_port_get_port_linkstate(uVar8,&local_4b,&local_4a,&local_49);
      if (iVar1 != 0) goto LAB_00016b7c;
      local_4a = sw_ztespeed_to_cspplatspeed(local_4a);
      uVar2 = sw_zteduplex_to_cspplatduplex(local_49);
      uVar4 = (uint)local_4b;
      local_49 = (byte)uVar2;
      if ((int)*(short *)(puVar7 + 2) == uVar4) {
LAB_00016d14:
        if (g_LAN_ON_Flag != 1) goto LAB_00016b7c;
LAB_00016d20:
        if ((local_4b == 1) && (uVar8 != _tm_vlan_check_ena_set)) {
LAB_00016d38:
          turn_flash_led(uVar6,uVar8);
        }
      }
      else {
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
        sprintf(local_48,"eth%d",uVar6);
        iVar3 = dev_get_by_name(&init_net,local_48);
        if (iVar3 == 0) {
          if (g_switch_debug_level != 0) {
            printk("sw_get_port_linkStatus@sw_alarm_scanforalarm the dev is null!\n");
          }
        }
        else {
          disableIRQinterrupts();
          iVar5 = coproc_movefrom_Privileged_only_Thread_and_Process_ID();
          *(int *)(iVar5 + *(int *)(iVar3 + 0x280)) = *(int *)(iVar5 + *(int *)(iVar3 + 0x280)) + -1
          ;
          if (local_4b == 0) {
            netif_carrier_off();
            if ((uVar8 == _tm_vlan_check_ena_set) ||
               (LedActionSet(0xb200,iVar9), g_LAN_ON_Flag = 0, uVar8 == _tm_vlan_check_ena_set)) {
              fpga_write_reg(0xd3000,0x1f40fa0);
              goto LAB_00016d14;
            }
          }
          else {
            netif_carrier_on();
            if (uVar8 != _tm_vlan_check_ena_set) {
              LedActionSet(0xb100,iVar9);
              g_LAN_PACKET_COUNT = 0;
              g_LAN_ON_Flag = 1;
              if (uVar8 == _tm_vlan_check_ena_set) goto LAB_00016db8;
              if (local_4b != 1) goto LAB_00016b7c;
              goto LAB_00016d38;
            }
LAB_00016db8:
            fpga_write_reg(0xd3000,0x3f40050);
            if (g_LAN_ON_Flag == 1) goto LAB_00016d20;
          }
        }
      }
LAB_00016b7c:
      uVar6 = uVar6 + 1;
      iVar9 = iVar9 + 1;
      puVar7 = puVar7 + 8;
    } while (uVar6 < _tm_port_unknwn_multicast_floodport_set);
  }
  return iVar1;
}

