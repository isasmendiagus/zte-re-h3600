// module: tm.ko
// function: zte_api_sw_phy_write @ 0x62018
// size: 40 bytes
//

undefined4
zte_api_sw_phy_write(int param_1,undefined2 param_2,undefined2 param_3,undefined4 param_4)

{
  zx_mdio_write(*(undefined1 *)((int)&uni_phy + param_1),param_2,param_3,&g_v4_fast_entry_up,param_4
               );
  return 0;
}

