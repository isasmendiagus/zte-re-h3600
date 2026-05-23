// module: tm.ko
// function: tm_port_brdcast_flood_ena_get @ 0x4f8c0
// size: 184 bytes
//

undefined4 tm_port_brdcast_flood_ena_get(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  int local_1c;
  int local_18 [3];
  
  local_1c = 0;
  if (param_2 == 0) {
    printk("ERROR:(%s:%d)","tm_api.c",0x1128);
    printk("param pp_ena is NULL\n");
    uVar2 = 0xffffffff;
  }
  else {
    iVar1 = getPort(param_1,local_18);
    if ((iVar1 == 0) && (local_18[0] != 8)) {
      iVar1 = sbrg_get_brdcst_fld_en(local_18[0],&local_1c);
      if (iVar1 == 0) {
        *(bool *)param_2 = local_1c != 0;
        uVar2 = 0;
      }
      else {
        printk("tm_port_brdcast_flood_ena_get fail\n");
        uVar2 = 0xffffffff;
      }
    }
    else {
      printk("tm_port_brdcast_flood_ena_get fail, error port %d\n",param_1);
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

