// module: tm.ko
// function: tm_stream_l3_mtu_get @ 0x4a768
// size: 36 bytes
//

undefined4 tm_stream_l3_mtu_get(void)

{
  int iVar1;
  
  iVar1 = cla_get_l3_mtu_length_cfg();
  if (iVar1 == 0) {
    return 0;
  }
  printk("tm_stream_l3_mtu_get fail\n");
  return 0xffffffff;
}

