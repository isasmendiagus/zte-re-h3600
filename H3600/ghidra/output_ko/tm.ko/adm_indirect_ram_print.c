// module: tm.ko
// function: adm_indirect_ram_print @ 0x2c774
// size: 508 bytes
//

undefined4 adm_indirect_ram_print(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  undefined4 local_30 [2];
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  if (param_1 == 0) {
    printk("**************** ADM BUCKET CFG INFO ************\n");
    pcVar4 = "adm_ebs";
    printk("%-10s%-10s%-11s%-14s%-8s%-8s%-8s%-8s\n","bucket_id","direction","bucket_ena",
           "bucket_couple","adm_cir","adm_eir","adm_cbs","adm_ebs");
    iVar2 = 0;
    do {
      iVar3 = adm_get_bucket_c(iVar2,&local_28);
      iVar1 = adm_get_bucket_e(iVar2,local_30);
      if (iVar1 != 0 || iVar3 != 0) {
        if ((g_tm_debug_level != 0) &&
           (iVar2 = ___ratelimit(_rs_7407,"adm_indirect_ram_print"), iVar2 != 0)) {
          printk("ERROR:(%s:%d)adm_indirect_ram_print failed!\n","pp_adm.c",0x6d6);
        }
        return 0xffffffff;
      }
      iVar3 = iVar2 + 1;
      printk("%-10d%-11d%-14d%-8d%-8d%-8d%-8d\n",iVar2,local_1c,local_20,local_24,local_28,
             local_30[0],local_30[0],pcVar4);
      iVar2 = iVar3;
    } while (iVar3 != 0x20);
  }
  else {
    if (param_1 != 1) {
      printk("invalid parameter!!!\n");
      return 0xffffffff;
    }
    printk("**** ADM CPUID TO PPS MAP ****\n");
    printk("%-8s%-14s\n","cpu_que","pps_bucket_id");
    iVar2 = 0;
    do {
      adm_get_protocol_pkt_map(0,iVar2,&local_28);
      printk("%-4s%-8d%-14d\n",&_LC82,iVar2,local_28);
      adm_get_protocol_pkt_map(1,iVar2,&local_28);
      iVar3 = iVar2 + 1;
      printk("%-4s%-8d%-14d\n",&_LC83,iVar2,local_28);
      iVar2 = iVar3;
    } while (iVar3 != 8);
  }
  return 0;
}

