// module: tm.ko
// function: tm_vlantable_add_set @ 0x51100
// size: 208 bytes
//

undefined4 tm_vlantable_add_set(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  int local_18 [2];
  
  iVar1 = getPort(param_1,local_18);
  if (iVar1 == -1 || local_18[0] == 8) {
    printk("tm_vlantable_add_set fail, error port %d\n",param_1);
    uVar2 = 0xffffffff;
  }
  else {
    switch(param_2) {
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
      printk("tm_vlantable_add_set fail, error p_attri %d\n",param_2);
      return 0xffffffff;
    }
    iVar1 = sbrg_add_vltbl(local_18[0],uVar2,param_3);
    uVar2 = 0;
    if (iVar1 != 0) {
      printk("ERROR:(%s:%d)","tm_api.c",0x40c4);
      printk("tm_vlantable_add_set fail\n");
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

