// module: mt7915.ko
// function: a4_proxy_delete @ 0x9f3cc
// size: 52 bytes
//

void a4_proxy_delete(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = a4_get_entry_count();
  if (iVar1 == 0) {
    return;
  }
  RoutingTabSetOneFree(param_1,param_2,param_3,1);
  return;
}

