// module: wlan_debug_module.ko
// function: pktcnt_dbgflag_read @ 0x1164c
// size: 40 bytes
//

void pktcnt_dbgflag_read(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  uVar1 = PDE_DATA(*(undefined4 *)(param_2 + 0x10));
  single_open(param_2,_pktcnt_dbgflag_read,uVar1);
  return;
}

