// module: mt7915.ko
// function: APKeyTableInit @ 0x1821c
// size: 784 bytes
//

undefined4 APKeyTableInit(int param_1,int param_2,int param_3)

{
  byte bVar1;
  ushort uVar2;
  undefined1 uVar3;
  size_t sVar4;
  uint uVar5;
  void *__src;
  int iVar6;
  int iVar7;
  
  if (param_2 == 0) {
    return 0;
  }
  bVar1 = *(byte *)(param_2 + 0xe);
  RTMPInitTimer(param_1,param_2 + 0x31c,rtmp_timer_GroupRekeyExec,param_1,1);
  if ((*(uint *)(param_2 + 0x2c) & 0x12cf8) != 0) {
    *(undefined1 *)(param_2 + 600) = 1;
  }
  uVar2 = *(ushort *)(param_3 + 2);
  *(undefined1 *)(param_2 + 0x888) = 2;
  __src = (void *)(param_2 + 0x21);
  *(undefined1 *)(param_1 + (uint)uVar2 * 0x620 + 0x2f762) = 2;
  os_zero_mem(param_3 + 0x14,0x88);
  *(undefined4 *)(param_3 + 0x14) = 2;
  *(ushort *)(param_3 + 0x20) = uVar2;
  *(undefined4 *)(param_3 + 0x18) = 0;
  *(undefined1 *)(param_3 + 0x22) = *(undefined1 *)(param_2 + 0xe);
  *(undefined4 *)(param_3 + 0x1c) = *(undefined4 *)(param_2 + 0x254);
  *(undefined1 *)(param_3 + 0x23) = *(undefined1 *)(param_2 + 600);
  os_move_mem((void *)(param_3 + 0x96),__src,6);
  if ((*(uint *)(param_2 + 0x254) & 0xe) != 0) {
    iVar7 = 0;
    do {
      bVar1 = *(byte *)(param_3 + 0x23);
      uVar3 = RandomByte(param_1);
      iVar6 = param_2 + (uint)bVar1 * 0x51 + iVar7;
      iVar7 = iVar7 + 1;
      *(undefined1 *)(iVar6 + 0x60) = uVar3;
    } while (iVar7 != 3);
    os_move_mem((void *)(param_3 + 0x24),
                (void *)(param_2 + (uint)*(byte *)(param_3 + 0x23) * 0x51 + 0x30),0x51);
    *(uint *)(param_3 + 0xc) = *(uint *)(param_3 + 0xc) | 0x1000;
    goto LAB_00018354;
  }
  if ((*(uint *)(param_2 + 0x254) & 0x1f0) == 0) goto LAB_00018354;
  sVar4 = strlen((char *)(param_2 + 0x179));
  iVar7 = (uint)bVar1 * 0x5834;
  SetWPAPSKKey(param_1,(char *)(param_2 + 0x179),sVar4,
               "Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n" +
               param_1 + iVar7 + 0x34,"pStaCfg->WpaPassPhrase"[param_1 + iVar7 + 5],param_2 + 0x1ba)
  ;
  GenRandom(param_1,__src,param_2 + 0x259);
  GenRandom(param_1,__src,param_2 + 0x39c);
  WpaDeriveGTK(param_2 + 0x259,param_2 + 0x39c,__src,(void *)(param_2 + 0x279),0x20);
  os_move_mem((void *)(param_3 + 0x24),(void *)(param_2 + 0x279),0x20);
  if (*(char *)(param_2 + 0x40c) == '\x01') {
    *(undefined1 *)(param_2 + 0x417) = 4;
    __memzero(param_2 + 0x458,6);
    PMF_DeriveIGTK(param_1,(void *)(param_2 + 0x418));
    os_move_mem((void *)(param_3 + 0x75),(void *)(param_2 + 0x418),0x20);
    uVar5 = *(uint *)(param_2 + 0x413);
    if ((uVar5 & 0xa00) == 0) {
      if ((uVar5 & 0x1400) == 0) {
        if (*(char *)(param_3 + 0x95) == '\0') goto LAB_00018478;
      }
      else {
        *(undefined1 *)(param_3 + 0x95) = 0x20;
        uVar5 = *(uint *)(param_2 + 0x413);
      }
    }
    else {
      *(undefined1 *)(param_3 + 0x95) = 0x10;
      uVar5 = *(uint *)(param_2 + 0x413);
    }
    *(uint *)(param_3 + 0x1c) = *(uint *)(param_3 + 0x1c) | uVar5;
  }
LAB_00018478:
  WPAInstallKey(param_1,param_3 + 0x14,1,0);
  *(uint *)(param_3 + 0xc) = *(uint *)(param_3 + 0xc) | 0x1000;
  *(undefined1 *)(param_2 + 0x3c5) = 1;
LAB_00018354:
  if (2 < DebugLevel) {
    printk("### BSS(%d) AKM=0x%x, PairwiseCipher=0x%x, GroupCipher=0x%x\n",
           *(undefined1 *)(param_2 + 0xe),*(undefined4 *)(param_2 + 0x2c),
           *(undefined4 *)(param_2 + 0x174),*(undefined4 *)(param_2 + 0x254));
  }
  return 1;
}

