// module: mt7915.ko
// function: WpaDeriveGTK @ 0x11c98c
// size: 244 bytes
//

void WpaDeriveGTK(undefined4 param_1,undefined4 *param_2,undefined4 *param_3,void *param_4,
                 size_t param_5)

{
  char local_d7 [19];
  undefined4 local_c4;
  undefined2 local_c0;
  undefined4 local_be;
  undefined4 local_ba;
  undefined4 local_b6;
  undefined4 local_b2;
  undefined4 local_ae;
  undefined4 local_aa;
  undefined4 local_a6;
  undefined4 local_a2;
  undefined1 auStack_78 [84];
  
  local_b6 = param_2[2];
  local_be = *param_2;
  local_b2 = param_2[3];
  local_ba = param_2[1];
  local_d7[0x12] = 'n';
  local_ae = param_2[4];
  local_aa = param_2[5];
  builtin_strncpy(local_d7,"Grou",4);
  builtin_strncpy(local_d7 + 8,"y ex",4);
  local_a6 = param_2[6];
  local_a2 = param_2[7];
  builtin_strncpy(local_d7 + 0xc,"pans",4);
  local_c4 = *param_3;
  builtin_strncpy(local_d7 + 4,"p ke",4);
  local_c0 = *(undefined2 *)(param_3 + 1);
  local_d7[0x10] = 'i';
  local_d7[0x11] = 'o';
  PRF(param_1,0x20,local_d7,0x13,&local_c4,0x26,auStack_78,param_5);
  memcpy(param_4,auStack_78,param_5);
  return;
}

