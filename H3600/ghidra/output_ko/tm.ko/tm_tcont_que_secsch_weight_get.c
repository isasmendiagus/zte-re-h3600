// module: tm.ko
// function: tm_tcont_que_secsch_weight_get @ 0x546a4
// size: 80 bytes
//

undefined4 tm_tcont_que_secsch_weight_get(undefined4 param_1,undefined4 param_2,uint *param_3)

{
  int iVar1;
  undefined4 uVar2;
  uint local_c;
  
  local_c = 0;
  iVar1 = sch_get_secsch_wrr_weight(param_1,param_2,&local_c);
  if (iVar1 == 0) {
    *param_3 = local_c >> 8;
    uVar2 = 0;
  }
  else {
    printk("tm_tcont_que_secsch_weight_get fail\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

