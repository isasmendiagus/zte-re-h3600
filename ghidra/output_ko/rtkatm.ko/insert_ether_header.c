// module: rtkatm.ko
// function: insert_ether_header @ 0x10bf8
// size: 224 bytes
//

undefined4 insert_ether_header(int *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  iVar1 = *param_1;
  if ((uint)(*(int *)(iVar1 + 0xcc) - *(int *)(iVar1 + 200)) < 0xc) {
    iVar1 = skb_realloc_headroom(iVar1,0xc);
    __dev_kfree_skb_any(*param_1,1);
    if (iVar1 == 0) {
      ProcKernLog("/home/ws/zx279128s/chip_zx279128s/kmodule/rtk_atm/rtk_atm.c",0xaf,
                  "insert_ether_header",0,4,0,"insert ether header error\n");
      return 0xffffffff;
    }
    *param_1 = iVar1;
  }
  skb_push(iVar1,0xc);
  puVar2 = *(undefined4 **)(*param_1 + 0xcc);
  *puVar2 = (undefined4)dmac;
  iVar1 = remote_dev;
  *(undefined2 *)(puVar2 + 1) = dmac._4_2_;
  puVar2 = *(undefined4 **)(iVar1 + 0x1dc);
  iVar1 = *(int *)(*param_1 + 0xcc);
  *(undefined4 *)(iVar1 + 6) = *puVar2;
  *(undefined2 *)(iVar1 + 10) = *(undefined2 *)(puVar2 + 1);
  return 1;
}

