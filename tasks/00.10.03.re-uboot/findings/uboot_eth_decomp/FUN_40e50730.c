// FUN_40e50730 @ 40e50730

undefined4 FUN_40e50730(undefined4 param_1,uint param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  uVar2 = FUN_40e4ff88();
  iVar3 = DAT_40e50848/*=0x47f59640*/;
  if ((int)uVar2 < 0) {
    FUN_40e2a1b4(DAT_40e50840/*=0x47f3ecf8*/);
  }
  else {
    if ((int)uVar2 < 0x800) {
      iVar4 = uVar2 * 0x800 + 0x41000010;
      FUN_40e45880(iVar4,param_1,param_2);
      *(byte *)(param_3 + 7) = *(byte *)(param_3 + 7) & 1 | (byte)((uVar2 & 0x7f) << 1);
      *(char *)(param_3 + 8) = (char)((int)uVar2 >> 7);
      *(ushort *)(param_3 + 0xc) =
           *(ushort *)(param_3 + 0xc) & 3 | (ushort)((param_2 & 0x3fff) << 2);
      uVar1 = *(uint *)(param_3 + 8) & 0xff8001ff;
      *(uint *)(param_3 + 8) = uVar1 | (param_2 & 0x3fff) << 9;
      *(byte *)(param_3 + 0xb) = (byte)(uVar1 >> 0x18) & 1 | 0x20;
      if (0 < *(int *)(iVar3 + 4)) {
        FUN_40e2a1b4(DAT_40e5084c/*=0x47f3ed1b*/,param_2,uVar2,iVar4);
        FUN_40e503e4(iVar4,param_2);
        *(int *)(iVar3 + 4) = *(int *)(iVar3 + 4) + -1;
      }
      FUN_40e215f0(iVar4,iVar4 + param_2);
      iVar3 = FUN_40e502f0(param_3);
      if (iVar3 < 0) {
        FUN_40e2a1b4(DAT_40e50850/*=0x47f3ed38*/);
        return 0xfffffffe;
      }
      return 0;
    }
    FUN_40e2a1b4(DAT_40e50844/*=0x47f3ed09*/,uVar2);
  }
  return 0xffffffff;
}
