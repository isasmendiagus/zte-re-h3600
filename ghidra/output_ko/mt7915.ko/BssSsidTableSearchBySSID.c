// module: mt7915.ko
// function: BssSsidTableSearchBySSID @ 0x10e6ec
// size: 112 bytes
//

uint BssSsidTableSearchBySSID(uint *param_1,void *param_2,size_t param_3)

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
      if ((*(byte *)((int)__s2 + -1) == param_3) &&
         (iVar1 = memcmp(param_2,__s2,param_3), iVar1 == 0)) {
        return uVar2;
      }
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

