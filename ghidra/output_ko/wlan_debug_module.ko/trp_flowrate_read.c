// module: wlan_debug_module.ko
// function: trp_flowrate_read @ 0x10738
// size: 40 bytes
//

void trp_flowrate_read(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  uVar1 = PDE_DATA(*(undefined4 *)(param_2 + 0x10));
  single_open(param_2,_trp_flowrate_read,uVar1);
  return;
}

