// module: mt7915.ko
// function: multi_profile_devname_req @ 0x166be4
// size: 140 bytes
//

undefined4 multi_profile_devname_req(int param_1,char *param_2,byte *param_3)

{
  int iVar1;
  undefined4 uVar2;
  char *pcVar3;
  
  pcVar3 = *(char **)(param_1 + 0xa7cbdc);
  if ((((pcVar3 != (char *)0x0) && (*pcVar3 != '\0')) && (pcVar3[1] != '\0')) &&
     ((byte)pcVar3[2] <= *param_3)) {
    if (*param_3 == pcVar3[2]) {
      uVar2 = 0x100;
    }
    else {
      uVar2 = 0x200;
    }
    iVar1 = FUN_001621e4(param_1,uVar2);
    if (iVar1 != 0) {
      snprintf(param_2,0x10,"%s",iVar1);
    }
    *param_3 = *param_3 - pcVar3[2];
  }
  return 0;
}

