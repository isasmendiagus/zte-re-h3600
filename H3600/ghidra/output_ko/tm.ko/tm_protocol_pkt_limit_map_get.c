// module: tm.ko
// function: tm_protocol_pkt_limit_map_get @ 0x4b394
// size: 196 bytes
//

undefined4 tm_protocol_pkt_limit_map_get(undefined4 param_1,uint param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_c;
  
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
    printk("tm_protocol_pkt_limit_map_set fail, error port %d\n",param_1);
    return 0xffffffff;
  }
  iVar1 = cla_get_cpu_queue_id(param_2,&local_c);
  if (iVar1 == 0) {
    *param_3 = local_c;
    uVar2 = 0;
  }
  else {
    printk("cla_get_cpu_queue_id fail\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

