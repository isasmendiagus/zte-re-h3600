// module: mt7915.ko
// function: WPAConstructEapolMsg @ 0x11d364
// size: 1268 bytes
//

void WPAConstructEapolMsg
               (undefined4 param_1,uint param_2,uint *param_3,int param_4,undefined1 *param_5)

{
  byte bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined *puVar7;
  byte bVar8;
  bool bVar9;
  
  bVar9 = (*param_3 & 0x18) == 0;
  if (bVar9) {
    param_5[2] = 0;
    *param_5 = 1;
    param_5[1] = 3;
    param_5[3] = 0x5f;
    param_5[4] = 2;
  }
  else {
    param_5[2] = 0;
    *param_5 = 1;
    param_5[1] = 3;
    param_5[3] = 0x5f;
    param_5[4] = 0xfe;
  }
  bVar4 = !bVar9 && 4 < param_2;
  if ((*param_3 & 0x12000) == 0) {
    bVar8 = 0;
    if ((char)param_3[0xa1] != '\x02') {
      if ((char)param_3[0xa1] == '\x01' || (*param_3 & 0xef00) != 0) {
        bVar8 = 3;
      }
      else if ((param_3[0x52] & 0x10) == 0) {
        bVar8 = 2;
      }
      else {
        bVar8 = 1;
      }
    }
  }
  else {
    bVar8 = 0;
  }
  bVar1 = param_5[6];
  param_5[6] = bVar1 & 0xf8 | bVar8;
  if (param_2 < 5) {
    param_5[6] = param_5[6] | 8;
    if (param_2 != 3) goto LAB_0011d464;
    bVar2 = false;
    bVar3 = true;
    param_5[6] = param_5[6] | 0xc0;
LAB_0011d48c:
    param_5[5] = param_5[5] | 1;
  }
  else {
    param_5[6] = bVar1 & 0xf0 | bVar8;
    if (bVar4) {
      param_5[6] = param_5[6] & 0xcf | (*(byte *)(param_4 + 0x22c) & 3) << 4;
    }
LAB_0011d464:
    bVar2 = param_2 == 5;
    bVar3 = (param_2 & 0xfd) == 1;
    if (!bVar3 && !bVar2) {
      bVar3 = false;
      bVar2 = false;
      goto LAB_0011d48c;
    }
    param_5[6] = param_5[6] | 0x80;
    if (param_2 != 1) goto LAB_0011d48c;
  }
  if (((*param_3 & 0x30000) != 0) || ((char)param_3[0xa1] == '\x02')) {
    param_5[3] = 0x67;
  }
  if ((bVar9 && 2 < param_2) || (bVar4)) {
    param_5[5] = param_5[5] | 2;
    if (bVar9) goto LAB_0011d4cc;
LAB_0011d5bc:
    if (param_2 < 5) {
      uVar6 = param_3[0x52];
      if ((uVar6 & 0x10) != 0) goto LAB_0011d694;
LAB_0011d5d0:
      if ((uVar6 & 0x20) == 0) {
        if ((uVar6 & 0x40) != 0) goto LAB_0011d694;
        if ((uVar6 & 0x80) != 0) goto LAB_0011d5e8;
        if ((uVar6 & 0x100) != 0) goto LAB_0011d694;
      }
      else {
LAB_0011d5e8:
        param_5[8] = 0x10;
      }
    }
    else {
      uVar6 = *(uint *)(param_4 + 0x228);
      if ((uVar6 & 0x10) == 0) goto LAB_0011d5d0;
LAB_0011d694:
      param_5[8] = 0x20;
    }
    memmove(param_5 + 9,param_3 + 0xe4,8);
    if (bVar3) {
      memmove(param_5 + 0x11,param_3 + 0xcc,0x20);
      goto LAB_0011d50c;
    }
  }
  else {
    if (!bVar9) goto LAB_0011d5bc;
LAB_0011d4cc:
    if (bVar2 || param_2 == 3) {
      param_5[5] = param_5[5] | 0x10;
    }
    if (bVar3) {
      uVar6 = param_3[0x52];
      if ((uVar6 & 0x10) == 0) {
        if ((uVar6 & 0x20) == 0) {
          if ((uVar6 & 0x40) != 0) goto LAB_0011d6dc;
          if ((uVar6 & 0x80) != 0) goto LAB_0011d7b0;
          if ((uVar6 & 0x100) != 0) goto LAB_0011d6dc;
        }
        else {
LAB_0011d7b0:
          param_5[8] = 0x10;
        }
      }
      else {
LAB_0011d6dc:
        param_5[8] = 0x20;
      }
      memmove(param_5 + 9,param_3 + 0xe4,8);
      memmove(param_5 + 0x11,param_3 + 0xcc,0x20);
      goto LAB_0011d50c;
    }
    memmove(param_5 + 9,param_3 + 0xe4,8);
  }
  if (param_2 == 2) {
    memmove(param_5 + 0x11,param_3 + 0xd4,0x20);
  }
  else if ((bool)(bVar2 & !bVar9)) {
    memmove(param_5 + 0x11,(void *)(param_4 + 0x370),0x20);
    memmove(param_5 + 0x31,(void *)(param_4 + 0x380),0x10);
    param_5[0x40] = param_5[0x40] + '\x02';
  }
LAB_0011d50c:
  if (bVar2 || bVar9 && param_2 == 3) {
    memmove(param_5 + 0x41,(void *)(param_4 + 0x39b),6);
  }
  if (((*param_3 & 0x30000) == 0) && ((char)param_3[0xa1] != '\x02')) {
    __memzero(param_5 + 0x51,0x10);
  }
  else {
    __memzero(param_5 + 0x51,0x18);
  }
  WPAConstructEapolKeyData(param_1,param_2,bVar8,param_3,param_4,param_5);
  if (param_2 != 1) {
    WPACalculateMIC(bVar8,*param_3,(int)param_3 + 0x1ce,(char)param_3[0xa1],param_5);
  }
  if (3 < DebugLevel) {
    puVar7 = &_LC99;
    if (!bVar9) {
      puVar7 = &_LC100;
    }
    uVar5 = GetEapolMsgType((int)(char)param_2);
    printk("===> %s for %s %s\n",puVar7,"WPAConstructEapolMsg",uVar5);
    if ((3 < DebugLevel) &&
       (printk("\t     Body length = %d\n",CONCAT11(param_5[2],param_5[3])), 3 < DebugLevel)) {
      printk("\t     Key length  = %d\n",CONCAT11(param_5[7],param_5[8]));
      return;
    }
  }
  return;
}

