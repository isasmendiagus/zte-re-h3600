// module: idmfdb.ko
// function: idm_proc_flood_status_seq_show @ 0x11d14
// size: 84 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 idm_proc_flood_status_seq_show(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = *(undefined4 *)(param_1 + 0x50);
  iVar1 = kmem_cache_alloc(_DAT_000180cc,0x80d0);
  if (iVar1 != 0) {
    print_idm_flood_status(uVar2,iVar1,0xfff);
    seq_printf(param_1,iVar1);
    kfree(iVar1);
  }
  return 0;
}

