// module: wlan_debug_module.ko
// function: pktcnt_dscp_read @ 0x115fc
// size: 40 bytes
//

void pktcnt_dscp_read(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  uVar1 = PDE_DATA(*(undefined4 *)(param_2 + 0x10));
  single_open(param_2,_pktcnt_dscp_read,uVar1);
  return;
}

