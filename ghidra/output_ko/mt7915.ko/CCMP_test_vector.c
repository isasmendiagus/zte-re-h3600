// module: mt7915.ko
// function: CCMP_test_vector @ 0xb7360
// size: 1328 bytes
//

void CCMP_test_vector(void)

{
  int iVar1;
  int iVar2;
  int local_11c;
  undefined4 local_115;
  undefined2 local_111;
  undefined4 local_10f;
  undefined4 local_10b;
  undefined4 local_107;
  undefined4 local_103;
  undefined4 local_ff;
  undefined1 local_fb;
  undefined4 local_fa;
  undefined4 local_f6;
  undefined4 local_f2;
  undefined4 local_ee;
  undefined4 local_ea;
  undefined4 local_e6;
  undefined4 local_e2;
  undefined4 local_de;
  undefined4 local_da;
  undefined4 local_d6;
  undefined4 local_d2;
  undefined4 local_ce;
  undefined4 local_ca;
  undefined4 local_c6;
  undefined2 local_c2;
  undefined4 local_c0;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined4 local_b0;
  undefined4 uStack_ac;
  undefined4 local_a8;
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined4 local_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 local_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 local_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  
  local_c0 = 0x2cc34808;
  local_115 = 0x9776e70c;
  local_d6 = 0xd20f4008;
  uStack_bc = 0x28e1d20f;
  uStack_b8 = 0x30507ca5;
  uStack_b4 = 0x84484f1;
  local_111 = 0xb503;
  local_b0 = 0xb8a5aeab;
  uStack_ac = 0x3380bafc;
  local_d2 = 0x7ca528e1;
  local_ce = 0x84f13050;
  local_ca = 0xaeab0844;
  local_f6 = 0x851137ce;
  local_fa = 0x671f7cc9;
  local_ee = 0x2fd5bdf2;
  local_c6 = 0xbafcb8a5;
  local_f2 = 0x198a4a51;
  local_a8 = 0xfea2d0f3;
  local_10f = 0x2000e70c;
  local_ea = 0x551abaf8;
  uStack_a4 = 0x23bf3d9a;
  local_10b = 0xb5039776;
  uStack_9c = 0xce84632;
  uStack_a0 = 0xe443a642;
  local_107 = 0xf1305000;
  local_c2 = 0;
  local_e6 = 0xae852fd0;
  local_e2 = 0x2fb67b96;
  local_da = 0x50a0787e;
  local_de = 0xeba8cdb6;
  local_103 = 0xb5084484;
  local_fb = 0xc;
  local_ff = 0xe7769703;
  local_98 = 0x19d0043c;
  uStack_94 = 0xbce4578;
  uStack_90 = 0x2376f916;
  local_11c = 0;
  if (-1 < DebugLevel) {
    printk("== CCMP test vector ==\n");
  }
  __memzero(&local_8c,100);
  local_11c = 0;
  RTMPConstructCCMPAAD(&local_c0,1,0,0,&local_8c,&local_11c);
  iVar1 = local_11c;
  if ((local_11c == 0x16) && (iVar2 = memcmp(&local_8c,&local_d6,0x16), iVar2 == 0)) {
    if (-1 < DebugLevel) {
      printk("Construct AAD is OK!!!\n");
    }
  }
  else {
    if (-1 < DebugLevel) {
      printk("\n!!!Construct AAD is FAILURE!!!\n\n");
      iVar1 = local_11c;
    }
    hex_dump("Calculate AAD",&local_8c,iVar1);
  }
  __memzero(&local_8c,100);
  local_11c = 0;
  RTMPConstructCCMPNonce(&local_c0,0,0,0,&local_115,&local_8c,&local_11c);
  iVar1 = local_11c;
  if ((local_11c == 0xd) && (iVar2 = memcmp(&local_8c,&local_107,0xd), iVar2 == 0)) {
    if (-1 < DebugLevel) {
      printk("Construct NONCE is OK!!!\n");
    }
  }
  else {
    if (-1 < DebugLevel) {
      printk("\n!!!Construct NONCE is FAILURE!!!\n\n");
      iVar1 = local_11c;
    }
    hex_dump("Calculate NONCE",&local_8c,iVar1);
  }
  __memzero(&local_8c,100);
  local_11c = 0;
  RTMPConstructCCMPHdr(0,&local_115,&local_8c);
  iVar1 = memcmp(&local_8c,&local_10f,8);
  if (iVar1 == 0) {
    if (-1 < DebugLevel) {
      printk("Construct CCMP_HDR is OK!!!\n");
    }
  }
  else {
    if (-1 < DebugLevel) {
      printk("\n!!!Construct CCMP_HDR is FAILURE!!!\n\n");
    }
    hex_dump("Calculate CCMP_HDR",&local_8c,8);
  }
  __memzero(&local_8c,100);
  local_8c = local_ea;
  uStack_88 = local_e6;
  uStack_84 = local_e2;
  uStack_80 = local_de;
  local_7c = local_da;
  local_11c = 0x1c;
  iVar2 = AES_CCM_Encrypt(&local_8c,0x14,&local_fa,0x10,&local_107,0xd,&local_d6,0x16,8,&local_8c,
                          &local_11c);
  iVar1 = local_11c;
  if (iVar2 == 0) {
    if ((local_11c == 0x1c) && (iVar2 = memcmp(&local_8c,&local_a8,0x1c), iVar2 == 0)) {
      if (-1 < DebugLevel) {
        printk("CCM_Encrypt is OK!!!\n");
      }
    }
    else {
      if (-1 < DebugLevel) {
        printk("\n!!!CCM_Encrypt is FAILURE!!!\n\n");
        iVar1 = local_11c;
      }
      hex_dump("CCM_Encrypt",&local_8c,iVar1);
    }
  }
  __memzero(&local_8c,100);
  local_8c = local_a8;
  uStack_88 = uStack_a4;
  uStack_84 = uStack_a0;
  uStack_80 = uStack_9c;
  local_11c = 0x14;
  local_7c = local_98;
  uStack_78 = uStack_94;
  uStack_74 = uStack_90;
  iVar2 = AES_CCM_Decrypt(&local_8c,0x1c,&local_fa,0x10,&local_107,0xd,&local_d6,0x16,8,&local_8c,
                          &local_11c);
  iVar1 = local_11c;
  if (iVar2 == 0) {
    if ((local_11c == 0x14) && (iVar2 = memcmp(&local_8c,&local_ea,0x14), iVar2 == 0)) {
      if (DebugLevel < 0) {
        return;
      }
      printk("CCM_Decrypt is OK!!!\n");
    }
    else {
      if (-1 < DebugLevel) {
        printk("\n!!!CCM_Decrypt is FAILURE!!!\n\n");
        iVar1 = local_11c;
      }
      hex_dump("CCM_Decrypt",&local_8c,iVar1);
    }
  }
  if (-1 < DebugLevel) {
    printk("== CCMP test vector ==\n");
  }
  return;
}

