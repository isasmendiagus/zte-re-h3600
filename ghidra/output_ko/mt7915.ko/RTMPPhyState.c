// module: mt7915.ko
// function: RTMPPhyState @ 0x37534
// size: 620 bytes
//

undefined4 RTMPPhyState(undefined4 param_1,int param_2)

{
  ushort uVar1;
  char *__s1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined1 auStack_20 [4];
  int local_1c;
  
  local_1c = 0;
  if ((*(ushort *)(param_2 + 0x14) == 1) && (**(char **)(param_2 + 0x10) == '\0')) {
    iVar4 = iwprivPhyStatHelp(*(char **)(param_2 + 0x10),0x2800);
    if (iVar4 != 0) {
      *(short *)(param_2 + 0x14) = (short)iVar4;
    }
    return 0;
  }
  os_alloc_mem(0,&local_1c,*(ushort *)(param_2 + 0x14) + 1);
  if (local_1c == 0) {
    return 0xfffffff4;
  }
  uVar2 = (uint)*(ushort *)(param_2 + 0x14);
  uVar3 = *(uint *)(((uint)auStack_20 & 0xffffe000) + 8);
  if (!CARRY4(*(uint *)(param_2 + 0x10),uVar2) && *(uint *)(param_2 + 0x10) + uVar2 <= uVar3) {
    uVar3 = 0;
  }
  if (uVar3 == 0) {
    iVar4 = __copy_from_user();
    if (iVar4 != 0) goto LAB_00037768;
    uVar3 = (uint)*(ushort *)(param_2 + 0x14);
  }
  else {
    uVar3 = 0;
    if (uVar2 != 0) {
      __memzero(local_1c,uVar2);
LAB_00037768:
      os_free_mem(local_1c);
      return 0xfffffff2;
    }
  }
  uVar2 = 0;
  *(undefined1 *)(local_1c + uVar3) = 0;
  __s1 = (char *)rstrtok(local_1c,&_LC612);
  if (__s1 == (char *)0x0) {
    uVar5 = 0;
    uVar2 = 0;
  }
  else {
    iVar4 = 0;
    uVar5 = 0;
    do {
      if (iVar4 == 0) {
        iVar4 = strcmp(__s1,"read");
        if (iVar4 == 0) {
          uVar5 = 0;
        }
        else {
          iVar4 = strcmp(__s1,"write");
          if (iVar4 == 0) {
            uVar5 = 1;
          }
        }
        __s1 = (char *)rstrtok(0,&_LC612);
        if (__s1 == (char *)0x0) break;
LAB_000375dc:
        uVar2 = simple_strtol(__s1,0,10);
        iVar4 = rstrtok(0,&_LC612);
        if (iVar4 == 0) break;
        iVar4 = 2;
      }
      else if (iVar4 == 1) goto LAB_000375dc;
      if (-1 < DebugLevel) {
        printk("%s: set wrong parameters\n","RTMPPhyState");
      }
      iVar4 = iVar4 + 1;
      __s1 = (char *)rstrtok(0,&_LC612);
    } while (__s1 != (char *)0x0);
  }
  _LANCHOR1 = &DAT_0032a9ec;
  uVar1 = DAT_0032a9ec;
  do {
    if (1 < uVar1) {
LAB_000376dc:
      uVar5 = 0;
LAB_000376e0:
      os_free_mem(local_1c);
      return uVar5;
    }
    if (uVar1 == uVar2) {
      iVar4 = (**(code **)(_LANCHOR1 + 2))(param_1,0,uVar5);
      if (iVar4 == 0) {
        uVar5 = 0xffffffea;
        goto LAB_000376e0;
      }
      goto LAB_000376dc;
    }
    _LANCHOR1 = _LANCHOR1 + 6;
    uVar1 = *_LANCHOR1;
  } while( true );
}

