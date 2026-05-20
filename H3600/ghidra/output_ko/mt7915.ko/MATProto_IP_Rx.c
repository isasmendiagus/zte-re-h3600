// module: mt7915.ko
// function: MATProto_IP_Rx @ 0x7a9dc
// size: 304 bytes
//

int MATProto_IP_Rx(int param_1,int param_2,int param_3)

{
  undefined2 uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = *(int *)(param_1 + 0x20);
  if (param_3 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = *(uint *)(param_3 + 0x10);
  }
  iVar3 = FUN_0007a21c(param_1,uVar2);
  if (iVar5 == 0) {
    if (-1 < DebugLevel) {
      printk("%s():ERROR! pAd is null!\n","MATProto_IP_Rx");
    }
  }
  else {
    iVar4 = *(int *)((uint)*(ushort *)(param_2 + 0x42) * 0x14c0 + iVar5 + 0xa281c);
    if ((((&DAT_0036790d)[iVar5] != '\0') && (iVar4 != 0)) && (*(char *)(iVar4 + 5) == '\x02')) {
      if ((uVar2 & 0xf0) == 0xe0) {
        iVar3 = iVar4 + 0x7d;
      }
      else if ((((&DAT_00367910)[iVar5] != '\x01') && (*(char *)(param_3 + 9) == '\x11')) &&
              (*(short *)(param_3 + 0x16) == 0x4400 && *(short *)(param_3 + 0x14) == 0x4300)) {
        memmove((void *)(param_3 + 0x38),(void *)(iVar4 + 0x7d),6);
        __memzero(param_3 + 0x1a,2);
        uVar1 = RTMP_UDP_Checksum(param_2);
        *(undefined2 *)(param_3 + 0x1a) = uVar1;
      }
    }
  }
  return iVar3;
}

