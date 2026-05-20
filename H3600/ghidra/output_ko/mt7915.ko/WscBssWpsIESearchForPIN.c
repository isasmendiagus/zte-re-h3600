// module: mt7915.ko
// function: WscBssWpsIESearchForPIN @ 0x1e79a4
// size: 1620 bytes
//

byte WscBssWpsIESearchForPIN
               (undefined4 param_1,int param_2,int param_3,int param_4,int param_5,ushort *param_6)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  undefined1 uVar4;
  ushort uVar5;
  char cVar6;
  ushort uVar7;
  uint uVar8;
  int iVar9;
  char cVar10;
  undefined1 *puVar11;
  char cVar12;
  undefined1 *puVar13;
  char local_78;
  undefined1 auStack_77 [16];
  undefined1 auStack_67 [16];
  undefined1 auStack_57 [6];
  undefined1 local_51;
  char local_50;
  undefined1 auStack_4f [32];
  undefined1 local_2f;
  
  memset(auStack_77,0,0x10);
  local_78 = '\0';
  if (2 < DebugLevel) {
    printk(&_LC159,"WscBssWpsIESearchForPIN");
  }
  iVar9 = 0;
  bVar1 = 0;
  __memzero(auStack_67,0x3f);
  cVar10 = '\0';
  cVar12 = '\0';
LAB_001e7a44:
  do {
    if (param_5 < 1 || cVar12 != '\0') {
      return bVar1 | (cVar10 != '\0' && cVar12 != '\0');
    }
    if ((char)*param_6 == -0x23) {
      iVar3 = memcmp(param_6 + 1,&WPS_OUI,4);
      if (iVar3 == 0) {
        param_6 = param_6 + 3;
        param_5 = param_5 + -6;
        cVar12 = '\0';
        if (*(byte *)(param_2 + 0x6c) < 4) {
          if (0 < param_5) {
LAB_001e7acc:
            cVar12 = '\0';
            do {
              uVar5 = *param_6;
              uVar7 = uVar5 << 8 | uVar5 >> 8;
              if (uVar7 == 0x1041) {
                hex_dump("SelReg:",param_6,5);
                cVar10 = (char)param_6[2];
                if (2 < DebugLevel) {
                  printk("bSelReg = %d\n",cVar10);
                  uVar5 = *param_6;
                  uVar7 = uVar5 << 8 | uVar5 >> 8;
                  goto LAB_001e7b28;
                }
                uVar7 = *param_6 << 8 | *param_6 >> 8;
                if (uVar7 == 0x1012) {
                  uVar7 = param_6[2] << 8 | param_6[2] >> 8;
                  goto LAB_001e7c38;
                }
              }
              else {
LAB_001e7b28:
                if (uVar7 == 0x1012) {
                  uVar7 = param_6[2] << 8 | param_6[2] >> 8;
                  if (DebugLevel < 3) {
                    if (uVar7 != 0 || *(int *)(param_2 + 4) != 1) {
LAB_001e7be0:
                      uVar7 = CONCAT11((char)uVar5,(char)(uVar5 >> 8));
                      goto joined_r0x001e7adc;
                    }
                  }
                  else {
                    printk("WscPINBssTableSort : DevicePasswordID = 0x%04x\n",uVar7);
LAB_001e7c38:
                    if (uVar7 != 0 || *(int *)(param_2 + 4) != 1) {
                      uVar5 = *param_6;
                      goto LAB_001e7be0;
                    }
                    if ((2 < DebugLevel) && (printk("DPID=PIN Found -->\n"), 2 < DebugLevel)) {
                      printk("#  Bssid %02x:%02x:%02x:%02x:%02x:%02x\n",*(undefined1 *)(param_3 + 6)
                             ,*(undefined1 *)(param_3 + 7),*(undefined1 *)(param_3 + 8),
                             *(undefined1 *)(param_3 + 9),*(undefined1 *)(param_3 + 10),
                             *(undefined1 *)(param_3 + 0xb));
                    }
                  }
                  cVar12 = '\x01';
                  if (*(byte *)(param_3 + 0xc) < 0xf) {
                    local_50 = '\x01';
                  }
                  else {
                    local_50 = '\x02';
                  }
                  RTMPMoveMemory(auStack_57,param_3 + 6,6);
                  local_51 = *(undefined1 *)(param_3 + 0xc);
                  RTMPZeroMemory(auStack_4f,0x20);
                  RTMPMoveMemory(auStack_4f,param_3 + 0x95,*(undefined1 *)(param_3 + 0x94));
                  local_2f = *(undefined1 *)(param_3 + 0x94);
                  uVar7 = *param_6 << 8 | *param_6 >> 8;
                }
              }
joined_r0x001e7adc:
              if (uVar7 == 0x1047) {
                RTMPMoveMemory(auStack_67,param_6 + 2,0x10);
              }
              uVar8 = (param_6[1] & 0xff) << 8 | (uint)(param_6[1] >> 8);
              param_5 = param_5 + (-4 - uVar8);
              param_6 = (ushort *)((int)param_6 + uVar8 + 4);
            } while (0 < param_5);
            cVar6 = cVar12;
            if (cVar10 != '\x01') {
              cVar6 = '\0';
            }
            if (cVar6 != '\0') {
              if (*(char *)(param_2 + 99) == '\b') {
                return 1;
              }
              if (*(char *)(param_2 + 99) == '\0') {
                uVar8 = 0;
                if (local_78 != '\0') {
LAB_001e7db8:
                  if (*(char *)(param_2 + 0x2a59) == '\0') {
                    if ((local_50 == '\x01') &&
                       (iVar3 = param_4 + iVar9 * 0x3f, *(char *)(iVar3 + 0x17) != '\x01')) {
LAB_001e7ef0:
                      RTMPMoveMemory(iVar3 + 0x10,auStack_57,6);
                      RTMPZeroMemory(iVar3 + 0x18,0x20);
                      RTMPMoveMemory(iVar3 + 0x18,auStack_4f,local_2f);
                      *(undefined1 *)(iVar3 + 0x38) = local_2f;
                      *(undefined1 *)(iVar3 + 0x16) = local_51;
                      if (local_78 == '\0') {
                        uVar8 = (uint)*(byte *)(param_2 + 99);
                        goto LAB_001e7e0c;
                      }
                    }
                  }
                  else if (((*(char *)(param_2 + 0x2a59) == '\x01') && (local_50 == '\x02')) &&
                          (iVar3 = param_4 + iVar9 * 0x3f, *(char *)(iVar3 + 0x17) != '\x02'))
                  goto LAB_001e7ef0;
                  cVar10 = '\x01';
                  cVar12 = cVar10;
                  goto LAB_001e7a44;
                }
              }
              else {
                iVar9 = 0;
                iVar3 = param_4;
                do {
                  FUN_001e06a0(iVar3,auStack_67,auStack_77,&local_78);
                  iVar3 = iVar3 + 0x3f;
                  if (local_78 != '\0') goto LAB_001e7db8;
                  uVar8 = (uint)*(byte *)(param_2 + 99);
                  iVar9 = iVar9 + 1;
                } while (iVar9 < (int)uVar8);
              }
LAB_001e7e0c:
              puVar11 = (undefined1 *)(param_4 + (short)uVar8 * 0x3f);
              puVar13 = puVar11 + 0x10;
              RTMPMoveMemory(puVar11,auStack_67);
              RTMPMoveMemory(puVar13,param_3 + 6,6);
              RTMPZeroMemory(puVar11 + 0x18,0x20);
              RTMPMoveMemory(puVar11 + 0x18,param_3 + 0x95,*(undefined1 *)(param_3 + 0x94));
              puVar11[0x38] = *(undefined1 *)(param_3 + 0x94);
              bVar2 = *(byte *)(param_3 + 0xc);
              puVar11[0x16] = bVar2;
              if (bVar2 < 0xf) {
                uVar4 = 1;
              }
              else {
                uVar4 = 2;
              }
              puVar11[0x17] = uVar4;
              iVar3 = DebugLevel;
              if (-1 < DebugLevel) {
                printk("UUID-E= ");
                iVar3 = DebugLevel;
              }
              do {
                if (-1 < iVar3) {
                  printk("%02x  ",*puVar11);
                  iVar3 = DebugLevel;
                }
                puVar11 = puVar11 + 1;
              } while (puVar11 != puVar13);
              if (-1 < iVar3) {
                printk(&_LC13);
              }
              cVar10 = '\x01';
              cVar12 = '\x01';
              *(char *)(param_2 + 99) = *(char *)(param_2 + 99) + '\x01';
              goto LAB_001e7a44;
            }
          }
          if (bVar1 != 1) goto LAB_001e7a44;
        }
        else if (0 < param_5) {
          bVar1 = 1;
          goto LAB_001e7acc;
        }
        iVar3 = param_4 + (uint)*(byte *)(param_2 + 99) * 0x3f;
        RTMPMoveMemory(iVar3,auStack_67,0x10);
        RTMPMoveMemory(iVar3 + 0x10,param_3 + 6,6);
        RTMPZeroMemory(iVar3 + 0x18,0x20);
        RTMPMoveMemory(iVar3 + 0x18,param_3 + 0x95,*(undefined1 *)(param_3 + 0x94));
        *(undefined1 *)(iVar3 + 0x38) = *(undefined1 *)(param_3 + 0x94);
        bVar1 = *(byte *)(param_3 + 0xc);
        *(byte *)(iVar3 + 0x16) = bVar1;
        if (bVar1 < 0xf) {
          uVar4 = 1;
        }
        else {
          uVar4 = 2;
        }
        *(undefined1 *)(iVar3 + 0x17) = uVar4;
        bVar1 = 1;
        *(char *)(param_2 + 99) = *(char *)(param_2 + 99) + '\x01';
        goto LAB_001e7a44;
      }
      if (2 < DebugLevel) {
        printk("%s: wpsIE AP not found\n","WscBssWpsIESearchForPIN");
      }
    }
    param_5 = param_5 + (-2 - (uint)*(byte *)((int)param_6 + 1));
    param_6 = (ushort *)((int)param_6 + *(byte *)((int)param_6 + 1) + 2);
    cVar12 = '\0';
  } while( true );
}

