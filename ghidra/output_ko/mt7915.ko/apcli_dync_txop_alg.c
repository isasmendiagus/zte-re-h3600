// module: mt7915.ko
// function: apcli_dync_txop_alg @ 0x6acdc
// size: 840 bytes
//

void apcli_dync_txop_alg(int param_1,int param_2,uint param_3,int param_4)

{
  short sVar1;
  short sVar2;
  char *pcVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  char cVar7;
  uint uVar8;
  uint uVar9;
  short sVar10;
  uint uVar11;
  char local_2d [9];
  
  sVar2 = txopfe;
  sVar10 = txop80;
  if (param_2 == 0 || param_1 == 0) {
    if (-1 < DebugLevel) {
      printk("%s:: pAd or wdev is NULL!\n","apcli_dync_txop_alg");
      return;
    }
    return;
  }
  sVar1 = *(short *)(param_2 + 0x9c2);
  local_2d[0] = '\0';
  local_2d[1] = 0;
  local_2d[2] = '\0';
  local_2d[3] = 0;
  local_2d[4] = 0;
  uVar9 = (uint)*(byte *)(param_2 + 0xe);
  if (sVar1 == 0x30) {
    iVar6 = uVar9 * 0x20;
    if ((byte)(&DAT_00580edd)[param_1 + uVar9 * 0x2137b0] < 4) {
      if (param_3 < 0x30d) {
        uVar11 = 0x30c;
        local_2d[3] = 1;
        uVar8 = 0xfa;
      }
      else {
        uVar11 = 0x30c;
        uVar8 = 0xfa;
      }
    }
    else {
      uVar11 = (short)(ushort)(byte)(&DAT_00580edd)[param_1 + uVar9 * 0x2137b0] * 10 + 0x32;
      uVar8 = 0xfa;
      if (0x95 < uVar11) {
        uVar11 = 0x96;
      }
      uVar11 = 0x33e - uVar11 & 0xffff;
    }
  }
  else if (txopfe == sVar1) {
    iVar6 = uVar9 << 5;
    uVar11 = 0x33e;
    uVar8 = 200;
  }
  else {
    iVar6 = uVar9 << 5;
    uVar11 = 0x33e;
    uVar8 = 0xfa;
  }
  if (uVar11 < param_3) {
    local_2d[1] = 1;
    uVar8 = (uint)(byte)(&DAT_00580edf)[param_1 + (iVar6 * 4 + uVar9 * 5) * 0x3ff0];
    if (uVar8 != 0) goto LAB_0006ae90;
    cVar7 = '\0';
    sVar10 = 0x30;
  }
  else {
    if (((uVar8 < param_3) && ((*(ushort *)(param_2 + 0x18) & 0x4e) != 0)) &&
       (uVar8 = __aeabi_uidiv(param_3 * 100,param_3 + param_4), 0x46 < uVar8)) {
      local_2d[2] = '\x01';
      uVar8 = (uint)(byte)(&DAT_00580edf)[param_1 + (iVar6 * 4 + uVar9 * 5) * 0x3ff0];
      if (uVar8 == 0) {
LAB_0006afe4:
        cVar7 = '\0';
        sVar10 = sVar2;
        goto LAB_0006adb8;
      }
    }
    else {
      uVar8 = (uint)(byte)(&DAT_00580edf)[param_1 + (iVar6 * 4 + uVar9 * 5) * 0x3ff0];
      if (uVar8 == 0) {
        cVar7 = '\0';
        if (local_2d[2] != '\x01') {
          if (sVar1 != txop0) {
            disable_tx_burst(param_1,param_2,2,7,txop0);
          }
          goto LAB_0006add8;
        }
        goto LAB_0006afe4;
      }
    }
LAB_0006ae90:
    local_2d[3] = 1;
    cVar7 = local_2d[0];
    if (param_3 < 0x33e) {
      local_2d[4] = 1;
      iVar4 = param_1 + (iVar6 * 4 + uVar9 * 5) * 0x3ff0;
      uVar8 = uVar8 + (1 << (&DAT_00580ee0)[iVar4] & 0xffU);
      if (0xef < uVar8) {
        uVar8 = 0xf0;
      }
      (&DAT_00580edf)[iVar4] = (char)uVar8;
    }
  }
LAB_0006adb8:
  if (sVar10 != sVar1) {
    enable_tx_burst(param_1,param_2,2,7,sVar10);
  }
LAB_0006add8:
  pcVar3 = local_2d;
  pcVar5 = &DAT_00580edc + param_1 + (iVar6 * 4 + uVar9 * 5) * 0x3ff0;
  while( true ) {
    if (cVar7 == '\x01') {
      *pcVar5 = *pcVar5 + '\x01';
    }
    else {
      *pcVar5 = '\0';
    }
    pcVar5 = pcVar5 + 1;
    if (pcVar3 == local_2d + 4) break;
    pcVar3 = pcVar3 + 1;
    cVar7 = *pcVar3;
  }
  param_1 = param_1 + (iVar6 * 4 + uVar9 * 5) * 0x3ff0;
  if (0xf0 < (byte)(&DAT_00580edf)[param_1]) {
    (&DAT_00580edf)[param_1] = 0;
  }
  return;
}

