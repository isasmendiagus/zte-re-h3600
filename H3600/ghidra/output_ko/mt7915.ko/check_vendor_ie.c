// module: mt7915.ko
// function: check_vendor_ie @ 0x146730
// size: 324 bytes
//

void check_vendor_ie(undefined4 param_1,int param_2,uint *param_3)

{
  byte bVar1;
  int iVar2;
  void *__s1;
  undefined2 local_2c;
  undefined1 local_2a;
  undefined2 local_29;
  undefined1 local_27;
  undefined4 local_26;
  undefined2 local_22;
  
  __s1 = (void *)(param_2 + 2);
  local_29 = 0xc00;
  local_26 = &DAT_004c9000;
  local_2c = 0xc00;
  local_27 = 0xe7;
  local_22 = 0x1810;
  local_2a = 0x43;
  iVar2 = memcmp(__s1,&local_2c,3);
  if ((iVar2 == 0) && (*(char *)(param_2 + 1) == '\a')) {
    bVar1 = *(byte *)(param_2 + 5);
    *(undefined1 *)((int)param_3 + 0xe) = 1;
    *(undefined1 *)(param_3 + 3) = 1;
    *param_3 = (uint)bVar1;
    *(undefined1 *)((int)param_3 + 0xd) = 1;
  }
  else {
    iVar2 = memcmp(__s1,&local_29,3);
    if ((iVar2 != 0) || (*(byte *)(param_2 + 1) < 7)) {
      iVar2 = memcmp(__s1,&local_26,3);
      if (iVar2 == 0) {
        param_3[2] = 1;
        *(undefined1 *)(param_3 + 3) = 1;
        *(undefined1 *)((int)param_3 + 0xd) = 1;
        return;
      }
      iVar2 = memcmp(__s1,(void *)((int)&local_26 + 3),3);
      if (iVar2 == 0) {
        *(undefined1 *)(param_3 + 4) = 1;
      }
      return;
    }
    bVar1 = *(byte *)(param_2 + 5);
    *(undefined1 *)((int)param_3 + 0xf) = 1;
    param_3[1] = (uint)bVar1;
    if (*(byte *)(param_2 + 1) < 8) {
      *(undefined1 *)(param_3 + 3) = 0;
      *(undefined1 *)((int)param_3 + 0xd) = 0;
    }
    else {
      *(undefined1 *)(param_3 + 3) = 1;
      *(undefined1 *)((int)param_3 + 0xd) = 1;
      *(byte *)((int)param_3 + 0x12) = bVar1 >> 7;
      *(undefined1 *)((int)param_3 + 0x11) = 1;
    }
  }
  return;
}

