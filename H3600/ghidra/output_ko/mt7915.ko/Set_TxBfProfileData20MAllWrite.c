// module: mt7915.ko
// function: Set_TxBfProfileData20MAllWrite @ 0xe82c0
// size: 1200 bytes
//

bool Set_TxBfProfileData20MAllWrite(int param_1,char *param_2)

{
  byte bVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  ushort uVar5;
  size_t sVar6;
  byte *__s;
  size_t sVar7;
  char cVar8;
  short sVar9;
  uint __n;
  char cVar10;
  int iVar11;
  ushort *puVar12;
  short sVar13;
  short sVar14;
  short sVar15;
  byte bVar16;
  bool bVar17;
  int iVar18;
  uint local_310;
  byte local_305;
  byte local_304 [12];
  ushort local_2f8 [362];
  
  bVar16 = "SetPartProfileParameters"[param_1 + 0x18];
  os_zero_mem(local_2f8,0x2d0);
  sVar6 = strlen(param_2);
  bVar16 = bVar16 >> 4;
  if (sVar6 != 0xb7 && sVar6 != 5) {
    if (-1 < DebugLevel) {
      printk("%s: False: Command inputs not meet the Command format Length!\n",
             "Set_TxBfProfileData20MAllWrite");
    }
    return false;
  }
  __s = (byte *)rstrtok(param_2,&_LC232);
  if (__s != (byte *)0x0) {
    if ((((&_ctype)[*__s] & 0x44) != 0) && (((&_ctype)[__s[1]] & 0x44) != 0)) {
      puVar12 = local_2f8;
      do {
        sVar7 = strlen((char *)__s);
        __n = sVar7 & 0xff;
        if ((sVar7 & 1) == 0) {
          if (__n == 2) {
            AtoH(__s,&local_305,1);
            *puVar12 = (ushort)local_305;
          }
          else {
            if (__n == 4) goto LAB_000e8400;
            if (-1 < DebugLevel) {
              printk("%s: Error: Un-expected Argument Length!\n","Set_TxBfProfileData20MAllWrite");
            }
          }
        }
        else {
          local_304[0] = 0x30;
          local_304[1] = 0;
          strncat((char *)local_304,(char *)__s,__n);
          __s = local_304;
LAB_000e8400:
          AtoH(__s,puVar12,2);
          *puVar12 = *puVar12 << 8 | *puVar12 >> 8;
        }
        __s = (byte *)rstrtok(0,&_LC232);
        if (__s == (byte *)0x0) goto LAB_000e8474;
      } while ((((&_ctype)[*__s] & 0x44) != 0) &&
              (puVar12 = puVar12 + 1, ((&_ctype)[__s[1]] & 0x44) != 0));
    }
    if (DebugLevel < 0) {
      return false;
    }
    printk("%s: False: Command input arguments aren\'t Hex format!\n",
           "Set_TxBfProfileData20MAllWrite");
    return false;
  }
LAB_000e8474:
  iVar18 = DebugLevel;
  if (sVar6 == 5) {
    if (local_2f8[1] == 0xf0) {
      *(undefined1 *)(param_1 + 0xa787cc) = 0;
      if (iVar18 < 3) {
        return true;
      }
      printk("%s: Status: Start to Input Profile Data!\n","Set_TxBfProfileData20MAllWrite");
      return true;
    }
    if (local_2f8[1] != 0xff) goto LAB_000e847c;
    local_310 = (uint)(byte)local_2f8[0];
    if (2 < DebugLevel) {
      bVar17 = true;
      printk("%s: Status: End to Input Profile Data!\n","Set_TxBfProfileData20MAllWrite");
      goto LAB_000e8480;
    }
    cVar8 = *(char *)(param_1 + 0x79504d);
    cVar10 = *(char *)(param_1 + 0xa3ae36);
    if (cVar8 == '\0') goto LAB_000e8650;
    bVar17 = true;
LAB_000e84ac:
    if (cVar10 == '\0') {
      bVar16 = "SetPartProfileParameters"[param_1 + 0x1a];
    }
    else {
      bVar16 = "rtmp_read_vow_parms_from_file"[param_1];
    }
  }
  else {
LAB_000e847c:
    bVar17 = false;
LAB_000e8480:
    cVar8 = *(char *)(param_1 + 0x79504d);
    cVar10 = *(char *)(param_1 + 0xa3ae36);
    if (cVar8 != '\0') goto LAB_000e84ac;
  }
  if (2 < DebugLevel) {
    printk("%s: Status: Config_DBDC_MODE=%d, control_band_idx=%d, \tdbdc_band0_tx_path=%d, dbdc_band1_tx_path=%d,  \tTx Path = %d!\n"
           ,"Set_TxBfProfileData20MAllWrite",cVar8,cVar10,"SetPartProfileParameters"[param_1 + 0x1a]
           ,"rtmp_read_vow_parms_from_file"[param_1],bVar16);
  }
  if (!bVar17) {
    puVar12 = local_2f8;
    iVar18 = 0;
    do {
      uVar2 = *puVar12;
      uVar3 = puVar12[1];
      uVar4 = puVar12[2];
      if (uVar2 < 0x20) {
        sVar13 = uVar2 + 0xe0;
      }
      else {
        sVar13 = uVar2 - 0x20;
      }
      uVar2 = puVar12[3];
      uVar5 = puVar12[4];
      if (bVar16 == 2) {
        sVar14 = uVar4 - uVar3;
        if (DebugLevel < 1) {
          sVar15 = 0;
          sVar9 = sVar15;
        }
        else {
          printk("%s:: SubCarrier ID=%d, angle_ph21 = %x, angle_ph11 = %x, phi11 = %x\n",
                 "Set_TxBfProfileData20MAllWrite",sVar13,uVar4,uVar3,(int)sVar14);
          sVar15 = 0;
          sVar9 = sVar15;
        }
      }
      else if (bVar16 == 3) {
        sVar14 = uVar2 - uVar3;
        sVar15 = uVar2 - uVar4;
        if (DebugLevel < 1) {
          sVar9 = 0;
        }
        else {
          printk("%s:: SubCarrier ID=%d, angle_ph31 = %x, angle_ph21 = %x, angle_ph11 = %x, phi11 = %x, phi21 = %x\n"
                 ,"Set_TxBfProfileData20MAllWrite",sVar13,uVar2,uVar4,uVar3,(int)sVar14,(int)sVar15)
          ;
          sVar9 = 0;
        }
      }
      else if (*(char *)(param_1 + 0x79504d) == '\0') {
        sVar14 = uVar5 - uVar3;
        sVar15 = uVar5 - uVar4;
        sVar9 = uVar5 - uVar2;
      }
      else {
        sVar14 = uVar4 - uVar3;
        sVar15 = 0;
        sVar9 = sVar15;
      }
      puVar12 = puVar12 + 5;
      bVar1 = *(byte *)(param_1 + 0xa787cc);
      iVar11 = iVar18 + (uint)bVar1;
      iVar18 = iVar18 + 1;
      iVar11 = param_1 + iVar11 * 8;
      *(short *)(iVar11 + 0xa787ce) = sVar13;
      *(short *)(iVar11 + 0xa787d0) = sVar14;
      *(short *)(iVar11 + 0xa787d2) = sVar15;
      *(short *)(iVar11 + 0xa787d4) = sVar9;
    } while (iVar18 != 8);
    *(byte *)(param_1 + 0xa787cc) = bVar1 + 8;
    return true;
  }
LAB_000e8650:
  iVar18 = CmdETxBfPfmuProfileDataWrite20MAll(param_1,local_310,param_1 + 0xa787ce);
  if (-1 < DebugLevel) {
    printk("%s: Status: Cmd Send to FW!\n","Set_TxBfProfileData20MAllWrite");
    return iVar18 == 0;
  }
  return iVar18 == 0;
}

