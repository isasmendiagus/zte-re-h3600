// module: tm.ko
// function: tm_mirror_ingress_ena_get @ 0x4cb08
// size: 124 bytes
//

undefined4 tm_mirror_ingress_ena_get(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_14 [2];
  
  if (param_1 == (undefined4 *)0x0) {
    printk("ERROR:(%s:%d)","tm_api.c",0x3166);
    printk("param pp_portMsk is NULL\n");
    uVar2 = 0xffffffff;
  }
  else {
    iVar1 = sbrg_get_igs_mirror_en(local_14);
    uVar2 = sbrg_change_portmask(local_14[0]);
    *param_1 = uVar2;
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      printk("tm_mirror_ingress_ena_get fail\n");
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

