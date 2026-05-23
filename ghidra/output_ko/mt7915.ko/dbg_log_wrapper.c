// module: mt7915.ko
// function: dbg_log_wrapper @ 0x1d5320
// size: 452 bytes
//

undefined4 dbg_log_wrapper(int param_1,int param_2,void *param_3,size_t param_4)

{
  byte bVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  ushort *__src;
  undefined4 *local_24;
  
  iVar3 = hc_get_chip_dbg(*(undefined4 *)(param_1 + 0xa797a0));
  local_24 = (undefined4 *)0x0;
  if ((*(byte *)(param_1 + 0xa7cc32) & 0x18) != 0) {
    if (param_2 == 0xc) {
      __src = *(ushort **)((int)param_3 + 0xcc);
      uVar6 = *__src + 0xc & 0xffff;
      iVar4 = os_alloc_mem(param_1,&local_24,uVar6);
      puVar2 = local_24;
      if (iVar4 != 0) {
        return 1;
      }
      *local_24 = 0x44e98caf;
      if (*(code **)(iVar3 + 0x90) == (code *)0x0) {
        local_24[1] = 0;
      }
      else {
        uVar5 = (**(code **)(iVar3 + 0x90))(param_1);
        puVar2[1] = uVar5;
      }
      *(undefined2 *)(puVar2 + 2) = 0xc;
      *(ushort *)((int)puVar2 + 10) = *__src;
      memcpy(local_24 + 3,__src,(uint)*__src);
    }
    else {
      if (param_2 != 0x13) {
        return 0;
      }
      if (*(char *)(param_1 + 0xa7cc53) == '\0') {
        return 0;
      }
      uVar6 = param_4 + 0xc & 0xffff;
      iVar4 = os_alloc_mem(param_1,&local_24,uVar6);
      puVar2 = local_24;
      if (iVar4 != 0) {
        return 1;
      }
      *local_24 = 0x44e98caf;
      if (*(code **)(iVar3 + 0x90) == (code *)0x0) {
        local_24[1] = 0;
      }
      else {
        uVar5 = (**(code **)(iVar3 + 0x90))(param_1);
        puVar2[1] = uVar5;
      }
      *(short *)((int)puVar2 + 10) = (short)param_4;
      *(undefined2 *)(puVar2 + 2) = 0x13;
      os_move_mem(local_24 + 3,param_3,param_4);
    }
    if (uVar6 != 0) {
      bVar1 = *(byte *)(param_1 + 0xa7cc32);
      if ((bVar1 & 8) != 0) {
        RTEnqueueInternalCmd(param_1,0x1f,local_24,uVar6);
        bVar1 = *(byte *)(param_1 + 0xa7cc32);
      }
      if ((bVar1 & 0x10) != 0) {
        fw_log_to_ethernet(param_1,local_24,uVar6);
      }
      os_free_mem(local_24);
    }
  }
  return 0;
}

