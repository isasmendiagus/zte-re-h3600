// module: mt7915.ko
// function: extcha_2_str @ 0xb8468
// size: 172 bytes
//

void extcha_2_str(undefined4 param_1,char *param_2)

{
  switch(param_1) {
  case 0:
    builtin_strncpy(param_2,"NONE",5);
    return;
  case 1:
    builtin_strncpy(param_2,"ABOVE",6);
    return;
  default:
    builtin_strncpy(param_2,"Invaild",8);
    return;
  case 3:
    builtin_strncpy(param_2,"BELOW",6);
    return;
  case 0xf:
    builtin_strncpy(param_2,"Not assignment",0xf);
    return;
  }
}

