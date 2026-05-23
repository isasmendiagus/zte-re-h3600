// module: tm.ko
// function: tm_pon_tm_red_initial @ 0x4d6e8
// size: 720 bytes
//

uint tm_pon_tm_red_initial(void)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  __memzero(&local_34,0x24);
  uVar1 = red_set_cfg_enable(0,1);
  if (uVar1 == 0) {
    uVar1 = red_set_open_out_en(1);
    if (uVar1 == 0) {
      uVar1 = red_set_trap_color_en(1);
      if (uVar1 == 0) {
        uVar1 = red_set_share_mode(1);
        if (uVar1 == 0) {
          uVar1 = red_set_in_share_max(0x3ff);
          if (uVar1 == 0) {
            uVar1 = red_set_up_out_share_max(0x3fff);
            if (uVar1 == 0) {
              uVar1 = 0;
              uVar2 = 0;
LAB_0004d780:
              do {
                if (uVar2 < 0x10) {
                  uVar4 = red_set_out_buffer_queue_cfg(uVar2,0x3ff,0);
                  uVar1 = uVar1 | uVar4;
                }
                else if (uVar2 < 0x150) {
                  uVar4 = red_set_out_buffer_queue_cfg(uVar2,0x40,0x7ff);
                  uVar1 = uVar1 | uVar4;
                }
                else {
                  if (uVar2 < 0x178) {
                    uVar4 = uVar2 + 1;
                    if ((uVar2 & 7) == 0) {
                      uVar3 = 0x200;
                    }
                    else {
                      uVar3 = 0x80;
                    }
                    uVar2 = red_set_out_buffer_queue_cfg(uVar2,0x40,uVar3);
                    uVar1 = uVar1 | uVar2;
                    uVar2 = uVar4;
                    if (uVar4 == 400) break;
                    goto LAB_0004d780;
                  }
                  if (uVar2 < 0x188) {
                    uVar3 = 0xc00;
                  }
                  else {
                    uVar3 = 0x3ff;
                  }
                  uVar4 = red_set_out_buffer_queue_cfg(uVar2,0x40,uVar3);
                  uVar1 = uVar1 | uVar4;
                }
                uVar2 = uVar2 + 1;
              } while (uVar2 != 400);
              if (uVar1 == 0) {
                uVar1 = 0;
                iVar6 = 0;
                do {
                  iVar5 = iVar6 + 1;
                  uVar2 = red_set_in_buffer_queue_cfg(iVar6,0x20,0x200);
                  uVar1 = uVar1 | uVar2;
                  iVar6 = iVar5;
                } while (iVar5 != 0x180);
                if (uVar1 == 0) {
                  local_34 = 0x3fff;
                  local_20 = 0x100;
                  local_1c = 0x200;
                  local_18 = 0x10;
                  local_30 = 0x80;
                  local_14 = 0x20;
                  local_28 = 0x80;
                  local_2c = 0xff;
                  local_24 = 0xff;
                  iVar6 = 0;
                  uVar1 = 0;
                  do {
                    uVar2 = red_set_buffer_queue_cfg(iVar6,&local_34);
                    iVar6 = iVar6 + 1;
                    uVar1 = uVar1 | uVar2;
                  } while (iVar6 != 0x180);
                  if (uVar1 != 0) {
                    printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0xd6);
                  }
                }
                else {
                  printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0xc6);
                }
              }
              else {
                printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0xbf);
              }
            }
            else {
              printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x9d);
            }
          }
          else {
            printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x98);
          }
        }
        else {
          printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x93);
        }
      }
      else {
        printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x8f);
      }
    }
    else {
      printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x8b);
    }
  }
  else {
    printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x87);
  }
  return uVar1;
}

