// module: mt7915.ko
// function: remove_vie @ 0x145d04
// size: 296 bytes
//

undefined4 remove_vie(undefined4 param_1,undefined4 param_2,uint param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int local_30;
  int local_2c [2];
  
  uVar5 = 0;
  local_30 = 0;
  local_2c[0] = 0;
  do {
    uVar6 = param_3 & 1 << (uVar5 & 0xff);
    if (uVar6 != 0) {
      FUN_0014580c(param_2,local_2c,uVar6);
      if (local_2c[0] == 0) {
        return 1;
      }
      iVar4 = find_oui_oitype(param_2,uVar6,param_4,&local_30);
      iVar3 = local_2c[0];
      iVar2 = local_30;
      if ((iVar4 == 1) && (local_30 != 0)) {
        iVar4 = *(int *)(local_2c[0] + 8);
        if (local_30 == iVar4) {
          *(undefined4 *)(local_2c[0] + 8) = *(undefined4 *)(local_30 + 0xc);
        }
        else {
          iVar1 = *(int *)(iVar4 + 0xc);
          iVar7 = local_30;
          while (iVar1 != 0) {
            if (local_30 == iVar1) {
              *(undefined4 *)(iVar4 + 0xc) = *(undefined4 *)(iVar7 + 0xc);
              break;
            }
            iVar7 = *(int *)(iVar1 + 0xc);
            iVar4 = iVar1;
            iVar1 = iVar7;
          }
        }
        if (*(int *)(local_30 + 8) != 0) {
          os_free_mem();
        }
        os_free_mem(iVar2);
        *(char *)(iVar3 + 4) = *(char *)(iVar3 + 4) + -1;
      }
    }
    uVar5 = uVar5 + 1;
    if (uVar5 == 7) {
      return 0;
    }
  } while( true );
}

