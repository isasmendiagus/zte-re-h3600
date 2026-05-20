// module: mt7915.ko
// function: ap_join_peer_response_updated @ 0x4b008
// size: 32 bytes
//

undefined4
ap_join_peer_response_updated
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  printk(&_LC0,0xf0,param_3,param_4,param_4);
  dump_stack();
  return 0;
}

