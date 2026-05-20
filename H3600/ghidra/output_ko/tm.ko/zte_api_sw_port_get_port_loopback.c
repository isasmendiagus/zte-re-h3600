// module: tm.ko
// function: zte_api_sw_port_get_port_loopback @ 0x61f1c
// size: 76 bytes
//

undefined4
zte_api_sw_port_get_port_loopback
          (int param_1,undefined1 *param_2,undefined1 *param_3,undefined4 param_4)

{
  uint uVar1;
  
  uVar1 = zx_mdio_read(*(undefined1 *)((int)&uni_phy + param_1),0,param_3,&g_v4_fast_entry_up,
                       param_4);
  if ((uVar1 & 0x4000) == 0) {
    *param_3 = 0;
  }
  else {
    *param_3 = 1;
  }
  *param_2 = 1;
  return 0;
}

