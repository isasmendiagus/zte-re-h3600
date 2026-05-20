// module: tm.ko
// function: tm_tcont_secsch_sharp_get @ 0x5458c
// size: 84 bytes
//

undefined4 tm_tcont_secsch_sharp_get(undefined4 param_1,undefined4 param_2,uint *param_3)

{
  int iVar1;
  undefined4 uVar2;
  int local_c;
  
  local_c = 0;
  iVar1 = sch_get_quesch_sharp_fill_rate(param_1,param_2,&local_c);
  if (iVar1 == 0) {
    *param_3 = (uint)(local_c * 5) >> 3;
    uVar2 = 0;
  }
  else {
    printk("tm_tcont_secsch_sharp_get fail\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

