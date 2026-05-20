// module: mt7915.ko
// function: a4_proxy_maintain @ 0x9f5c0
// size: 40 bytes
//

void a4_proxy_maintain(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 extraout_r2;
  
  iVar1 = a4_get_entry_count();
  if (iVar1 == 0) {
    return;
  }
  RoutingTabMaintain(param_1,param_2,extraout_r2,param_4);
  return;
}

