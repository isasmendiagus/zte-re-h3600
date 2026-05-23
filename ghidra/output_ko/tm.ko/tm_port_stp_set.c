// module: tm.ko
// function: tm_port_stp_set @ 0x48204
// size: 164 bytes
//

undefined4 tm_port_stp_set(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  switch(param_1) {
  case 0:
    uVar3 = 0;
    break;
  case 1:
    uVar3 = 1;
    break;
  case 2:
    uVar3 = 2;
    break;
  case 3:
    uVar3 = 3;
    break;
  case 4:
    uVar3 = 4;
    break;
  default:
    printk("tm_port_stp_set fail, error p_port %d\n",param_1);
    return 0xffffffff;
  case 6:
    uVar3 = 5;
    break;
  case 7:
    uVar3 = 6;
  }
  iVar1 = greg_set_port_stp_en(uVar3,param_2 != 0);
  iVar2 = greg_set_port_sel_stp_rstp(uVar3,param_3 != 0);
  if (iVar2 == 0 && iVar1 == 0) {
    return 0;
  }
  printk("tm_port_stp_set fail\n");
  return 0xffffffff;
}

