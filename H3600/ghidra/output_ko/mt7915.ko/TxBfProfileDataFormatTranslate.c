// module: mt7915.ko
// function: TxBfProfileDataFormatTranslate @ 0x87dc4
// size: 448 bytes
//

undefined4 TxBfProfileDataFormatTranslate(int param_1,uint *param_2,short *param_3)

{
  char cVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  ushort uVar5;
  byte bVar6;
  int iVar7;
  uint uVar8;
  short sVar9;
  byte bVar10;
  uint *puVar11;
  short sVar12;
  short sVar13;
  short sVar14;
  
  iVar7 = net_ad_wrap_service();
  bVar10 = (byte)"SetPartProfileParameters"[param_1 + 0x18] >> 4;
  cVar1 = *(char *)(iVar7 + 0x4cc);
  if (DebugLevel < 1) {
    if (*(char *)(param_1 + 0x79504d) == '\0') goto LAB_00087e2c;
LAB_00087e18:
    if (cVar1 == '\0') {
      bVar10 = "SetPartProfileParameters"[param_1 + 0x1a];
    }
    else {
      bVar10 = "rtmp_read_vow_parms_from_file"[param_1];
    }
  }
  else {
    printk("%s :: Band index = %d\n","TxBfProfileDataFormatTranslate",cVar1);
    if (*(char *)(param_1 + 0x79504d) != '\0') goto LAB_00087e18;
  }
  if (0 < DebugLevel) {
    printk("%s :: Tx num = %d\n","TxBfProfileDataFormatTranslate",bVar10);
  }
LAB_00087e2c:
  puVar11 = param_2 + 0x140;
  do {
    uVar8 = *param_2;
    uVar8 = uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 |
            uVar8 >> 0x18;
    sVar14 = (short)uVar8;
    if (uVar8 < 0x20) {
      sVar14 = sVar14 + 0xe0;
    }
    else {
      sVar14 = sVar14 + -0x20;
    }
    uVar3 = (ushort)((param_2[1] >> 0x10 & 0xff) << 8) | (ushort)(byte)(param_2[1] >> 0x18);
    uVar2 = (ushort)((param_2[2] >> 0x10 & 0xff) << 8) | (ushort)(byte)(param_2[2] >> 0x18);
    uVar5 = (ushort)((param_2[3] >> 0x10 & 0xff) << 8);
    bVar6 = (byte)(param_2[3] >> 0x18);
    if (bVar10 == 2) {
LAB_00087ef4:
      sVar9 = uVar2 - uVar3;
      sVar12 = 0;
      sVar13 = sVar12;
    }
    else if (bVar10 == 3) {
      uVar5 = uVar5 | bVar6;
      sVar13 = 0;
      sVar9 = uVar5 - uVar3;
      sVar12 = uVar5 - uVar2;
    }
    else {
      if (*(char *)(param_1 + 0x79504d) != '\0') goto LAB_00087ef4;
      uVar4 = (ushort)((param_2[4] >> 0x10 & 0xff) << 8) | (ushort)(byte)(param_2[4] >> 0x18);
      sVar9 = uVar4 - uVar3;
      sVar12 = uVar4 - uVar2;
      sVar13 = uVar4 - (uVar5 | bVar6);
    }
    param_2 = param_2 + 5;
    *param_3 = sVar14;
    param_3[1] = sVar9;
    param_3[2] = sVar12;
    param_3[3] = sVar13;
    param_3 = param_3 + 4;
    if (param_2 == puVar11) {
      return 1;
    }
  } while( true );
}

