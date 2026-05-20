// module: mt7915.ko
// function: WscBssWpsIESearchForPBC @ 0x1e73f0
// size: 1460 bytes
//

/* WARNING: Type propagation algorithm not settling */

bool WscBssWpsIESearchForPBC
               (int param_1,int param_2,int param_3,int param_4,int param_5,ushort *param_6)

{
  byte bVar1;
  int iVar2;
  undefined1 uVar3;
  ushort uVar4;
  uint uVar5;
  undefined1 *puVar6;
  undefined1 *puVar7;
  int iVar8;
  char cVar9;
  undefined1 *puVar10;
  char cVar11;
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
  __memzero(auStack_67,0x3f);
  bVar1 = *(byte *)(param_2 + 0x1c54);
  if (((0x2f < bVar1) && (uVar5 = bVar1 & 0xf, (bVar1 & 0xf) == 0 || uVar5 == 1)) &&
     (param_1 + uVar5 * 0x2137b0 != -0x36db58)) {
    HcGetBandByWdev();
  }
  cVar9 = '\0';
  iVar8 = 0;
  cVar11 = '\0';
LAB_001e7488:
  do {
    do {
      do {
        while( true ) {
          if (param_5 < 1 || cVar11 != '\0') {
            return cVar9 != '\0' && cVar11 != '\0';
          }
          if (((char)*param_6 == -0x23) && (iVar2 = memcmp(param_6 + 1,&WPS_OUI,4), iVar2 == 0))
          break;
          cVar11 = '\0';
          param_5 = param_5 + (-2 - (uint)*(byte *)((int)param_6 + 1));
          param_6 = (ushort *)((int)param_6 + *(byte *)((int)param_6 + 1) + 2);
        }
        param_5 = param_5 + -6;
        param_6 = param_6 + 3;
        cVar11 = '\0';
      } while (param_5 < 1);
      do {
        uVar4 = *param_6 << 8 | *param_6 >> 8;
        if (uVar4 == 0x1041) {
          hex_dump("SelReg:",param_6,5);
          cVar9 = (char)param_6[2];
          if (2 < DebugLevel) {
            printk("bSelReg = %d\n",cVar9);
            uVar4 = *param_6 << 8 | *param_6 >> 8;
            goto LAB_001e7534;
          }
          uVar4 = *param_6 << 8 | *param_6 >> 8;
          if (uVar4 == 0x1012) {
            uVar4 = param_6[2] << 8 | param_6[2] >> 8;
            goto LAB_001e7564;
          }
        }
        else {
LAB_001e7534:
          if (uVar4 == 0x1012) {
            uVar4 = param_6[2] << 8 | param_6[2] >> 8;
            if (2 < DebugLevel) {
              printk("WscPBCBssTableSort : DevicePasswordID = 0x%04x\n",uVar4);
            }
LAB_001e7564:
            if (*(int *)(param_2 + 4) == 2) {
              if (uVar4 == 4) goto LAB_001e7690;
            }
            else if (uVar4 == 6 && *(int *)(param_2 + 4) == 3) {
LAB_001e7690:
              if ((2 < DebugLevel) && (printk("DPID=PBC Found -->\n"), 2 < DebugLevel)) {
                printk("#  Bssid %02x:%02x:%02x:%02x:%02x:%02x\n",*(undefined1 *)(param_3 + 6),
                       *(undefined1 *)(param_3 + 7),*(undefined1 *)(param_3 + 8),
                       *(undefined1 *)(param_3 + 9),*(undefined1 *)(param_3 + 10),
                       *(undefined1 *)(param_3 + 0xb));
              }
              cVar11 = '\x01';
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
              uVar4 = *param_6 << 8 | *param_6 >> 8;
              goto joined_r0x001e74e8;
            }
            uVar4 = *param_6 << 8 | *param_6 >> 8;
          }
        }
joined_r0x001e74e8:
        if (uVar4 == 0x1047) {
          RTMPMoveMemory(auStack_67,param_6 + 2,0x10);
        }
        uVar5 = (param_6[1] & 0xff) << 8 | (uint)(param_6[1] >> 8);
        param_5 = param_5 + (-4 - uVar5);
        param_6 = (ushort *)((int)param_6 + uVar5 + 4);
      } while (0 < param_5);
    } while (cVar9 != '\x01' || cVar11 != '\x01');
    if (*(char *)(param_2 + 0x4c) == '\b') {
      return true;
    }
    if (*(char *)(param_2 + 0x4c) != '\0') {
      iVar8 = 0;
      iVar2 = param_4;
      do {
        FUN_001e06a0(iVar2,auStack_67,auStack_77,&local_78);
        iVar2 = iVar2 + 0x3f;
        if (local_78 != '\0') goto LAB_001e7660;
        uVar5 = (uint)*(byte *)(param_2 + 0x4c);
        iVar8 = iVar8 + 1;
      } while (iVar8 < (int)uVar5);
LAB_001e7720:
      puVar10 = (undefined1 *)(param_4 + (short)uVar5 * 0x3f);
      puVar6 = puVar10 + 0x18;
      RTMPMoveMemory(puVar10,auStack_67);
      RTMPMoveMemory(puVar10 + 0x10,param_3 + 6,6);
      RTMPZeroMemory(puVar6,0x20);
      RTMPMoveMemory(puVar6,param_3 + 0x95,*(undefined1 *)(param_3 + 0x94));
      iVar2 = DebugLevel;
      puVar10[0x38] = *(undefined1 *)(param_3 + 0x94);
      bVar1 = *(byte *)(param_3 + 0xc);
      puVar10[0x16] = bVar1;
      if (bVar1 < 0xf) {
        uVar3 = 1;
      }
      else {
        uVar3 = 2;
      }
      puVar10[0x17] = uVar3;
      puVar7 = puVar10;
      if (-1 < iVar2) {
        printk("UUID-E= ");
        iVar2 = DebugLevel;
      }
      do {
        if (-1 < iVar2) {
          printk("%02x  ",*puVar7);
          iVar2 = DebugLevel;
        }
        puVar7 = puVar7 + 1;
      } while (puVar7 != puVar10 + 0x10);
      if ((-1 < iVar2) && (printk(" SSID: %s, CH: %d ",puVar6,puVar10[0x16]), -1 < DebugLevel)) {
        printk(&_LC13);
      }
      cVar9 = '\x01';
      cVar11 = '\x01';
      *(char *)(param_2 + 0x4c) = *(char *)(param_2 + 0x4c) + '\x01';
      goto LAB_001e7488;
    }
    uVar5 = 0;
    if (local_78 == '\0') goto LAB_001e7720;
LAB_001e7660:
    if (*(char *)(param_2 + 0x2a59) == '\0') {
      if ((local_50 == '\x01') &&
         (iVar2 = param_4 + iVar8 * 0x3f, *(char *)(iVar2 + 0x17) != '\x01')) {
LAB_001e7808:
        RTMPMoveMemory(iVar2 + 0x10,auStack_57,6);
        RTMPZeroMemory(iVar2 + 0x18,0x20);
        RTMPMoveMemory(iVar2 + 0x18,auStack_4f,local_2f);
        *(undefined1 *)(iVar2 + 0x38) = local_2f;
        *(undefined1 *)(iVar2 + 0x16) = local_51;
        if (local_78 == '\0') {
          uVar5 = (uint)*(byte *)(param_2 + 0x4c);
          goto LAB_001e7720;
        }
      }
    }
    else if (((*(char *)(param_2 + 0x2a59) == '\x01') && (local_50 == '\x02')) &&
            (iVar2 = param_4 + iVar8 * 0x3f, *(char *)(iVar2 + 0x17) != '\x02')) goto LAB_001e7808;
    cVar9 = '\x01';
    cVar11 = cVar9;
  } while( true );
}

