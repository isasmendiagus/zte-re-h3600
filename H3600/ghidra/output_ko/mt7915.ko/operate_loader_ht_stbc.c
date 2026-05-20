// module: mt7915.ko
// function: operate_loader_ht_stbc @ 0x1078b0
// size: 104 bytes
//

void operate_loader_ht_stbc(int param_1,uint param_2,int param_3,int param_4)

{
  int iVar1;
  
  if (param_4 == 1) {
    if (param_2 < 2) {
      if (param_3 == 0) {
        param_4 = 0;
        iVar1 = 0;
        goto LAB_001078c4;
      }
      iVar1 = 0;
    }
    else {
      iVar1 = 1;
      if (param_3 == 0) goto LAB_001078c4;
    }
    param_3 = 1;
  }
  else {
    param_3 = 0;
    iVar1 = param_3;
  }
LAB_001078c4:
  *(char *)(param_1 + 10) = (char)param_4;
  *(byte *)(param_1 + 0x36) = *(byte *)(param_1 + 0x36) & 0x7f | (byte)(iVar1 << 7);
  *(byte *)(param_1 + 0x37) = *(byte *)(param_1 + 0x37) & 0xfc | (byte)param_3 & 3;
  return;
}

