// module: mt7915.ko
// function: parse_fw_v3 @ 0x1c0fc4
// size: 1736 bytes
//

uint parse_fw_v3(int param_1,int param_2,int *param_3)

{
  byte bVar1;
  undefined1 uVar2;
  int iVar3;
  uint uVar4;
  uint extraout_r1;
  undefined1 *puVar5;
  byte *pbVar6;
  int iVar7;
  undefined1 *puVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  int iVar13;
  int iVar14;
  undefined1 *local_40;
  undefined4 local_3c;
  int local_38;
  undefined4 local_34;
  uint local_30;
  byte *local_2c [2];
  
  iVar3 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  uVar4 = FUN_001c00c0(param_1,*(undefined4 *)(iVar3 + 0x118),param_1 + param_2 * 0x3c + 0xa78530);
  if (uVar4 == 0) {
    if (0 < DebugLevel) {
      printk("Parsing CPU %d fw tailer\n",param_2);
    }
    iVar13 = param_1 + param_2 * 0x3c;
    iVar3 = param_1 + param_2 * 0x3c + 0xa78540;
    puVar5 = (undefined1 *)(iVar3 + 0xc);
    iVar7 = *(int *)(iVar13 + 0xa78544) + -0x24;
    iVar14 = *(int *)(iVar13 + 0xa78540) + iVar7;
    puVar8 = (undefined1 *)(iVar14 + 6);
    *(undefined1 *)(iVar3 + 8) = *(undefined1 *)(*(int *)(iVar13 + 0xa78540) + iVar7);
    *(undefined1 *)(iVar13 + 0xa78549) = *(undefined1 *)(iVar14 + 1);
    *(undefined1 *)(iVar13 + 0xa7854a) = *(undefined1 *)(iVar14 + 2);
    *(undefined1 *)(iVar13 + 0xa7854b) = *(undefined1 *)(iVar14 + 3);
    *(undefined1 *)(iVar13 + 0xa7854c) = *(undefined1 *)(iVar14 + 4);
    do {
      puVar8 = puVar8 + 1;
      puVar5 = puVar5 + 1;
      *puVar5 = *puVar8;
    } while (puVar8 != (undefined1 *)(iVar14 + 0x10));
    puVar5 = (undefined1 *)(param_1 + param_2 * 0x3c + 0xa78556);
    do {
      puVar8 = puVar8 + 1;
      puVar5 = puVar5 + 1;
      *puVar5 = *puVar8;
    } while (puVar8 != (undefined1 *)(iVar14 + 0x1f));
    local_40 = (undefined1 *)(iVar14 + 0x20);
    iVar7 = param_1 + param_2 * 0x3c;
    FUN_001c062c(param_1 + param_2 * 0x3c + 0xa78568,&local_40);
    FUN_001bf6f4(iVar3 + 8);
    bVar1 = *(byte *)(iVar7 + 0xa7854a);
    *(byte *)(param_3 + 1) = bVar1;
    uVar4 = os_alloc_mem(param_1,param_3,(short)(ushort)bVar1 * 0x1c);
    if (uVar4 == 0) {
      if (bVar1 == 0) {
        iVar3 = 0;
      }
      else {
        iVar13 = (short)(ushort)bVar1 * 0x28;
        iVar3 = 0;
        uVar4 = 0;
        do {
          if (0 < DebugLevel) {
            printk("Parsing tailer region %d\n",uVar4);
          }
          local_40 = (undefined1 *)
                     (*(int *)(iVar7 + 0xa78540) + ((*(int *)(iVar7 + 0xa78544) + -0x24) - iVar13));
          FUN_001c062c(&local_34,&local_40);
          if (0 < DebugLevel) {
            printk("\tDecomp crc: 0x%x\n",local_34);
          }
          FUN_001c062c(&local_30,&local_40);
          if (0 < DebugLevel) {
            printk("\tDecomp size: 0x%x\n",local_30);
          }
          FUN_001c062c(local_2c,&local_40);
          if (0 < DebugLevel) {
            printk("\tDecomp block size: 0x%x\n",local_2c[0]);
          }
          local_40 = local_40 + 4;
          FUN_001c062c(&local_3c,&local_40);
          if (0 < DebugLevel) {
            printk("\tTarget address: 0x%x\n",local_3c);
          }
          FUN_001c062c(&local_38,&local_40);
          if (0 < DebugLevel) {
            printk("\tDownload size: %d\n",local_38);
          }
          puVar5 = local_40 + 1;
          uVar2 = *local_40;
          local_40 = puVar5;
          if ((((-1 < DebugLevel) && (printk("\tFeature set: "), -1 < DebugLevel)) &&
              (printk(&_LC5), -1 < DebugLevel)) && (printk(&_LC6,uVar2), -1 < DebugLevel)) {
            printk(&_LC2);
          }
          uVar11 = uVar4 + 1;
          iVar13 = iVar13 + -0x28;
          iVar14 = *param_3;
          iVar9 = iVar14 + uVar4 * 0x1c;
          *(int *)(iVar9 + 8) = local_38;
          *(undefined1 *)(iVar9 + 0xc) = uVar2;
          *(undefined4 *)(iVar9 + 4) = local_3c;
          *(undefined4 *)(iVar9 + 0x10) = local_34;
          *(uint *)(iVar9 + 0x14) = local_30;
          *(byte **)(iVar9 + 0x18) = local_2c[0];
          *(int *)(iVar14 + uVar4 * 0x1c) = *(int *)(iVar7 + 0xa78540) + iVar3;
          iVar3 = iVar3 + local_38;
          uVar4 = uVar11;
        } while (bVar1 != uVar11);
      }
      param_1 = param_1 + param_2 * 0x3c;
      if (*(char *)(param_1 + 0xa7854b) != '\x02') {
        if (0 < DebugLevel) {
          printk("%s: unknown format version %d\n","parse_fw_v3");
          return 0;
        }
        return 0;
      }
      if ((*(byte *)(param_1 + 0xa7854c) & 1) == 0) {
        return *(byte *)(param_1 + 0xa7854c) & 1;
      }
      local_2c[0] = (byte *)(*(int *)(param_1 + 0xa78540) + iVar3);
      if (0 < DebugLevel) {
        printk("\tRelease info: ");
      }
      local_2c[0] = local_2c[0] + 0x10;
      FUN_001c0fa0(&local_30,local_2c);
      pbVar6 = local_2c[0] + 2;
      bVar1 = local_2c[0][1];
      local_2c[0] = pbVar6;
      if (0 < DebugLevel) {
        printk("header tag = %d, total length = %d\n",bVar1,local_30 & 0xffff);
      }
      uVar4 = local_30;
      if (bVar1 != 0) {
        return 0;
      }
      do {
        if ((uVar4 & 0xffff) == 0) {
          return 0;
        }
        FUN_001c0fa0(&local_30,local_2c);
        pbVar6 = local_2c[0] + 2;
        uVar12 = (uint)*local_2c[0];
        uVar11 = (uint)local_2c[0][1];
        local_2c[0] = pbVar6;
        if (0 < DebugLevel) {
          printk("\ttag %d, padding length = %d, tag length = %d\n",uVar11,uVar12,local_30 & 0xffff)
          ;
          uVar11 = extraout_r1;
        }
        if (DebugLevel < 0) {
          uVar11 = local_30 & 0xffff;
          if (uVar11 != 0) {
LAB_001c1440:
            uVar10 = 0;
            iVar3 = DebugLevel;
            do {
              if (-1 < iVar3) {
                printk(&_LC1,local_2c[0][uVar10]);
                uVar11 = local_30 & 0xffff;
                iVar3 = DebugLevel;
              }
              uVar10 = uVar10 + 1;
            } while (uVar10 < uVar11);
            goto LAB_001c1458;
          }
        }
        else {
          printk("\tpayload: ",uVar11);
          uVar11 = local_30 & 0xffff;
          iVar3 = DebugLevel;
          if (uVar11 != 0) goto LAB_001c1440;
LAB_001c1458:
          if (-1 < iVar3) {
            printk(&_LC2);
            uVar11 = local_30 & 0xffff;
          }
        }
        local_2c[0] = local_2c[0] + uVar11 + uVar12;
        uVar4 = (uVar4 & 0xffff) + ((0xfffc - uVar11) - uVar12);
      } while( true );
    }
  }
  if (0 < DebugLevel) {
    printk("%s: parse fw fail\n","parse_fw_v3");
  }
  return uVar4;
}

