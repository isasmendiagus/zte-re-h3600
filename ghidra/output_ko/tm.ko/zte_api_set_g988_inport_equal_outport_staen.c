// module: tm.ko
// function: zte_api_set_g988_inport_equal_outport_staen @ 0x63c04
// size: 24 bytes
//

int zte_api_set_g988_inport_equal_outport_staen(void)

{
  int iVar1;
  
  iVar1 = pm_set_g988_inport_equal_outport_staen();
  return -(uint)(iVar1 != 0);
}

