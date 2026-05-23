// module: tm.ko
// function: sdet_info_store @ 0x6eb58
// size: 196 bytes
//

undefined4 sdet_info_store(undefined4 param_1,undefined4 *param_2,char *param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  char *__s1;
  undefined4 local_20;
  undefined4 local_1c [2];
  
  __s1 = (char *)*param_2;
  local_20 = 0;
  local_1c[0] = 0;
  iVar3 = capable(0xc);
  if (iVar3 == 0) {
    param_4 = 0xffffffff;
  }
  else {
    sscanf(param_3,"%d %d",&local_20,local_1c);
    disableIRQinterrupts();
    iVar3 = strcmp(__s1,"sonumtu");
    uVar2 = local_1c[0];
    uVar1 = local_20;
    if (iVar3 == 0) {
      iVar3 = zte_api_sw_other_set_onu_mtu(local_20,local_1c[0]);
      if (iVar3 == 0) {
        printk("zte_api_sw_other_set_onu_mtu input:port = %d, length = %d\n",uVar1,uVar2);
      }
      else {
        printk("zte_api_sw_other_set_onu_mtu fail, error code %d!\n");
      }
    }
  }
  return param_4;
}

