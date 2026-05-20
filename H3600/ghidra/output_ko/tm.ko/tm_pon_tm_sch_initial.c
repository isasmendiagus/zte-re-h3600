// module: tm.ko
// function: tm_pon_tm_sch_initial @ 0x54070
// size: 488 bytes
//

uint tm_pon_tm_sch_initial(void)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 in_r3;
  int iVar4;
  int iVar5;
  
  iVar1 = fpga_read_reg(0x10006);
  uVar2 = sch_set_dwrr_enable(1);
  if (uVar2 == 0) {
    uVar2 = sch_set_secsch_dwrr_enable(1);
    if (uVar2 == 0) {
      uVar2 = sch_set_que_sharp_enable(1);
      if (uVar2 == 0) {
        uVar2 = sch_set_tcont_sharp_enable(1);
        if (uVar2 == 0) {
          sch_set_hw_up_age_enable(1);
          uVar2 = sch_set_hw_dn_age_enable(1);
          iVar5 = 0;
          if (uVar2 == 0) {
            do {
              iVar4 = 0;
              uVar2 = tm_tcont_sharp_set(iVar5,1600000);
              do {
                uVar3 = tm_tcont_que_sharp_set(iVar5,iVar4,1600000);
                iVar4 = iVar4 + 1;
                uVar2 = uVar2 | uVar3;
              } while (iVar4 != 8);
              iVar5 = iVar5 + 1;
            } while (iVar5 != 0x20);
            if (uVar2 == 0) {
              if (iVar1 == 0) {
                tm_tcont_que_age_mode_set(0,1);
                tm_tcont_que_age_mode_set(1,1);
                tm_tcont_que_hw_age_time_set(100000000);
                return 0;
              }
              tm_tcont_que_age_mode_set(0,0);
              tm_tcont_que_age_mode_set(1,1);
              tm_tcont_que_hw_age_time_set(220000000);
              sch_set_oam_age_enable(1);
            }
            else {
              printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x11b);
            }
          }
          else {
            printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x111);
          }
        }
        else {
          printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x10b);
        }
      }
      else {
        printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x108,uVar2,in_r3);
      }
    }
    else {
      printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x104,uVar2,in_r3);
    }
  }
  else {
    printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x101,uVar2,in_r3);
  }
  return uVar2;
}

