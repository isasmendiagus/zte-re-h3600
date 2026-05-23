// module: mt7915.ko
// function: WscAppendV2SubItem @ 0x201524
// size: 152 bytes
//

bool WscAppendV2SubItem(undefined1 param_1,void *param_2,size_t param_3,void *param_4,
                       undefined1 *param_5)

{
  undefined1 *puVar1;
  bool bVar2;
  undefined1 *local_1c [2];
  
  local_1c[0] = (undefined1 *)0x0;
  os_alloc_mem(0,local_1c,param_3 + 10);
  bVar2 = local_1c[0] != (undefined1 *)0x0;
  if (bVar2) {
    *local_1c[0] = param_1;
    local_1c[0][1] = (char)param_3;
    memmove(local_1c[0] + 2,param_2,param_3);
    puVar1 = local_1c[0];
    *param_5 = (char)(param_3 + 2);
    memmove(param_4,local_1c[0],param_3 + 2 & 0xff);
    os_free_mem(puVar1);
  }
  return bVar2;
}

