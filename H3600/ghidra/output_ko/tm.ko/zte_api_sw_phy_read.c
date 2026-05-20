// module: tm.ko
// function: zte_api_sw_phy_read @ 0x61f68
// size: 44 bytes
//

undefined4 zte_api_sw_phy_read(int param_1,undefined2 param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  
  uVar1 = zx_mdio_read(*(undefined1 *)((int)&uni_phy + param_1),param_2);
  *param_3 = uVar1;
  return 0;
}

