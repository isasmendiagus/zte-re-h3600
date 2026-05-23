// module: mt7915.ko
// function: Set_DeletePMKID_Proc @ 0x32d50
// size: 80 bytes
//

undefined4 Set_DeletePMKID_Proc(int param_1,undefined4 param_2)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  
  uVar1 = os_str_tol(param_2,0,10);
  iVar2 = 0;
  do {
    iVar3 = iVar2 + 1;
    RTMPDeletePMKIDCache(&DAT_003687fc + param_1,uVar1,iVar2);
    iVar2 = iVar3;
  } while (iVar3 != 0x80);
  return 1;
}

