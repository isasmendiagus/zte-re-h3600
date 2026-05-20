// module: tm.ko
// function: tm_pon_pp_dpa_initial @ 0x4ea24
// size: 164 bytes
//

uint tm_pon_pp_dpa_initial(void)

{
  uint uVar1;
  undefined4 in_r3;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = 0;
  uVar3 = 0;
  do {
    iVar4 = 0;
    do {
      iVar2 = 0;
      do {
        uVar1 = dpa_set_tpid_i_sel_i(iVar5,iVar4,iVar2,iVar2,in_r3);
        iVar2 = iVar2 + 1;
        uVar3 = uVar3 | uVar1;
      } while (iVar2 != 4);
      iVar4 = iVar4 + 1;
    } while (iVar4 != 4);
    iVar5 = iVar5 + 1;
  } while (iVar5 != 9);
  iVar5 = 0;
  do {
    uVar1 = dpa_set_protocol_pkt_aly_en(iVar5,1);
    iVar5 = iVar5 + 1;
    uVar3 = uVar3 | uVar1;
  } while (iVar5 != 7);
  uVar1 = dpa_set_protocol_cpu_pps_en(1);
  if ((uVar1 | uVar3) != 0) {
    printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x2c4);
  }
  return uVar1 | uVar3;
}

