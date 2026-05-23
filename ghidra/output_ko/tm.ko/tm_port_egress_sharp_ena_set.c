// module: tm.ko
// function: tm_port_egress_sharp_ena_set @ 0x45ee8
// size: 12 bytes
//

void tm_port_egress_sharp_ena_set(int param_1)

{
  sch_set_tcont_sharp_enable(param_1 != 0);
  return;
}

