// module: mt7915.ko
// function: a4_proxy_lookup @ 0x9f464
// size: 88 bytes
//

undefined4
a4_proxy_lookup(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5,undefined2 *param_6)

{
  int iVar1;
  undefined4 uVar2;
  
  *param_6 = 0;
  iVar1 = a4_get_entry_count();
  uVar2 = 0;
  if (iVar1 != 0) {
    iVar1 = RoutingTabLookup(param_1,param_2,param_3,param_4,param_6);
    uVar2 = 0;
    if (iVar1 != 0) {
      uVar2 = 1;
    }
  }
  return uVar2;
}

