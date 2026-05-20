// module: mt7915.ko
// function: RTMPSoftDecryptCCMP @ 0xb71a8
// size: 436 bytes
//

undefined1
RTMPSoftDecryptCCMP(undefined4 param_1,byte *param_2,int param_3,undefined1 *param_4,ushort *param_5
                   )

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  bool bVar4;
  uint uVar5;
  undefined4 local_68;
  undefined4 local_64;
  uint local_60;
  undefined1 local_59;
  undefined1 local_58;
  undefined1 local_57;
  undefined1 local_56;
  undefined1 local_55;
  undefined1 local_54;
  undefined1 auStack_53 [13];
  undefined1 auStack_46 [34];
  
  local_68 = 0;
  local_60 = (uint)*param_5;
  local_64 = 0;
  if (*(char *)(param_3 + 0x41) == '\0') {
    if (-1 < DebugLevel) {
      printk("%s : The key is not available !\n","RTMPSoftDecryptCCMP");
      return 0;
    }
  }
  else {
    __memzero(auStack_46,0x1e);
    __memzero(auStack_53,0xd);
    uVar3 = ((uint)*param_2 << 0x1c) >> 0x1e;
    bVar4 = uVar3 == 2 && (*param_2 >> 4) - 8 < 4;
    local_59 = *param_4;
    uVar1 = *param_5;
    local_58 = param_4[1];
    local_57 = param_4[4];
    local_56 = param_4[5];
    local_55 = param_4[6];
    local_54 = param_4[7];
    if (8 < uVar1) {
      uVar5 = ((uint)param_2[1] << 0x1e) >> 0x1f & (uint)param_2[1];
      RTMPConstructCCMPAAD(param_2,uVar3 == 2,uVar5,bVar4,auStack_46,&local_68);
      RTMPConstructCCMPNonce(param_2,uVar5,bVar4,uVar3 == 0,&local_59,auStack_53,&local_64);
      iVar2 = AES_CCM_Decrypt(param_4 + 8,uVar1 - 8,param_3,0x10,auStack_53,local_64,auStack_46,
                              local_68,8,param_4,&local_60);
      if (iVar2 == 0) {
        *param_5 = (ushort)local_60;
        return 1;
      }
    }
  }
  return 0;
}

