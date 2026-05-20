// module: tm.ko
// function: tm_port_status_get @ 0x47d90
// size: 168 bytes
//

undefined4 tm_port_status_get(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  int local_c;
  
  switch(param_1) {
  case 0:
    uVar2 = 0;
    break;
  case 1:
    uVar2 = 1;
    break;
  case 2:
    uVar2 = 2;
    break;
  case 3:
    uVar2 = 3;
    break;
  case 4:
    uVar2 = 4;
    break;
  default:
    printk("tm_port_status_get fail, error p_port %d\n",param_1);
    return 0xffffffff;
  case 6:
    uVar2 = 5;
    break;
  case 7:
    uVar2 = 6;
  }
  iVar1 = greg_get_port_closed(uVar2,&local_c);
  if (iVar1 == 0) {
    *(bool *)param_2 = local_c != 1;
    uVar2 = 0;
  }
  else {
    printk("tm_port_status_get fail\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

