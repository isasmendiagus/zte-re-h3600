// module: mt7915.ko
// function: mt7915_get_wf_path_comb @ 0x17dc84
// size: 160 bytes
//

undefined4
mt7915_get_wf_path_comb(undefined4 param_1,int param_2,int param_3,int param_4,byte *param_5)

{
  char cVar1;
  uint uVar2;
  char local_a [2];
  
  local_a[0] = '\0';
  local_a[1] = 2;
  if (param_5 != (byte *)0x0 && param_4 != 0) {
    uVar2 = 0;
    if (param_3 == 0) {
      *param_5 = 4;
      uVar2 = 0;
      do {
        *(char *)(param_4 + uVar2) = (char)uVar2;
        uVar2 = uVar2 + 1 & 0xff;
      } while (uVar2 < *param_5);
      return 0;
    }
    *param_5 = 2;
    cVar1 = local_a[param_2];
    do {
      *(char *)(param_4 + uVar2) = (char)uVar2 + cVar1;
      uVar2 = uVar2 + 1 & 0xff;
    } while (uVar2 < *param_5);
  }
  return 0;
}

