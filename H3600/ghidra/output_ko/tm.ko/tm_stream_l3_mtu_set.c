// module: tm.ko
// function: tm_stream_l3_mtu_set @ 0x4611c
// size: 36 bytes
//

undefined4 tm_stream_l3_mtu_set(void)

{
  int iVar1;
  
  iVar1 = cla_set_l3_mtu_length_cfg();
  if (iVar1 == 0) {
    return 0;
  }
  printk("tm_stream_l3_mtu_set fail\n");
  return 0xffffffff;
}

