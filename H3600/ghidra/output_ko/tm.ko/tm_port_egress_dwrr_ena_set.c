// module: tm.ko
// function: tm_port_egress_dwrr_ena_set @ 0x46cc8
// size: 12 bytes
//

void tm_port_egress_dwrr_ena_set(int param_1)

{
  sch_set_quesch_sharp_enable(param_1 != 0);
  return;
}

