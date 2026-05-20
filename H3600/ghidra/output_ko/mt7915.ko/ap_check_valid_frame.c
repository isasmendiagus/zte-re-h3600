// module: mt7915.ko
// function: ap_check_valid_frame @ 0x1ede8
// size: 80 bytes
//

bool ap_check_valid_frame(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  
  bVar1 = *(byte *)(*(int *)(param_2 + 0x1c) + 1);
  if ((bVar1 & 1) == 0) {
    return false;
  }
  if (((bVar1 & 2) == 0) && (iVar2 = ap_chk_cl2_cl3_err(), iVar2 != 0)) {
    return false;
  }
  return (&DAT_003687e5)[param_1] != '\x01';
}

