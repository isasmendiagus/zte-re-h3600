// module: mt7915.ko
// function: is_sae_pwd_id_element @ 0x209ab0
// size: 104 bytes
//

undefined4 is_sae_pwd_id_element(char *param_1,int param_2,int *param_3)

{
  uint uVar1;
  
  if ((2 < param_2 - (int)param_1) && (*param_1 == -1)) {
    uVar1 = (uint)(byte)param_1[1];
    if (uVar1 == 0) {
      return 0;
    }
    if (((int)uVar1 <= (param_2 - (int)param_1) + -2) && (param_1[2] == '!')) {
      if (param_3 != (int *)0x0) {
        *param_3 = uVar1 - 1;
        return 1;
      }
      return 1;
    }
  }
  return 0;
}

