// module: switch.ko
// function: ethdrv_port_dev_set_mac_addr @ 0x103c4
// size: 60 bytes
//

undefined4 ethdrv_port_dev_set_mac_addr(int param_1,int param_2)

{
  if (param_2 != 0 && param_1 != 0) {
    memcpy(*(void **)(param_1 + 0x1dc),(void *)(param_2 + 2),(uint)*(byte *)(param_1 + 0x179));
    return 0;
  }
  return 0xffffffde;
}

