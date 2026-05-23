// module: tm.ko
// function: operInfoDel @ 0x57a48
// size: 704 bytes
//

undefined4 operInfoDel(uint param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  undefined4 local_64 [3];
  char local_58 [4];
  undefined4 local_54;
  short local_50;
  short local_46;
  undefined4 local_40 [5];
  short local_2c;
  char local_2a;
  short local_26;
  char local_21;
  
  uVar6 = param_1 & 0xffff;
  if (uVar6 < 0x8000) {
    if (tmInfoListInited == '\0') {
      uVar5 = 0xfffffff4;
      printk("no info to be deleted\n");
    }
    else {
      iVar1 = opcDbSetCrtList(param_2);
      if (iVar1 == 0) {
        uVar5 = 0;
        if ((int)param_1 < 0) {
          iVar1 = opcDbQosEntryValidSet((param_1 << 7) >> 0x17,0);
          if (iVar1 != 0) {
            uVar5 = 0xfffffff4;
            printk("set qos to invalid fail\n");
          }
        }
        else {
          __memzero(local_40);
          iVar1 = s_tmFlowInfoListHead;
          do {
            puVar2 = *(undefined4 **)(iVar1 + 0x10);
            if ((puVar2 != (undefined4 *)0x0) && (uVar6 == puVar2[1])) {
              puVar7 = puVar2;
              puVar9 = local_40;
              do {
                puVar10 = puVar9;
                puVar8 = puVar7;
                puVar7 = puVar8 + 4;
                uVar5 = puVar8[1];
                uVar3 = puVar8[2];
                uVar4 = puVar8[3];
                *puVar10 = *puVar8;
                puVar10[1] = uVar5;
                puVar10[2] = uVar3;
                puVar10[3] = uVar4;
                puVar9 = puVar10 + 4;
              } while (puVar7 != puVar2 + 8);
              uVar5 = puVar8[5];
              puVar10[4] = *puVar7;
              puVar10[5] = uVar5;
              iVar1 = s_tmSubRamInfoListHead;
              while ((puVar2 = *(undefined4 **)(iVar1 + 0x10), puVar2 == (undefined4 *)0x0 ||
                     (local_2c != *(short *)((int)puVar2 + 2)))) {
                iVar1 = *(int *)(iVar1 + 4);
                if (iVar1 == 0) {
                  printk("no subram info found by subRamID = %d\n");
                  return 0xfffffff4;
                }
              }
              puVar7 = local_64;
              puVar9 = puVar2;
              do {
                puVar10 = puVar9 + 4;
                uVar5 = puVar9[1];
                uVar3 = puVar9[2];
                puVar8 = puVar7 + 4;
                uVar4 = puVar9[3];
                *puVar7 = *puVar9;
                puVar7[1] = uVar5;
                puVar7[2] = uVar3;
                puVar7[3] = uVar4;
                puVar7 = puVar8;
                puVar9 = puVar10;
              } while (puVar10 != puVar2 + 8);
              *puVar8 = *puVar10;
              if ((((local_21 != '\0') || (local_2a != '\0')) && (local_26 != -1)) &&
                 (iVar1 = opcDbNatEntryValidSet((int)local_26,0), iVar1 != 0)) {
                printk("set nat to invalid fail\n");
                return 0xfffffff4;
              }
              if (((local_58[0] != '\0') && (local_50 != -1)) &&
                 (iVar1 = opcDbVlanEntryValidSet((int)local_50,0), iVar1 != 0)) {
                printk("set vlan to invalid fail\n");
                return 0xfffffff4;
              }
              iVar1 = opcDbCmdEntryValidSet((int)local_46,0);
              if (iVar1 != 0) {
                printk("set command to invalid fail\n");
                return 0xfffffff4;
              }
              iVar1 = opcDbSubRamEntryValidSet((int)local_2c);
              if (iVar1 == 0) {
                iVar1 = opcDbFlowEntryValidSet(uVar6);
                if (iVar1 == 0) {
                  return 0;
                }
                printk("set flow to invalid fail\n");
                return 0xfffffff4;
              }
              printk("set subram to invalid fail\n");
              return 0xfffffff4;
            }
            iVar1 = *(int *)(iVar1 + 4);
          } while (iVar1 != 0);
          uVar5 = 0xfffffff4;
          printk("no flow info found by flowID = %d\n",uVar6);
        }
      }
      else {
        uVar5 = 0xfffffff4;
      }
    }
  }
  else {
    uVar5 = 0xfffffff4;
    printk("ERROR:del flowId %d exceed 512",param_1);
  }
  return uVar5;
}

