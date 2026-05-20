// module: mt7915.ko
// function: BssSsidTableSearch @ 0x10e554
// size: 176 bytes
//

uint BssSsidTableSearch(uint *param_1,void *param_2,void *param_3,size_t param_4,byte param_5)

{
  int iVar1;
  void *__s2;
  uint uVar2;
  uint uVar3;
  bool bVar4;
  
  uVar3 = *param_1;
  if (uVar3 != 0) {
    __s2 = (void *)((int)param_1 + 0x9d);
    uVar2 = 0;
    do {
      if (*(byte *)((int)__s2 + -0x89) < 0xf) {
        if (param_5 < 0xf) {
LAB_0010e588:
          iVar1 = memcmp((void *)((int)__s2 + -0x8f),param_2,6);
          if (((iVar1 == 0) && (*(byte *)((int)__s2 + -1) == param_4)) &&
             (iVar1 = memcmp(param_3,__s2,param_4), iVar1 == 0)) {
            return uVar2;
          }
        }
      }
      else if (0xe < param_5) goto LAB_0010e588;
      uVar2 = uVar2 + 1;
      bVar4 = 0xfe < uVar2;
      if (uVar2 < 0x100) {
        bVar4 = uVar3 <= uVar2;
      }
      __s2 = (void *)((int)__s2 + 0xaf4);
    } while (!bVar4);
  }
  return 0xffffffff;
}

