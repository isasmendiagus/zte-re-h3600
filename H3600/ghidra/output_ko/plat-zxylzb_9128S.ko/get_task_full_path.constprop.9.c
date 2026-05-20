// module: plat-zxylzb_9128S.ko
// function: get_task_full_path.constprop.9 @ 0x11870
// size: 156 bytes
//

size_t get_task_full_path_constprop_9
                 (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  void *pvVar1;
  int iVar2;
  int iVar3;
  size_t __n;
  
  iVar2 = *(int *)(param_1 + 0x18c);
  if (((iVar2 != 0) && (iVar3 = *(int *)(iVar2 + 0x188), iVar3 != 0)) &&
     (iVar2 = __get_free_pages(0x800d0,0,param_3,iVar2,param_4), iVar2 != 0)) {
    pvVar1 = (void *)d_path(iVar3 + 8,iVar2,0x1000);
    if (pvVar1 == (void *)0x0) {
      __n = 0xffffffff;
    }
    else {
      __n = (iVar2 + 0xfff) - (int)pvVar1;
      if (0x7e < (int)__n) {
        __n = 0x7f;
      }
      pvVar1 = memcpy(&task_path,pvVar1,__n);
      *(undefined1 *)((int)pvVar1 + __n) = 0;
    }
    free_pages(iVar2,0);
    return __n;
  }
  return 0xffffffff;
}

