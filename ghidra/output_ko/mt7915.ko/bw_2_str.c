// module: mt7915.ko
// function: bw_2_str @ 0xb8348
// size: 260 bytes
//

void bw_2_str(undefined4 param_1,char *param_2)

{
  switch(param_1) {
  case 0:
    param_2[0] = '2';
    param_2[1] = '0';
    param_2[2] = '\0';
    return;
  case 1:
    builtin_strncpy(param_2,"20/40",6);
    return;
  case 2:
    builtin_strncpy(param_2,"20/40/80",9);
    return;
  case 3:
    builtin_strncpy(param_2,"20/40/80/160C",0xe);
    return;
  case 4:
    param_2[0] = '1';
    param_2[1] = '0';
    param_2[2] = '\0';
    return;
  case 5:
    param_2[0] = '5';
    param_2[1] = '\0';
    return;
  case 6:
    builtin_strncpy(param_2,"20/40/80/160NC",0xf);
    return;
  default:
    builtin_strncpy(param_2,"Invaild",8);
    return;
  }
}

