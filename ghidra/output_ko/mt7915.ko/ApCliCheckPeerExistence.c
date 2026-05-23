// module: mt7915.ko
// function: ApCliCheckPeerExistence @ 0x6b0d4
// size: 260 bytes
//

void ApCliCheckPeerExistence(int param_1,void *param_2,size_t param_3,uint param_4)

{
  int iVar1;
  void *__s2;
  
  __s2 = (void *)(param_1 + 0x580e3a);
  do {
    if (((*(char *)((int)__s2 + 0x62) != '\x01') && (*(byte *)((int)__s2 + -0x2132c8) == param_4))
       && ((((*(byte *)((int)__s2 + 0x20) == param_3 &&
             (iVar1 = memcmp(param_2,__s2,param_3), iVar1 == 0)) || (param_3 == 0)) ||
           (((*(int *)((int)__s2 + -0x211ffe) != 0 && (*(char *)((int)__s2 + -0x20f61a) == '\x01'))
            && (iVar1 = memcmp(param_2,(void *)((int)__s2 + -0x211fd2),param_3), iVar1 == 0)))))) {
      *(undefined1 *)((int)__s2 + 0x62) = 1;
    }
    __s2 = (void *)((int)__s2 + 0x2137b0);
  } while (__s2 != (void *)(param_1 + 0x9a7d9a));
  return;
}

