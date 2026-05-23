// module: mt7915.ko
// function: RtmpIoctl_rt_ioctl_siwencodeext @ 0x63c74
// size: 1604 bytes
//

undefined4
RtmpIoctl_rt_ioctl_siwencodeext(int *param_1,undefined4 *param_2,undefined4 param_3,int param_4)

{
  short sVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  uint uVar7;
  void *__dest;
  int iVar8;
  undefined1 uVar9;
  undefined2 uVar10;
  undefined1 uStack_21;
  
  iVar8 = *(int *)(*param_1 + 0x3c);
  iVar3 = GetAssociatedAPByWdev(param_1,param_4);
  uVar7 = param_2[2];
  if (3 < uVar7) {
switchD_00063cd8_default:
    return 1;
  }
  if (((*(ushort *)(param_2 + 5) & 1) != 0) &&
     (*(char *)(param_4 + 0x178) = (char)uVar7, 2 < DebugLevel)) {
    printk("%s::DefaultKeyId = %d\n","RtmpIoctl_rt_ioctl_siwencodeext",uVar7);
  }
  switch(param_2[4]) {
  case 1:
    if (DebugLevel < 3) {
      return 0;
    }
    printk("%s::IW_ENCODE_ALG_NONE\n","RtmpIoctl_rt_ioctl_siwencodeext");
    return 0;
  case 2:
    if (2 < DebugLevel) {
      printk("%s::IW_ENCODE_ALG_WEP - ext->key_len = %d, keyIdx = %d\n",
             "RtmpIoctl_rt_ioctl_siwencodeext",*(undefined2 *)(param_2 + 1),uVar7);
    }
    sVar1 = *(short *)(param_2 + 1);
    if (sVar1 == 0xd) {
      uVar9 = 2;
    }
    else {
      if (sVar1 != 5) {
        return 1;
      }
      uVar9 = 1;
    }
    __dest = (void *)((int)param_1 + uVar7 * 0x49 + 0xa37764);
    *(char *)((int)param_1 + uVar7 * 0x49 + 0xa377a5) = (char)sVar1;
    *(undefined1 *)((int)param_1 + uVar7 * 0x49 + 0xa377a4) = uVar9;
    __memzero(__dest,0x10);
    memmove(__dest,(void *)*param_2,(uint)*(ushort *)(param_2 + 1));
    if (param_1[iVar8 * 0x84dec + 0x16000a] - 0xdU < 2) {
      AsicAddSharedKeyEntry(param_1,0,uVar7 & 0xff,__dest);
      iVar3 = GetStaCfgByWdev(param_1,param_4);
      iVar8 = GetAssociatedAPByWdev(param_1,param_4);
      *(undefined1 *)(param_4 + 0x888) = 1;
      RTMP_IndicateMediaState(param_1);
      _raw_spin_lock_bh(param_1 + 0xa1656);
      if (iVar8 != 0) {
        *(undefined1 *)((int)param_1 + (uint)*(ushort *)(iVar8 + 0xe0) * 0x620 + 0x2f762) =
             *(undefined1 *)(param_4 + 0x888);
        *(undefined4 *)(iVar8 + 0xadc) = 0;
      }
      _raw_spin_unlock_bh(param_1 + 0xa1656);
      RTMPCancelTimer(iVar3 + 0x212470,&uStack_21);
    }
    return 0;
  case 3:
    if (2 < DebugLevel) {
      printk("%s::IW_ENCODE_ALG_TKIP - keyIdx = %d, ext->key_len = %d\n",
             "RtmpIoctl_rt_ioctl_siwencodeext",uVar7,*(undefined2 *)(param_2 + 1));
    }
    if (*(short *)(param_2 + 1) != 0x20) {
      return 1;
    }
    if ((*(uint *)(param_4 + 0x2c) & 0x20) == 0) {
      uVar2 = *(ushort *)(param_2 + 5);
      if ((uVar2 & 1) == 0) {
        if ((uVar2 & 2) == 0) goto LAB_00063d44;
        fnSetCipherKey(param_1,uVar7,3,1,*param_2,0x20,param_4);
        iVar8 = GetStaCfgByWdev(param_1,param_4);
        iVar4 = GetAssociatedAPByWdev(param_1,param_4);
        *(undefined1 *)(param_4 + 0x888) = 1;
        goto LAB_00063e40;
      }
      fnSetCipherKey(param_1,uVar7,3,0,*param_2,0x20,param_4);
      uVar7 = *(uint *)(param_4 + 0x2c) & 0xc0;
joined_r0x00064164:
      if (uVar7 == 0) goto LAB_00063d44;
      iVar8 = GetStaCfgByWdev(param_1,param_4);
      iVar4 = GetAssociatedAPByWdev(param_1,param_4);
      *(undefined1 *)(param_4 + 0x888) = 1;
      RTMP_IndicateMediaState(param_1);
      _raw_spin_lock_bh(param_1 + 0xa1656);
      if (iVar4 != 0) {
        *(undefined1 *)((int)param_1 + (uint)*(ushort *)(iVar4 + 0xe0) * 0x620 + 0x2f762) =
             *(undefined1 *)(param_4 + 0x888);
        *(undefined4 *)(iVar4 + 0xadc) = 0;
      }
    }
    else {
      RTMPZeroMemory(param_1 + iVar8 * 0x84dec + 0x16001e,0x20);
      RTMPMoveMemory(param_1 + iVar8 * 0x84dec + 0x16001e,*param_2,*(undefined2 *)(param_2 + 1));
      uVar10 = *(undefined2 *)(param_2 + 1);
      uVar6 = *param_2;
      uVar5 = 3;
      if ((*(ushort *)(param_2 + 5) & 1) == 0) goto LAB_00064234;
LAB_00064090:
      fnSetCipherKey(param_1,uVar7,uVar5,0,uVar6,uVar10,param_4);
LAB_0006409c:
      iVar8 = GetStaCfgByWdev(param_1,param_4);
      iVar4 = GetAssociatedAPByWdev(param_1,param_4);
      *(undefined1 *)(param_4 + 0x888) = 1;
      RTMP_IndicateMediaState(param_1);
      _raw_spin_lock_bh(param_1 + 0xa1656);
      if (iVar4 != 0) {
        *(undefined1 *)((int)param_1 + (uint)*(ushort *)(iVar4 + 0xe0) * 0x620 + 0x2f762) =
             *(undefined1 *)(param_4 + 0x888);
        *(undefined4 *)(iVar4 + 0xadc) = 0;
      }
    }
    break;
  case 4:
    if ((*(uint *)(param_4 + 0x2c) & 0x20) != 0) {
      RTMPZeroMemory(param_1 + iVar8 * 0x84dec + 0x16001e,0x20);
      RTMPMoveMemory(param_1 + iVar8 * 0x84dec + 0x16001e,*param_2,*(undefined2 *)(param_2 + 1));
      uVar10 = *(undefined2 *)(param_2 + 1);
      uVar6 = *param_2;
      uVar5 = 4;
      if ((*(ushort *)(param_2 + 5) & 1) != 0) goto LAB_00064090;
LAB_00064234:
      fnSetCipherKey(param_1,uVar7,uVar5,1,uVar6,uVar10,param_4);
      goto LAB_0006409c;
    }
    uVar2 = *(ushort *)(param_2 + 5);
    if ((uVar2 & 1) != 0) {
      fnSetCipherKey(param_1,uVar7,4,0,*param_2,*(undefined2 *)(param_2 + 1),param_4);
      uVar7 = *(uint *)(param_4 + 0x2c) & 0x12cf8;
      goto joined_r0x00064164;
    }
    if ((uVar2 & 2) == 0) goto LAB_00063d44;
    fnSetCipherKey(param_1,uVar7,4,1,*param_2,*(undefined2 *)(param_2 + 1),param_4);
    iVar8 = GetStaCfgByWdev(param_1,param_4);
    iVar4 = GetAssociatedAPByWdev(param_1,param_4);
    *(undefined1 *)(param_4 + 0x888) = 1;
LAB_00063e40:
    RTMP_IndicateMediaState(param_1);
    _raw_spin_lock_bh(param_1 + 0xa1656);
    if (iVar4 != 0) {
      *(undefined1 *)((int)param_1 + (uint)*(ushort *)(iVar4 + 0xe0) * 0x620 + 0x2f762) =
           *(undefined1 *)(param_4 + 0x888);
      *(uint *)(iVar4 + 0xadc) = uVar2 & 1;
    }
    break;
  default:
    goto switchD_00063cd8_default;
  }
  _raw_spin_unlock_bh(param_1 + 0xa1656);
  RTMPCancelTimer(iVar8 + 0x212470,&uStack_21);
LAB_00063d44:
  *(undefined1 *)((int)param_1 + (uint)*(ushort *)(iVar3 + 0xe0) * 0x620 + 0x2f762) = 1;
  *(undefined4 *)(iVar3 + 0xadc) = 0;
  WifiSysUpdatePortSecur(param_1,iVar3,0);
  return 0;
}

