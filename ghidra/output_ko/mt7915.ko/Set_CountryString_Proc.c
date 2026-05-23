// module: mt7915.ko
// function: Set_CountryString_Proc @ 0x2b82c
// size: 776 bytes
//

undefined4 Set_CountryString_Proc(int param_1,char *param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  size_t __n;
  int iVar4;
  byte bVar5;
  uint uVar6;
  undefined1 *puVar7;
  void *__dest;
  byte *pbVar8;
  int iVar9;
  bool bVar10;
  char local_50 [44];
  
  uVar6 = 0;
  local_50[0] = '\0';
  local_50[1] = '\0';
  local_50[2] = '\0';
  local_50[3] = '\0';
  local_50[4] = '\0';
  local_50[5] = '\0';
  local_50[6] = '\0';
  local_50[7] = '\0';
  local_50[8] = '\0';
  local_50[9] = '\0';
  local_50[10] = '\0';
  local_50[0xb] = '\0';
  local_50[0xc] = '\0';
  local_50[0xd] = '\0';
  local_50[0xe] = '\0';
  local_50[0xf] = '\0';
  local_50[0x10] = '\0';
  local_50[0x11] = '\0';
  local_50[0x12] = '\0';
  local_50[0x13] = '\0';
  local_50[0x14] = '\0';
  local_50[0x15] = '\0';
  local_50[0x16] = '\0';
  local_50[0x17] = '\0';
  local_50[0x18] = '\0';
  local_50[0x19] = '\0';
  local_50[0x1a] = '\0';
  local_50[0x1b] = '\0';
  local_50[0x1c] = '\0';
  local_50[0x1d] = '\0';
  local_50[0x1e] = '\0';
  local_50[0x1f] = '\0';
  local_50[0x20] = '\0';
  local_50[0x21] = '\0';
  local_50[0x22] = '\0';
  local_50[0x23] = '\0';
  local_50[0x24] = '\0';
  local_50[0x25] = '\0';
  local_50[0x26] = '\0';
  local_50[0x27] = '\0';
  iVar1 = HcIsRfSupport(param_1,2);
  iVar2 = HcIsRfSupport(param_1,1);
  uVar3 = strlen(param_2);
  if (uVar3 < 0x27) {
    if (uVar3 < 4) {
      if (DebugLevel < 0) {
        return 0;
      }
      printk("Set_CountryString_Proc::Parameter of CountryString are too short !\n");
      return 0;
    }
    pbVar8 = (byte *)(param_2 + -1);
    while (bVar10 = uVar6 < uVar3, uVar6 = uVar6 + 1, bVar10) {
      pbVar8 = pbVar8 + 1;
      bVar5 = *pbVar8;
      if (bVar5 - 0x61 < 0x1a) {
        if (((&_ctype)[bVar5] & 2) != 0) {
          bVar5 = bVar5 - 0x20;
        }
        *pbVar8 = bVar5;
      }
      uVar3 = strlen(param_2);
    }
    iVar9 = 0;
    puVar7 = allCountry;
    do {
      __memzero(local_50,0x28);
      snprintf(local_50,0x28,"\"%s\"",*(undefined4 *)(puVar7 + 8));
      __n = strlen(param_2);
      iVar4 = strncmp(*(char **)(puVar7 + 8),param_2,__n);
      if ((iVar4 == 0) || (iVar4 = strncmp(local_50,param_2,__n), iVar4 == 0)) {
        if (*(char *)(param_1 + 0x794c44) < '\0') {
          if (DebugLevel < 0) {
            return 0;
          }
          printk("Set_CountryString_Proc::parameter of CountryRegion in eeprom is programmed\n");
          break;
        }
        if (iVar2 == 0) {
LAB_0002b9b8:
          if (iVar1 == 0) break;
          iVar2 = iVar9 << 4;
          bVar10 = false;
        }
        else {
          iVar2 = iVar9 * 0x10;
          if (allCountry[iVar2 + 0xe] != '\x01') {
            if (2 < DebugLevel) {
              printk("The Country are not Support G Band Channel\n");
            }
            goto LAB_0002b9b8;
          }
          *(undefined1 *)(param_1 + 0x794c44) = allCountry[iVar2 + 0xf];
          bVar10 = true;
          if (iVar1 == 0) goto LAB_0002b9ec;
        }
        if (allCountry[iVar2 + 0xc] == '\x01') {
          *(undefined1 *)(param_1 + 0x794c45) = allCountry[iVar2 + 0xd];
        }
        else {
          if (2 < DebugLevel) {
            printk("The Country are not Support A Band Channel\n");
          }
          if (!bVar10) break;
        }
LAB_0002b9ec:
        __dest = (void *)(param_1 + 0x794c31);
        os_zero_mem(__dest,4);
        os_move_mem(__dest,allCountry + iVar2 + 2,2);
        iVar1 = DebugLevel;
        *(undefined1 *)(param_1 + 0x794c30) = 1;
        *(undefined1 *)(param_1 + 0x794c33) = 0x20;
        if (iVar1 < 3) {
          return 1;
        }
        printk("Set_CountryString_Proc::(CountryString=%s CountryRegin=%d CountryCode=%s)\n",
               *(undefined4 *)(allCountry + iVar2 + 8),*(undefined1 *)(param_1 + 0x794c44),__dest);
        return 1;
      }
      iVar9 = iVar9 + 1;
      puVar7 = puVar7 + 0x10;
    } while (iVar9 != 0x66);
  }
  if (-1 < DebugLevel) {
    printk("Set_CountryString_Proc::Parameters out of range\n");
  }
  return 0;
}

