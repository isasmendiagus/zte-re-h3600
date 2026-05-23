// module: mt7915.ko
// function: prepare_veri_pkt_ctnt @ 0x1d5c20
// size: 184 bytes
//

undefined4 prepare_veri_pkt_ctnt(int param_1,void *param_2,size_t param_3,undefined4 param_4)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0xa7cc5c) == 1) {
    if ((*(int *)(param_1 + 0xa7cc60) == 1) && (*(int *)(param_1 + 0xa7cc64) == 10)) {
      iVar1 = 10;
    }
    else {
      iVar1 = param_3 + *(int *)(param_1 + 0xa7cc68);
      *(int *)(param_1 + 0xa7cc68) = iVar1;
    }
    __memzero((void *)(param_1 + 0xa7cc7e),0x400,iVar1,param_1 + 0xa7c000,param_4);
    memmove((void *)(param_1 + 0xa7cc7e),param_2,param_3);
    *(undefined4 *)(param_1 + 0xa7cc5c) = 2;
    return 1;
  }
  if (DebugLevel < 1) {
    return 0;
  }
  printk("%s: state error:%d update pkt head first\n","prepare_veri_pkt_ctnt");
  return 0;
}

