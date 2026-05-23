// module: mt7915.ko
// function: Show_DescInfo_Proc @ 0xdb124
// size: 888 bytes
//

undefined4 Show_DescInfo_Proc(int param_1,char *param_2)

{
  byte *pbVar1;
  undefined4 uVar2;
  char *pcVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  char *local_2c [2];
  
  local_2c[0] = param_2;
  pbVar1 = (byte *)hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  if ((((local_2c[0] == (char *)0x0) || (*local_2c[0] == '\0')) ||
      (pcVar3 = strsep(local_2c,":"), local_2c[0] == (char *)0x0)) || (*local_2c[0] == '\0')) {
LAB_000db15c:
    if ((0 < DebugLevel) &&
       (printk("Usage:   iwpriv $(inf_name) show descinfo=$(tx/rx):$(resource_idx)\n"),
       0 < DebugLevel)) {
      printk("Example: iwpriv ra0 show descinfo=tx:0\n");
    }
    uVar2 = 0;
  }
  else {
    uVar4 = os_str_tol(local_2c[0],0,10);
    iVar5 = rtstrcasecmp(pcVar3,&_LC286);
    if (iVar5 == 0) {
      iVar5 = rtstrcasecmp(pcVar3,&_LC293);
      if (iVar5 == 0) goto LAB_000db15c;
      if ((int)uVar4 < (int)(uint)pbVar1[1]) {
        iVar5 = *(int *)(*(int *)(pbVar1 + 4) + (uVar4 & 0xff) * 4);
        uVar10 = (uint)*(ushort *)(iVar5 + 0x14);
        if (0 < DebugLevel) {
          printk("Rx Ring %d ---------------------------------\n",uVar4);
        }
        if (uVar10 != 0) {
          iVar9 = 0;
          uVar4 = 0;
          do {
            iVar8 = *(int *)(*(int *)(iVar5 + 0x18) + iVar9 + 4);
            if (DebugLevel < 1) {
              if (iVar8 != 0) {
LAB_000db310:
                dump_rxd(param_1,iVar8);
                if (0 < DebugLevel) {
                  printk("pRxD->DDONE = %x\n",*(byte *)(iVar8 + 7) >> 7);
                }
              }
            }
            else {
              printk("Desc #%d\n",uVar4);
              if (iVar8 != 0) goto LAB_000db310;
              if (0 < DebugLevel) {
                printk("RXD null!!\n");
              }
            }
            uVar4 = uVar4 + 1;
            iVar9 = iVar9 + 0x24;
          } while (uVar4 != uVar10);
        }
      }
      else if (0 < DebugLevel) {
        printk("Rx resource_idx %d out of range\n",uVar4);
      }
    }
    else if ((int)uVar4 < (int)(uint)*pbVar1) {
      iVar5 = *(int *)(*(int *)(pbVar1 + 8) + (uVar4 & 0xff) * 4);
      if (0 < DebugLevel) {
        printk("Tx Ring %d ---------------------------------\n",uVar4);
      }
      if (*(short *)(iVar5 + 0x5a) != 0) {
        iVar8 = 0;
        iVar9 = iVar8;
        do {
          iVar6 = *(int *)(iVar5 + 0xc) + iVar8;
          iVar7 = *(int *)(iVar6 + 0x1c);
          iVar6 = *(int *)(iVar6 + 4);
          if (DebugLevel < 1) {
            if (iVar6 != 0) {
LAB_000db220:
              dump_txd(param_1,iVar6);
              goto LAB_000db22c;
            }
LAB_000db284:
            if (iVar7 != 0) goto LAB_000db234;
          }
          else {
            printk("Desc #%d\n",iVar9);
            if (iVar6 != 0) goto LAB_000db220;
            if (DebugLevel < 1) goto LAB_000db284;
            printk("TXD null!!\n");
LAB_000db22c:
            if (iVar7 == 0) {
              if (0 < DebugLevel) {
                printk("pkt is null\n");
              }
            }
            else {
LAB_000db234:
              asic_dump_tmac_info(param_1,iVar7);
              if (0 < DebugLevel) {
                printk("pkt physical address = %x\n",
                       *(undefined4 *)(*(int *)(iVar5 + 0xc) + iVar8 + 0x14));
              }
            }
          }
          iVar9 = iVar9 + 1;
          iVar8 = iVar8 + 0x24;
        } while (iVar9 < (int)(uint)*(ushort *)(iVar5 + 0x5a));
      }
    }
    else if (0 < DebugLevel) {
      printk("Tx resource_idx %d out of range\n",uVar4);
      return 1;
    }
    uVar2 = 1;
  }
  return uVar2;
}

