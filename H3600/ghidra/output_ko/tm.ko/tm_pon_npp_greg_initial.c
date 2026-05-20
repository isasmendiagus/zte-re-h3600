// module: tm.ko
// function: tm_pon_npp_greg_initial @ 0x4eb0c
// size: 168 bytes
//

uint tm_pon_npp_greg_initial(void)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar3 = 0;
  uVar4 = 0;
  do {
    if (uVar3 == 5) {
      uVar1 = tm_port_802x_authen_set(6,0);
      uVar3 = 7;
      uVar2 = tm_port_status_set(6,0);
      uVar4 = uVar4 | uVar1 | uVar2;
    }
    uVar1 = tm_port_802x_authen_set(uVar3,0);
    uVar2 = tm_port_status_set(uVar3,0);
    uVar3 = uVar3 + 1;
    uVar4 = uVar4 | uVar1 | uVar2;
  } while (uVar3 < 8);
  uVar3 = greg_set_wifi_queue1_protocol(1);
  if ((uVar3 | uVar4) != 0) {
    printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x2fb);
  }
  return uVar3 | uVar4;
}

