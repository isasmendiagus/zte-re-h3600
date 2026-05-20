// module: switch.ko
// function: ethdrv_port_dev_change_mtu @ 0x10024
// size: 28 bytes
//

uint ethdrv_port_dev_change_mtu(int param_1,uint param_2)

{
  if (*(uint *)(*(int *)(param_1 + 0x4c4) + 0x14c) < param_2) {
    param_2 = 0xffffffde;
  }
  else {
    *(uint *)(param_1 + 0x14c) = param_2;
  }
  return param_2;
}

