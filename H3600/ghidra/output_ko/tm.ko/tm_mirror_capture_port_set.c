// module: tm.ko
// function: tm_mirror_capture_port_set @ 0x4aa08
// size: 132 bytes
//

undefined4
tm_mirror_capture_port_set
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  switch(param_1) {
  case 0:
    uVar2 = 1;
    break;
  case 1:
    uVar2 = 2;
    break;
  case 2:
    uVar2 = 3;
    break;
  case 3:
    uVar2 = 4;
    break;
  case 4:
    uVar2 = 5;
    break;
  case 5:
    uVar2 = 0;
    break;
  case 6:
    uVar2 = 6;
    break;
  case 7:
    uVar2 = 7;
    break;
  default:
    printk("param p_port %d is invalid\n",param_1,param_3,param_4,param_4);
    return 0xffffffff;
  }
  iVar1 = sbrg_set_capture_pt(uVar2);
  if (iVar1 != 0) {
    printk("tm_mirror_capture_port_set fail\n");
    return 0xffffffff;
  }
  return 0;
}

