// module: mt7915.ko
// function: sae_parse_password_identifier @ 0x209c2c
// size: 248 bytes
//

undefined4 sae_parse_password_identifier(int param_1,int param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  int *piVar4;
  size_t __n;
  void *__s2;
  
  iVar1 = is_sae_pwd_id_element(param_2,param_3,param_1 + 0x94);
  if (iVar1 == 0) {
    if (param_4 == 0) {
      uVar2 = 0;
    }
    else {
      *(undefined4 *)(param_1 + 0x94) = 0;
      uVar2 = 0x7b;
    }
  }
  else {
    *(int *)(param_1 + 0x90) = param_2 + 3;
    hex_dump_with_cat_and_lvl("peer pwd id",param_2 + 3,*(undefined4 *)(param_1 + 0x94),0xf,0x20,3);
    piVar4 = *(int **)(param_1 + 0x178);
    if ((piVar4 != (int *)0x0) && (piVar3 = (int *)*piVar4, piVar4 != piVar3)) {
      __s2 = *(void **)(param_1 + 0x90);
      __n = *(size_t *)(param_1 + 0x94);
      do {
        iVar1 = memcmp((void *)((int)piVar3 + 0x49),__s2,__n);
        if (iVar1 == 0) {
          *(int **)(param_1 + 0x88) = piVar3;
          *(int **)(param_1 + 0x174) = piVar3 + 2;
          return 0;
        }
        piVar3 = (int *)*piVar3;
      } while (piVar4 != piVar3);
    }
    if (DebugLevel < 3) {
      uVar2 = 0x7b;
    }
    else {
      printk("%s(): pwd id search fail\n","sae_parse_password_identifier");
      uVar2 = 0x7b;
    }
  }
  return uVar2;
}

