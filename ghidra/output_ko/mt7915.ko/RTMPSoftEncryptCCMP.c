// module: mt7915.ko
// function: RTMPSoftEncryptCCMP @ 0xb708c
// size: 284 bytes
//

bool RTMPSoftEncryptCCMP(undefined4 param_1,byte *param_2,undefined4 param_3,undefined4 param_4,
                        undefined4 param_5,int param_6)

{
  int iVar1;
  bool bVar2;
  uint uVar3;
  uint uVar4;
  undefined4 local_60;
  undefined4 local_5c;
  int local_58;
  undefined1 auStack_53 [13];
  undefined1 auStack_46 [34];
  
  local_58 = param_6 + 8;
  local_60 = 0;
  local_5c = 0;
  __memzero(auStack_46,0x1e);
  __memzero(auStack_53,0xd);
  uVar4 = ((uint)*param_2 << 0x1c) >> 0x1e;
  uVar3 = ((uint)param_2[1] << 0x1e) >> 0x1f & (uint)param_2[1];
  bVar2 = uVar4 == 2 && (*param_2 >> 4) - 8 < 4;
  RTMPConstructCCMPAAD(param_2,uVar4 == 2,uVar3,bVar2,auStack_46,&local_60);
  RTMPConstructCCMPNonce(param_2,uVar3,bVar2,uVar4 == 0,param_3,auStack_53,&local_5c);
  iVar1 = AES_CCM_Encrypt(param_5,param_6,param_4,0x10,auStack_53,local_5c,auStack_46,local_60,8,
                          param_5,&local_58);
  return iVar1 == 0;
}

