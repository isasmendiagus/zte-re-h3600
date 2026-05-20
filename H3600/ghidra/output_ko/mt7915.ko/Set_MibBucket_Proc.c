// module: mt7915.ko
// function: Set_MibBucket_Proc @ 0xc32d4
// size: 84 bytes
//

undefined4 Set_MibBucket_Proc(int param_1,undefined4 param_2)

{
  undefined1 uVar1;
  uint uVar2;
  
  uVar2 = HcGetAmountOfBand();
  uVar1 = os_str_tol(param_2,0,10);
  if ((uVar2 != 0) && (*(undefined1 *)(param_1 + 0xa7c304) = uVar1, 1 < uVar2)) {
    *(undefined1 *)(param_1 + 0xa7c305) = uVar1;
  }
  *(undefined1 *)(param_1 + 0xa7c349) = uVar1;
  return 1;
}

