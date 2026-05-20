// module: mt7915.ko
// function: Show_ReptTable_Proc @ 0x80518
// size: 1496 bytes
//

undefined4 Show_ReptTable_Proc(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined2 uVar3;
  undefined *puVar4;
  undefined1 *puVar5;
  int iVar6;
  int iVar7;
  bool bVar8;
  uint local_30;
  undefined4 local_2c;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (param_1 == 0) {
    uVar2 = 0;
    if (-1 < DebugLevel) {
      printk("%s():Unexpected pAd NULL!\n","Show_ReptTable_Proc");
    }
  }
  else {
    puVar4 = &DAT_0036790e + param_1;
    iVar6 = 0;
    do {
      if (0 < DebugLevel) {
        printk("Band_%d_RpEn(%d),RpEnByAnyBand(%d),RpEn(%d)\n",iVar6,*puVar4,
               (&DAT_0036790f)[param_1] | (&DAT_0036790e)[param_1],(&DAT_0036790d)[param_1]);
      }
      bVar8 = iVar6 != 1;
      iVar6 = 1;
      puVar4 = puVar4 + 1;
    } while (bVar8);
    if ((&DAT_0036790d)[param_1] != '\0') {
      if ((((-1 < DebugLevel) && (printk("---------------------------------\n"), -1 < DebugLevel))
          && (printk("--------pRepeaterCliPool --------\n"), -1 < DebugLevel)) &&
         (printk("---------------------------------\n"), -1 < DebugLevel)) {
        printk("\n%-3s%-5s%-4s%-5s%-4s%-4s%-8s%-6s%-5s%-5s%-5s%-5s%-19s%-19s%-19s%-19s%-10s\n",&_LC5
               ,&_LC6,&_LC7,&_LC8,&_LC9,&_LC10,"CliType","Block",&_LC13,&_LC14,&_LC15,&_LC16,
               "REAL_MAC","FAKE_MAC","MUAR_MAC","MUAR_ROOT",&_LC21);
      }
      if (*(char *)(iVar1 + 0x14a) != '\0') {
        iVar6 = 0;
        iVar7 = 0;
        do {
          puVar5 = (undefined1 *)(*(int *)(&DAT_003687a8 + param_1) + iVar6);
          if ((-1 < DebugLevel) && (printk(&_LC22,puVar5[0xee]), -1 < DebugLevel)) {
            uVar2 = HcGetBandByWdev(puVar5 + 0xe0);
            printk(&_LC23,uVar2);
            if ((-1 < DebugLevel) && (printk(&_LC24,puVar5[4]), -1 < DebugLevel)) {
              if (*(int *)(puVar5 + 0x4144) == 0) {
                uVar3 = 0;
              }
              else {
                uVar3 = *(undefined2 *)(*(int *)(puVar5 + 0x4144) + 0xe0);
              }
              printk(&_LC23,uVar3);
              if (((((-1 < DebugLevel) && (printk(&_LC24,*puVar5), -1 < DebugLevel)) &&
                   ((printk(&_LC24,puVar5[1]), -1 < DebugLevel &&
                    (((printk(&_LC25,puVar5[3]), -1 < DebugLevel &&
                      (printk(&_LC26,puVar5[0x7c]), -1 < DebugLevel)) &&
                     (printk(&_LC23,puVar5[5]), -1 < DebugLevel)))))) &&
                  ((printk("%-5lu",*(undefined4 *)(puVar5 + 0xd88)), -1 < DebugLevel &&
                   (printk("%-5lu",*(undefined4 *)(puVar5 + 0xf10)), -1 < DebugLevel)))) &&
                 ((printk("%-5lu",*(undefined4 *)(puVar5 + 0xcbc)), -1 < DebugLevel &&
                  (printk("%02x:%02x:%02x:%02x:%02x:%02x  ",puVar5[0x7d],puVar5[0x7e],puVar5[0x7f],
                          puVar5[0x80],puVar5[0x81],puVar5[0x82]), -1 < DebugLevel)))) {
                printk("%02x:%02x:%02x:%02x:%02x:%02x  ",puVar5[0x83],puVar5[0x84],puVar5[0x85],
                       puVar5[0x86],puVar5[0x87],puVar5[0x88]);
              }
            }
          }
          __memzero(&local_30,4);
          __memzero(&local_2c,4);
          local_2c = CONCAT13(local_2c._3_1_ & 0xc0 | (puVar5[4] & 0x1f) << 1,(int3)local_2c) |
                     0x10000;
          hw_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820f5260,local_2c);
          do {
            hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f5260,&local_2c);
          } while ((local_2c & 0x10000) != 0);
          hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f525c,&local_30);
          if (-1 < DebugLevel) {
            printk("%02x:%02x:%02x:%02x:%02x:%02x  ",local_30 & 0xff,(local_30 << 0x10) >> 0x18,
                   (local_30 << 8) >> 0x18,local_30 >> 0x18,local_2c & 0xff,local_2c >> 8 & 0xff);
          }
          __memzero(&local_30,4);
          __memzero(&local_2c,4);
          local_2c = CONCAT13(local_2c._3_1_ & 0xc0 | puVar5[4] * '\x02' + 1U & 0x3f,(int3)local_2c)
                     | 0x10000;
          hw_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820f5260,local_2c);
          do {
            hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f5260,&local_2c);
          } while ((local_2c & 0x10000) != 0);
          hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f525c,&local_30);
          if ((-1 < DebugLevel) &&
             (printk("%02x:%02x:%02x:%02x:%02x:%02x",local_30 & 0xff,(local_30 << 0x10) >> 0x18,
                     (local_30 << 8) >> 0x18,local_30 >> 0x18,local_2c & 0xff,local_2c >> 8 & 0xff),
             -1 < DebugLevel)) {
            printk("  (%ld)\n",*(undefined4 *)(puVar5 + 0x74));
          }
          iVar7 = iVar7 + 1;
          iVar6 = iVar6 + 0x42f4;
        } while (iVar7 < (int)(uint)*(byte *)(iVar1 + 0x14a));
      }
    }
    uVar2 = 1;
  }
  return uVar2;
}

