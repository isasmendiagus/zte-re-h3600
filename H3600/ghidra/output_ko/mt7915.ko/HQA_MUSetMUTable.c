// module: mt7915.ko
// function: HQA_MUSetMUTable @ 0x272008
// size: 252 bytes
//

int HQA_MUSetMUTable(undefined4 param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  uint __n;
  void *local_34;
  uint local_30;
  undefined2 local_2c [2];
  uint local_28;
  void *local_24;
  
  local_34 = (void *)0x0;
  os_zero_mem(local_2c,0xc);
  uVar1 = *(uint *)(param_3 + 0xc);
  __n = ((*(ushort *)(param_3 + 8) & 0xff) << 8 | (uint)(*(ushort *)(param_3 + 8) >> 8)) - 4 &
        0xffff;
  uVar1 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 | uVar1 >> 0x18;
  local_30 = uVar1;
  iVar2 = os_alloc_mem(param_1,&local_34,__n);
  if (iVar2 == 0) {
    os_zero_mem(local_34,__n);
    memmove(local_34,(void *)(param_3 + 0x10),__n);
    local_2c[0] = (undefined2)uVar1;
    local_24 = local_34;
    local_28 = __n;
    iVar2 = hqa_wifi_test_mu_table_set(param_1,local_2c);
    os_free_mem(local_34);
  }
  if (0 < DebugLevel) {
    printk("%s: len:%u, su_mu:%u\n","HQA_MUSetMUTable",__n,uVar1);
  }
  FUN_0026cdd0(param_3,param_2,2,iVar2);
  return iVar2;
}

