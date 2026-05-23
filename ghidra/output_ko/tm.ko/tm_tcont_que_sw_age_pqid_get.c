// module: tm.ko
// function: tm_tcont_que_sw_age_pqid_get @ 0x5451c
// size: 112 bytes
//

undefined4 tm_tcont_que_sw_age_pqid_get(uint param_1,byte *param_2)

{
  int iVar1;
  undefined4 uVar2;
  byte local_11 [5];
  
  local_11[0] = 0;
  if (param_1 < 8) {
    iVar1 = sch_get_sw_age_pqid(local_11);
    if (iVar1 == 0) {
      *param_2 = (byte)((int)(uint)local_11[0] >> (param_1 & 0xff)) & 1;
      uVar2 = 0;
    }
    else {
      printk("tm_tcont_que_sw_age_pqid_get fail\n");
      uVar2 = 0xffffffff;
    }
  }
  else {
    printk("tm_tcont_que_sw_age_pqid_get para error\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

