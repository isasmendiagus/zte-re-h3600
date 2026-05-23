// module: mt7915.ko
// function: multi_profile_apcli_devname_req @ 0x166c70
// size: 104 bytes
//

undefined4 multi_profile_apcli_devname_req(int param_1,char *param_2,int *param_3)

{
  char *pcVar1;
  
  pcVar1 = *(char **)(param_1 + 0xa7cbdc);
  if ((((pcVar1 != (char *)0x0) && (*pcVar1 != '\0')) && (pcVar1[1] != '\0')) && (*param_3 == 1)) {
    pcVar1 = (char *)FUN_001621e4(param_1,0x400);
    if (pcVar1 != (char *)0x0) {
      strcpy(param_2,pcVar1);
    }
    return 0;
  }
  return 0;
}

