// module: mt7915.ko
// function: get_own_he_ie @ 0x205f74
// size: 120 bytes
//

void get_own_he_ie(undefined4 param_1,int param_2)

{
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  FUN_0020429c();
  FUN_002043c4(param_1,param_2 + 6);
  __memzero(&local_1c,0xc);
  FUN_00204d68(param_1,&local_1c);
  *(undefined4 *)(param_2 + 0x11) = local_1c;
  *(undefined4 *)(param_2 + 0x15) = local_18;
  *(undefined4 *)(param_2 + 0x19) = local_14;
  FUN_002049e0(param_1,param_2 + 0x1d);
  *(undefined2 *)(param_2 + 0x21) = 0xfffc;
  return;
}

