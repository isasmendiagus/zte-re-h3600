// module: mt7915.ko
// function: MlmeCalculateChannelQuality @ 0x12fd2c
// size: 864 bytes
//

void MlmeCalculateChannelQuality(int param_1,int *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  bool bVar11;
  int local_30;
  
  if ((param_2 == (int *)0x0) || (iVar1 = GetStaCfgByWdev(param_1,param_2[2]), iVar1 == 0)) {
    printk(&_LC14,0xbe5);
    dump_stack();
    return;
  }
  iVar5 = *(int *)(iVar1 + 0x212458);
  if ((*param_2 == 2) && (*(byte *)(iVar1 + 0xe) < 2)) {
    local_30 = *(int *)(iVar1 + 0x213340);
  }
  else {
    local_30 = *(int *)(iVar1 + 0x21245c);
  }
  iVar10 = *(int *)(param_1 + 0xa39e18);
  iVar8 = *(int *)(param_1 + 0xa39e14);
  iVar2 = RTMPMaxRssi(param_1,(int)(char)param_2[0x42],(int)*(char *)((int)param_2 + 0x109),
                      (int)*(char *)((int)param_2 + 0x10a));
  uVar9 = param_2[0x31a];
  iVar6 = param_2[0x31b];
  uVar3 = uVar9 + iVar6 + param_2[0x31c];
  if (uVar3 < 5) {
    iVar7 = 0;
  }
  else {
    iVar7 = __aeabi_uidiv((uVar3 - uVar9) * 100);
  }
  if ((uint)(iVar8 + iVar10) < 5) {
    iVar8 = 0;
  }
  else {
    iVar8 = __aeabi_uidiv(iVar8 * 100);
  }
  iVar10 = DebugLevel;
  if ((*(uint *)(iVar1 + 0x212464) & 1) == 0) goto LAB_0012fe6c;
  if ((*(char *)(iVar1 + 0x2124ba) != '\0') && (*(char *)(iVar1 + 0x2124c0) != '\0')) {
    uVar3 = 0;
    *(undefined4 *)(iVar1 + 0x212460) = 0;
    if (DebugLevel < 4) {
      cVar4 = *(char *)(param_1 + 0x286285);
    }
    else {
      printk("%s::STA/APCLI BEACON lost meet\n","MlmeCalculateChannelQuality");
      cVar4 = *(char *)(param_1 + 0x286285);
    }
    goto LAB_0012fec0;
  }
  if (*(char *)(param_1 + 0x286285) == '\0') {
    bVar11 = uVar9 == 1;
    if (uVar9 < 2) {
      bVar11 = *(short *)(iVar1 + 0x2124b8) == 0;
    }
    if ((!bVar11) || (-1 < (local_30 + iVar5) - param_3)) goto LAB_0012fe6c;
    if ((1 < *(byte *)((int)param_2 + 0x1429)) && (param_2[0x50b] != 0)) {
      *(int *)(iVar1 + 0x21245c) = param_3;
      if (iVar10 < 3) {
        cVar4 = *(char *)(param_1 + 0x286285);
        uVar3 = 0x5a;
      }
      else {
        uVar3 = 0x5a;
        printk("Tx success cnt increasing, update LastBeaconRxTime to %ld\n",local_30);
        cVar4 = *(char *)(param_1 + 0x286285);
      }
      goto LAB_0012fec0;
    }
    if (2 < DebugLevel) {
      uVar3 = 0;
      printk("BEACON lost > %ld msec with TxOkCnt=%ld -> CQI=0\n",iVar5 * 10,uVar9 + iVar6);
      cVar4 = *(char *)(param_1 + 0x286285);
      goto LAB_0012fec0;
    }
    uVar3 = 0;
  }
  else {
LAB_0012fe6c:
    if (iVar2 < -0x27) {
      if (iVar2 < -0x5a) {
        iVar5 = 0;
      }
      else {
        iVar5 = ((iVar2 + 0x5a) * 2 & 0xfeU) * 0x32;
      }
    }
    else {
      iVar5 = 5000;
    }
    uVar3 = (uint)(iVar7 * -0x1e + 5000 + iVar8 * -0x14 + iVar5) / 100;
    if (3 < DebugLevel) {
      printk("%s(line:%d), ChannelQuality(%lu)\n","MlmeCalculateChannelQuality",0xc72,uVar3);
    }
    cVar4 = *(char *)(param_1 + 0x286285);
LAB_0012fec0:
    if (cVar4 != '\0') goto LAB_0012fec8;
  }
  uVar9 = uVar3;
  if (99 < uVar3) {
    uVar9 = 100;
  }
  *(uint *)(iVar1 + 0x212460) = uVar9;
  cVar4 = *(char *)(param_1 + 0x286285);
LAB_0012fec8:
  if (cVar4 == '\x01') {
    if (99 < uVar3) {
      uVar3 = 100;
    }
    param_2[0x4eb] = uVar3;
  }
  return;
}

