// module: mt7915.ko
// function: HQA_BFSounding @ 0x27256c
// size: 408 bytes
//

undefined4 HQA_BFSounding(undefined4 param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  uint *puVar2;
  uint *puVar3;
  uint __n;
  undefined4 uVar4;
  int iVar5;
  char *local_44;
  uint local_40 [4];
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined1 local_24;
  
  os_alloc_mem(param_1,&local_44,0x200);
  if (local_44 == (char *)0x0) {
    uVar4 = 3;
  }
  else {
    __n = (*(ushort *)(param_3 + 8) & 0xff) << 8 | (uint)(*(ushort *)(param_3 + 8) >> 8);
    if (__n < 0x21) {
      memcpy(local_40,(void *)(param_3 + 0xc),__n);
      if (__n >> 2 != 0) {
        puVar2 = local_40;
        do {
          uVar1 = *puVar2;
          puVar3 = puVar2 + 1;
          *puVar2 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 |
                    uVar1 >> 0x18;
          puVar2 = puVar3;
        } while (puVar3 != local_40 + (__n >> 2));
      }
      puVar2 = local_40;
      iVar5 = 0;
      do {
        if (0 < DebugLevel) {
          printk("DWORD%d:%08x\n",iVar5,*puVar2);
        }
        iVar5 = iVar5 + 1;
        puVar2 = puVar2 + 1;
      } while (iVar5 != 8);
      __memzero(local_44,0x200);
      sprintf(local_44,"%02x:%02x:%02x:%02x:%02x:%02x:%02x",local_40[0],local_40[1],local_40[2],
              local_40[3],local_30,local_2c,local_28);
      MtATESetMacTxRx(param_1,1,1,local_24);
      Set_Trigger_Sounding_Proc(param_1,local_44);
      if (local_44 == (char *)0x0) {
        uVar4 = 0;
        goto LAB_002725bc;
      }
      uVar4 = 0;
    }
    else {
      uVar4 = 2;
    }
    os_free_mem();
  }
LAB_002725bc:
  if (0 < DebugLevel) {
    printk(&_LC11,"HQA_BFSounding");
  }
  FUN_0026cdd0(param_3,param_2,2,uVar4);
  return uVar4;
}

