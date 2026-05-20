// module: rtkatm.ko
// function: insert_mpoatag @ 0x10b20
// size: 212 bytes
//

undefined4 insert_mpoatag(int *param_1,undefined1 param_2)

{
  int iVar1;
  
  iVar1 = *param_1;
  if ((uint)(*(int *)(iVar1 + 0xcc) - *(int *)(iVar1 + 200)) < 4) {
    iVar1 = skb_realloc_headroom(iVar1,4);
    __dev_kfree_skb_any(*param_1,1);
    if (iVar1 == 0) {
      ProcKernLog("/home/ws/zx279128s/chip_zx279128s/kmodule/rtk_atm/rtk_atm.c",0x93,
                  "insert_mpoatag",0,4,0,"insert mpoatag error\n");
      return 0xffffffff;
    }
    *param_1 = iVar1;
  }
  skb_push(iVar1,4);
  memmove(*(void **)(*param_1 + 0xcc),(void *)((int)*(void **)(*param_1 + 0xcc) + 4),0xc);
  iVar1 = *(int *)(*param_1 + 0xcc);
  *(undefined1 *)(iVar1 + 0xf) = param_2;
  *(undefined1 *)(iVar1 + 0xc) = 0x88;
  *(undefined1 *)(iVar1 + 0xd) = 0x4c;
  *(undefined1 *)(iVar1 + 0xe) = 0;
  return 1;
}

