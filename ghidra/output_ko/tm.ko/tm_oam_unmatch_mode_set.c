// module: tm.ko
// function: tm_oam_unmatch_mode_set @ 0x46f78
// size: 100 bytes
//

undefined4
tm_oam_unmatch_mode_set(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
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
  default:
    printk("tm_oam_unmatch_mode_set fail, error mode %d\n",param_1,param_3,param_4,param_4);
    return 0xffffffff;
  }
  iVar1 = greg_set_oam_mode(uVar2);
  if (iVar1 != 0) {
    printk("tm_mac_learn_mode_set fail\n");
    return 0xffffffff;
  }
  return 0;
}

