// module: mt7915.ko
// function: RTMP_UDP_Checksum @ 0xedab4
// size: 112 bytes
//

uint RTMP_UDP_Checksum(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  short sVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  
  iVar3 = *(int *)(param_1 + 0xcc);
  sVar1 = CONCAT11(*(undefined1 *)(iVar3 + 0xc),*(undefined1 *)(iVar3 + 0xd));
  if (sVar1 == -0x7f00) {
    iVar3 = iVar3 + 0x12;
  }
  else {
    iVar3 = iVar3 + 0xe;
  }
  uVar4 = (*(ushort *)(iVar3 + 0x18) & 0xff) << 8 | (uint)(*(ushort *)(iVar3 + 0x18) >> 8);
  uVar2 = FUN_000d7e14(iVar3 + 0xc,8,uVar4 + 0x11,sVar1,param_4);
  uVar2 = FUN_000d7e14(iVar3 + 0x1c,uVar4 - 8 & 0xffff,uVar2);
  uVar4 = FUN_000d7e14(iVar3 + 0x14,8,uVar2);
  return (~uVar4 & 0xff) << 8 | ~uVar4 >> 8 & 0xff;
}

