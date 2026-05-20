// module: mt7915.ko
// function: mt_engine_start @ 0x2553f8
// size: 752 bytes
//

int mt_engine_start(int param_1,undefined4 param_2,uint *param_3,undefined4 *param_4,
                   undefined4 param_5)

{
  undefined2 uVar1;
  int iVar2;
  byte bVar3;
  byte bVar4;
  uint *puVar5;
  int iVar6;
  undefined4 local_30;
  undefined4 local_2c;
  
  if (*(char *)(param_1 + 0x34) == '\0') {
    bVar3 = 1;
  }
  else {
    bVar3 = 2;
  }
  puVar5 = param_3;
  if ((*param_3 & 1) == 0) {
    bVar4 = 0;
    do {
      if ((((puVar5[1] == 0) && (iVar2 = sys_ad_alloc_mem(puVar5 + 1,0x33ff), iVar2 != 0)) ||
          (iVar2 = (*(code *)param_4[0x16])(param_1,1), iVar2 != 0)) ||
         (iVar2 = (*(code *)param_4[0x5b])(param_1,param_5,bVar4), iVar2 != 0)) goto LAB_00255564;
      if (puVar5[0x33a] != 0) {
        sys_ad_free_mem();
      }
      sys_ad_zero_mem(puVar5 + 0x335,0x18);
      puVar5[0x339] = 1;
      *(undefined1 *)(puVar5 + 0x338) = 0;
      puVar5[0x336] = 0;
      puVar5[0x337] = 0;
      puVar5[0x33a] = 0;
      puVar5[0x335] = 0;
      iVar2 = (*(code *)*param_4)(param_1,3,0,bVar4);
      if (iVar2 != 0) goto LAB_00255564;
      sys_ad_zero_mem(&local_30,8);
      uVar1 = CONCAT11(local_2c._3_1_,bVar4);
      bVar4 = bVar4 + 1;
      local_30 = 0x33b86;
      local_2c = CONCAT22(uVar1,0x100);
      iVar2 = (*(code *)param_4[4])(param_1,0x33b86,local_2c);
      if (iVar2 != 0) goto LAB_00255564;
      if (bVar4 == bVar3) {
        iVar2 = net_ad_init_thread(param_1,param_3,0);
        if ((iVar2 == 0) && (iVar2 = net_ad_exit_normal(param_1,param_2), iVar2 == 0)) {
          puVar5 = param_3 + 0x31c;
          bVar4 = 0;
          iVar2 = (int)param_3 + 0x205;
          while( true ) {
            iVar6 = iVar2;
            sys_ad_zero_mem(iVar6 + 0xf,0x328);
            *(undefined4 *)(iVar6 + -0x205) = 1;
            iVar2 = net_ad_init_wdev(param_1,iVar6 + -0x205,bVar4);
            if ((iVar2 != 0) ||
               (iVar2 = net_ad_init_txpwr(param_1,iVar6 + -0x205,bVar4), iVar2 != 0)) break;
            bVar4 = bVar4 + 1;
            if (*(char *)(param_1 + 0x34) == '\0') {
              *(undefined1 *)(iVar6 + 0xf) = 0x10;
            }
            else {
              *(undefined1 *)(iVar6 + 0xf) = 8;
            }
            *(undefined4 *)(iVar6 + -0x1f9) = 0;
            sys_ad_zero_mem(iVar6,0xd);
            *(undefined1 *)(iVar6 + 0xb) = 1;
            *(undefined1 *)(iVar6 + 0xc) = 1;
            *(undefined1 *)(iVar6 + 0xa6b) = 2;
            puVar5[2] = 0x60ff;
            puVar5[3] = 0x240004;
            puVar5 = puVar5 + 0x346;
            iVar2 = iVar6 + 0xd18;
            if (bVar3 <= bVar4) {
              printk("%s: enter test mode, wdev_idx=%u\n","mt_engine_start",
                     *(undefined1 *)(iVar6 + -0x1d9));
              return 0;
            }
          }
        }
LAB_00255564:
        printk("%s: enter test mode fail, err=0x%8x\n","mt_engine_start",iVar2);
        return iVar2;
      }
      puVar5 = puVar5 + 0x346;
    } while ((*puVar5 & 1) == 0);
  }
  else {
    bVar4 = 0;
  }
  printk("%s: test mode has already started, ","mt_engine_start");
  printk("wdev_idx:%u, band_idx:%u\n",(char)puVar5[0xb],bVar4);
  return 0;
}

