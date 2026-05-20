// module: mt7915.ko
// function: ap_join_peer_response_matched @ 0x4b028
// size: 32 bytes
//

undefined4
ap_join_peer_response_matched
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  printk(&_LC0,0xe8,param_3,param_4,param_4);
  dump_stack();
  return 0;
}

