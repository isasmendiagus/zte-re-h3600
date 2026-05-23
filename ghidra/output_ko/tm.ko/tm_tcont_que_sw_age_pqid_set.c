// module: tm.ko
// function: tm_tcont_que_sw_age_pqid_set @ 0x54484
// size: 152 bytes
//

undefined4 tm_tcont_que_sw_age_pqid_set(uint param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  byte local_11 [5];
  
  local_11[0] = 0;
  if (param_1 < 8) {
    iVar1 = sch_get_sw_age_pqid(local_11);
    if (iVar1 == 0) {
      local_11[0] = local_11[0] & ~(byte)(1 << (param_1 & 0xff)) |
                    (byte)(param_2 << (param_1 & 0xff));
      iVar1 = sch_set_sw_age_pqid();
      uVar2 = 0;
      if (iVar1 != 0) {
        printk("tm_tcont_que_sw_age_pqid_set write fail\n");
        uVar2 = 0xffffffff;
      }
    }
    else {
      printk("tm_tcont_que_sw_age_pqid_set read fail\n");
      uVar2 = 0xffffffff;
    }
  }
  else {
    printk("tm_tcont_que_sw_age_pqid_set para error\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

