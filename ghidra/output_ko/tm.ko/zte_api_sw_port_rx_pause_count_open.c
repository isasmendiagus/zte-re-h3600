// module: tm.ko
// function: zte_api_sw_port_rx_pause_count_open @ 0x628dc
// size: 48 bytes
//

undefined4 zte_api_sw_port_rx_pause_count_open(undefined4 param_1)

{
  int iVar1;
  char *pcVar2;
  undefined4 uVar3;
  
  iVar1 = smac_set_rfe(param_1,1);
  if (iVar1 == 0) {
    pcVar2 = "zte_api_sw_port_rx_pause_count_open";
    uVar3 = 0;
  }
  else {
    uVar3 = 0xffffffff;
    pcVar2 = "set rx_pause_count enable failed\n";
  }
  printk(pcVar2);
  return uVar3;
}

