// module: switch.ko
// function: tcphy_proc_write @ 0x13048
// size: 424 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint tcphy_proc_write(undefined4 param_1,uint param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  byte *pbVar4;
  bool bVar5;
  uint local_30 [4];
  
  local_30[0] = 0;
  local_30[1] = 0;
  local_30[2] = 0;
  local_30[3] = 0;
  if (0x10 < param_3) {
    printk("too many data (count=%d max=%d)\n",param_3,0x10);
    return 0xffffffea;
  }
  uVar2 = *(uint *)(((uint)local_30 & 0xffffe000) + 8);
  if (!CARRY4(param_2,param_3) && param_2 + param_3 <= uVar2) {
    uVar2 = 0;
  }
  if (uVar2 == 0) {
    iVar1 = __copy_from_user(local_30);
    if (iVar1 == 0) goto LAB_000130a0;
  }
  else {
    if (param_3 == 0) {
LAB_000130a0:
      printk("ctrl_buffer = %s, count %d \n",local_30,param_3);
      if ((local_30[0] & 0xff) == 0x30) {
        bVar5 = false;
        loopback_enable = 0;
      }
      else {
        if ((local_30[0] & 0xff) != 0x31) {
          printk("ctrl_buffer = %s, please input right command\n",local_30);
          return 0xffffffff;
        }
        bVar5 = true;
        loopback_enable = 1;
      }
      if (_tm_port_unknwn_multicast_floodport_set == 0) {
        return param_3;
      }
      pbVar4 = (byte *)((int)&proc_create_data + 3);
      uVar2 = 0;
      do {
        while( true ) {
          pbVar4 = pbVar4 + 1;
          uVar3 = (uint)*pbVar4;
          if (uVar3 != _zte_api_sw_mac_set_port_learnlimit) break;
LAB_00013108:
          uVar2 = uVar2 + 1;
          if (_tm_port_unknwn_multicast_floodport_set <= uVar2) {
            return param_3;
          }
        }
        if (bVar5) {
          zte_api_sw_port_set_port_loopback(uVar3,1,1);
          loopback_status = 1;
          goto LAB_00013108;
        }
        uVar2 = uVar2 + 1;
        zte_api_sw_port_set_port_loopback(uVar3,1,0);
        loopback_status = 0;
        if (_tm_port_unknwn_multicast_floodport_set <= uVar2) {
          loopback_status = 0;
          return param_3;
        }
      } while( true );
    }
    __memzero(local_30,param_3);
  }
  printk("copy_from_user failed\n");
  return 0xffffffff;
}

