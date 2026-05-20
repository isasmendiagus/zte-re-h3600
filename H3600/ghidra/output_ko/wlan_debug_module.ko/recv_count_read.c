// module: wlan_debug_module.ko
// function: recv_count_read @ 0x10fd4
// size: 40 bytes
//

void recv_count_read(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  uVar1 = PDE_DATA(*(undefined4 *)(param_2 + 0x10));
  single_open(param_2,_recv_count_read,uVar1);
  return;
}

