// module: tm.ko
// function: tm_protocol_pkt_limit_map_set @ 0x4b2cc
// size: 168 bytes
//

undefined4
tm_protocol_pkt_limit_map_set(undefined4 param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  switch(param_1) {
  case 0:
    param_2 = param_2 & 0xff | 0x80;
    break;
  case 1:
    param_2 = param_2 & 0x7f | 0x100;
    break;
  case 2:
    param_2 = param_2 & 0xff | 0x180;
    break;
  case 3:
    param_2 = param_2 & 0x7f | 0x200;
    break;
  case 4:
    param_2 = param_2 & 0xff | 0x280;
    break;
  case 5:
    param_2 = param_2 & 0x7f;
    break;
  case 6:
    param_2 = param_2 & 0x7f | 0x300;
    break;
  case 7:
    param_2 = param_2 & 0xff | 0x380;
    break;
  default:
    printk("tm_protocol_pkt_limit_map_set fail, error port %d\n",param_1,param_3,param_1,param_4);
    return 0xffffffff;
  }
  iVar1 = cla_set_cpu_queue_id(param_2,param_3);
  if (iVar1 != 0) {
    printk("tm_protocol_pkt_limit_map_set fail\n");
    return 0xffffffff;
  }
  return 0;
}

