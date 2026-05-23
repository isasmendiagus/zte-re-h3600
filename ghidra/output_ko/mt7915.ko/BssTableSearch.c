// module: mt7915.ko
// function: BssTableSearch @ 0x10e4c8
// size: 140 bytes
//

uint BssTableSearch(uint *param_1,void *param_2,uint param_3)

{
  int iVar1;
  void *__s1;
  uint uVar2;
  uint uVar3;
  bool bVar4;
  
  uVar3 = *param_1;
  if (uVar3 != 0) {
    __s1 = (void *)((int)param_1 + 0xe);
    uVar2 = 0;
    do {
      if (*(byte *)((int)__s1 + 6) < 0xf) {
        if (param_3 < 0xf) {
          iVar1 = memcmp(__s1,param_2,6);
joined_r0x0010e4fc:
          if (iVar1 == 0) {
            return uVar2;
          }
        }
      }
      else if (0xe < param_3) {
        iVar1 = memcmp(__s1,param_2,6);
        goto joined_r0x0010e4fc;
      }
      uVar2 = uVar2 + 1;
      bVar4 = 0xfe < uVar2;
      if (uVar2 < 0x100) {
        bVar4 = uVar3 <= uVar2;
      }
      __s1 = (void *)((int)__s1 + 0xaf4);
    } while (!bVar4);
  }
  return 0xffffffff;
}

