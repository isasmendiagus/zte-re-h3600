// module: mt7915.ko
// function: BssTableSearchWithSSID @ 0x10e604
// size: 232 bytes
//

uint BssTableSearchWithSSID(uint *param_1,void *param_2,void *param_3,size_t param_4,byte param_5)

{
  byte bVar1;
  int iVar2;
  void *__s2;
  uint uVar3;
  uint uVar4;
  bool bVar5;
  
  uVar3 = *param_1;
  if (uVar3 != 0) {
    __s2 = (void *)((int)param_1 + 0x9d);
    uVar4 = 0;
    do {
      if (*(byte *)((int)__s2 + -0x89) < 0xf) {
        if (param_5 < 0xf) {
LAB_0010e638:
          iVar2 = memcmp((void *)((int)__s2 + -0x8f),param_2,6);
          if ((iVar2 == 0) &&
             ((((bVar1 = *(byte *)((int)__s2 + -1), bVar1 == param_4 &&
                (iVar2 = memcmp(param_3,__s2,param_4), iVar2 == 0)) ||
               (iVar2 = memcmp(param_3,ZeroSsid,param_4), iVar2 == 0)) ||
              (iVar2 = memcmp(__s2,ZeroSsid,(uint)bVar1), iVar2 == 0)))) {
            return uVar4;
          }
        }
      }
      else if (0xe < param_5) goto LAB_0010e638;
      uVar4 = uVar4 + 1;
      bVar5 = 0xfe < uVar4;
      if (uVar4 < 0x100) {
        bVar5 = uVar3 <= uVar4;
      }
      __s2 = (void *)((int)__s2 + 0xaf4);
    } while (!bVar5);
  }
  return 0xffffffff;
}

