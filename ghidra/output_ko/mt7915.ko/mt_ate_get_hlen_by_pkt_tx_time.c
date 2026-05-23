// module: mt7915.ko
// function: mt_ate_get_hlen_by_pkt_tx_time @ 0x285210
// size: 996 bytes
//

undefined2
mt_ate_get_hlen_by_pkt_tx_time
          (int param_1,int param_2,uint param_3,char *param_4,undefined1 *param_5,
          undefined1 *param_6)

{
  int iVar1;
  uint uVar2;
  undefined2 uVar3;
  int *unaff_r6;
  int unaff_r8;
  uint uVar4;
  bool bVar5;
  bool bVar6;
  
  iVar1 = net_ad_wrap_service();
  uVar4 = (uint)*(byte *)(param_2 * 0xd18 + iVar1 + 0x1135);
  if (param_3 < 0x17) {
    unaff_r8 = 0;
    uVar2 = uVar4 - 0xb & 0xff;
LAB_00285258:
    unaff_r6 = &DebugLevel;
    if (uVar2 < 2) {
      *param_6 = 1;
    }
  }
  else if (param_3 < 0x901) {
    uVar2 = uVar4 - 0xb & 0xff;
    bVar6 = 3 < uVar4;
    bVar5 = uVar4 != 4;
    if (bVar5) {
      bVar6 = uVar2 != 0;
    }
    if (bVar6 && (bVar5 && uVar2 != 1)) {
      unaff_r8 = 1;
      unaff_r6 = &DebugLevel;
    }
    if (!bVar6 || (!bVar5 || uVar2 == 1)) {
LAB_002852ec:
      unaff_r8 = 1;
      *param_4 = '\x01';
      goto LAB_00285258;
    }
  }
  else if (param_3 < 0x1001) {
    uVar2 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
    if ((uVar2 == 0x7915 ||
         (uVar2 == 0x6867 ||
         (uVar2 == 0x6632 || (uVar2 == 0x7663 || (uVar2 == 0x7622 || uVar2 == 0x7615))))) &&
       (uVar4 - 2 < 2)) {
      unaff_r8 = 1;
      unaff_r6 = &DebugLevel;
      *param_5 = 1;
      *param_4 = '\x01';
    }
    else {
      uVar2 = uVar4 - 0xb & 0xff;
      bVar6 = 3 < uVar4;
      if (uVar4 != 4) {
        bVar6 = uVar2 != 0;
      }
      if (!bVar6 || (uVar4 == 4 || uVar2 == 1)) goto LAB_002852ec;
LAB_00285384:
      unaff_r6 = &DebugLevel;
      if (DebugLevel < 0) {
        unaff_r8 = 1;
      }
      else {
        unaff_r8 = 1;
        printk("%s: Can\'t generate frame with such length for CCK/OFDM mode!!\n",
               "mt_ate_get_hlen_by_pkt_tx_time");
      }
    }
  }
  else {
    if (0x1a2c < param_3) {
      uVar2 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
      if ((uVar2 == 0x7915 ||
           (uVar2 == 0x6867 ||
           (uVar2 == 0x6632 || (uVar2 == 0x7663 || (uVar2 == 0x7622 || uVar2 == 0x7615))))) &&
         (1 < uVar4)) {
        unaff_r8 = 1;
        *param_6 = 1;
        uVar2 = uVar4 - 0xb & 0xff;
        *param_5 = 1;
        *param_4 = '\x01';
      }
      else if (DebugLevel < 0) {
        unaff_r8 = 1;
        uVar2 = uVar4 - 0xb & 0xff;
      }
      else {
        unaff_r8 = 1;
        printk("%s: Can\'t generate frame with such length for CCK/OFDM mode!!\n",
               "mt_ate_get_hlen_by_pkt_tx_time");
        uVar2 = uVar4 - 0xb & 0xff;
      }
      goto LAB_00285258;
    }
    uVar2 = uVar4 - 0xb & 0xff;
    bVar6 = 3 < uVar4;
    if (uVar4 != 4) {
      bVar6 = uVar2 != 0;
    }
    if (!bVar6 || (uVar4 == 4 || uVar2 == 1)) goto LAB_002852ec;
    uVar2 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
    if ((uVar2 != 0x7915 &&
         (uVar2 != 0x6867 &&
         (uVar2 != 0x6632 && (uVar2 != 0x7663 && (uVar2 != 0x7622 && uVar2 != 0x7615))))) ||
       (1 < uVar4 - 2)) goto LAB_00285384;
    unaff_r8 = 1;
    unaff_r6 = &DebugLevel;
    *param_6 = 1;
    *param_5 = 1;
    *param_4 = '\x01';
  }
  iVar1 = net_ad_wrap_service(param_1);
  uVar3 = *(undefined2 *)(param_2 * 0xd18 + iVar1 + 0x6d6);
  if (*unaff_r6 < 3) {
    if (unaff_r8 == 0) {
      return uVar3;
    }
    iVar1 = *unaff_r6;
    if (*param_4 != '\0') {
      return 0x1a;
    }
  }
  else {
    printk("%s: original header len=%d\n","mt_ate_get_hlen_by_pkt_tx_time",uVar3);
    iVar1 = DebugLevel;
    if (unaff_r8 == 0) goto LAB_002852b0;
    if (*param_4 != '\0') {
      uVar3 = 0x1a;
      goto LAB_002852b0;
    }
  }
  uVar3 = 0x18;
LAB_002852b0:
  if (2 < iVar1) {
    printk("%s: pkt_len=%d, need_qos/amsdu/ampdu/dataframe/hlen=%d/%d/%d/%d/%d\n",
           "mt_ate_get_hlen_by_pkt_tx_time",param_3,*param_4,*param_5,*param_6,unaff_r8,uVar3);
  }
  return uVar3;
}

