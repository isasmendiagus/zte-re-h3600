// module: tm.ko
// function: smac_get_stat @ 0x312ec
// size: 1848 bytes
//

undefined4 smac_get_stat(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14 [2];
  
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14[0] = 0;
  iVar1 = smac_get_statistics(param_1,0xf,&local_38);
  iVar2 = smac_get_statistics(param_1,0x10,&local_34);
  iVar3 = smac_get_statistics(param_1,0x23,&local_30);
  iVar4 = smac_get_statistics(param_1,0x24,&local_2c);
  iVar5 = smac_get_statistics(param_1,0x19,&local_28);
  iVar6 = smac_get_statistics(param_1,0x1a,&local_24);
  iVar7 = smac_get_statistics(param_1,0x1b,&local_20);
  iVar8 = smac_get_statistics(param_1,0x11,&local_1c);
  iVar9 = smac_get_statistics(param_1,0x12,&local_18);
  iVar10 = smac_get_statistics(param_1,0x13,local_14);
  if (((((((((iVar2 == 0 && iVar1 == 0) && iVar3 == 0) && iVar4 == 0) && iVar5 == 0) && iVar6 == 0)
        && iVar7 == 0) && iVar8 == 0) && iVar9 == 0) && iVar10 == 0) {
    printk("smac%d send total bytes    :%u\n",param_1,local_38);
    printk("smac%d send total frames   :%u\n",param_1,local_34);
    printk("smac%d send good bytes     :%u\n",param_1,local_30);
    printk("smac%d send good frames    :%u\n",param_1,local_2c);
    printk("smac%d send total unicast  :%u\n",param_1,local_28);
    printk("smac%d send total multicast:%u\n",param_1,local_24);
    printk("smac%d send total broadcast:%u\n",param_1,local_20);
    printk("smac%d send good broadcast :%u\n",param_1,local_1c);
    printk("smac%d send good multicast :%u\n",param_1,local_18);
    printk("smac%d send 64 bytes       :%u\n",param_1,local_14[0]);
    iVar1 = smac_get_statistics(param_1,0x14,&local_38);
    iVar2 = smac_get_statistics(param_1,0x15,&local_34);
    iVar3 = smac_get_statistics(param_1,0x16,&local_30);
    iVar4 = smac_get_statistics(param_1,0x17,&local_2c);
    iVar5 = smac_get_statistics(param_1,0x18,&local_28);
    iVar6 = smac_get_statistics(param_1,0x26,&local_24);
    iVar7 = smac_get_statistics(param_1,0x27,&local_20);
    iVar8 = smac_get_statistics(param_1,0x28,&local_1c);
    iVar9 = smac_get_statistics(param_1,0x29,&local_18);
    iVar10 = smac_get_statistics(param_1,0x2a,local_14);
    if (((((((((iVar2 == 0 && iVar1 == 0) && iVar3 == 0) && iVar4 == 0) && iVar5 == 0) && iVar6 == 0
           ) && iVar7 == 0) && iVar8 == 0) && iVar9 == 0) && iVar10 == 0) {
      printk("smac%d send 65-127 bytes   :%u\n",param_1,local_38);
      printk("smac%d send 128-255 bytes  :%u\n",param_1,local_34);
      printk("smac%d send 256-511 bytes  :%u\n",param_1,local_30);
      printk("smac%d send 512-1023 bytes :%u\n",param_1,local_2c);
      printk(&_LC68,param_1,local_28);
      printk("smac%d send pause frames   :%u\n",param_1,local_24);
      printk("smac%d send vlan  frames   :%u\n",param_1,local_20);
      printk("smac%d receive total frames:%u\n",param_1,local_1c);
      printk("smac%d receive total bytes :%u\n",param_1,local_18);
      printk("smac%d receive good  bytes :%u\n",param_1,local_14[0]);
      iVar1 = smac_get_statistics(param_1,0x39,&local_38);
      iVar2 = smac_get_statistics(param_1,0x2b,&local_34);
      iVar3 = smac_get_statistics(param_1,0x2c,&local_30);
      iVar4 = smac_get_statistics(param_1,0x33,&local_2c);
      iVar5 = smac_get_statistics(param_1,0x34,&local_28);
      iVar6 = smac_get_statistics(param_1,0x35,&local_24);
      iVar7 = smac_get_statistics(param_1,0x36,&local_20);
      iVar8 = smac_get_statistics(param_1,0x37,&local_1c);
      iVar9 = smac_get_statistics(param_1,0x38,&local_18);
      iVar10 = smac_get_statistics(param_1,0x2d,local_14);
      if (((((((((iVar2 == 0 && iVar1 == 0) && iVar3 == 0) && iVar4 == 0) && iVar5 == 0) &&
             iVar6 == 0) && iVar7 == 0) && iVar8 == 0) && iVar9 == 0) && iVar10 == 0) {
        printk("smac%d receive good unicast    :%u\n",param_1,local_38);
        printk("smac%d receive broadcast frames:%u\n",param_1,local_34);
        printk("smac%d receive multicast frames:%u\n",param_1,local_30);
        printk("smac%d receive 64 bytes        :%u\n",param_1,local_2c);
        printk("smac%d receive 65-127 bytes    :%u\n",param_1,local_28);
        printk("smac%d receive 128-255 bytes   :%u\n",param_1,local_24);
        printk("smac%d receive 256-511 bytes   :%u\n",param_1,local_20);
        printk("smac%d receive 512-1023 bytes  :%u\n",param_1,local_1c);
        printk(&_LC82,param_1,local_18);
        printk("smac%d receive crc  err frames :%u\n",param_1,local_14[0]);
        iVar1 = smac_get_statistics(param_1,0x2e,&local_38);
        iVar2 = smac_get_statistics(param_1,0x3a,&local_34);
        iVar3 = smac_get_statistics(param_1,0x3c,&local_30);
        iVar4 = smac_get_statistics(param_1,0x3e,&local_2c);
        iVar5 = smac_get_statistics(param_1,0x1c,&local_28);
        iVar6 = smac_get_statistics(param_1,0x3d,&local_24);
        iVar7 = smac_get_statistics(param_1,0x1d,&local_20);
        iVar8 = smac_get_statistics(param_1,0x1e,&local_1c);
        iVar9 = smac_get_statistics(param_1,0x20,&local_18);
        iVar10 = smac_get_statistics(param_1,0x21,local_14);
        if (((((((((iVar2 == 0 && iVar1 == 0) && iVar3 == 0) && iVar4 == 0) && iVar5 == 0) &&
               iVar6 == 0) && iVar7 == 0) && iVar8 == 0) && iVar9 == 0) && iVar10 == 0) {
          printk("smac%d receive align error frames     :%u\n",param_1,local_38);
          printk("smac%d receive length error frames    :%u\n",param_1,local_34);
          printk("smac%d receive pause frames           :%u\n",param_1,local_30);
          printk("smac%d receive vlan frames            :%u\n",param_1,local_2c);
          printk("smac%d send under flow error frames   :%u\n",param_1,local_28);
          printk("smac%d receive over  flow error frames:%u\n",param_1,local_24);
          printk("smac%d send single collison frames    :%u\n",param_1,local_20);
          printk("smac%d send multi collison frames     :%u\n",param_1,local_1c);
          printk("smac%d send late collison frames      :%u\n",param_1,local_18);
          printk("smac%d send excessive collison frames :%u\n",param_1,local_14[0]);
          iVar1 = smac_get_statistics(param_1,0x22,&local_38);
          iVar2 = smac_get_statistics(param_1,0x32,&local_34);
          iVar3 = smac_get_statistics(param_1,0x3f,&local_30);
          if ((iVar2 == 0 && iVar1 == 0) && iVar3 == 0) {
            printk("smac%d send carrier error frames    :%u\n",param_1,local_38);
            printk("smac%d receive oversize  frames     :%u\n",param_1,local_34);
            printk("smac%d receive watchdog error frames:%u\n",param_1,local_30);
            return 0;
          }
        }
      }
    }
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][smac_get_stat]read reg failed!\n");
  }
  return 0xffffffff;
}

