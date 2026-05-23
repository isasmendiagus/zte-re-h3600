// module: mt7915.ko
// function: pkt_alloc_fail_handle @ 0xc628c
// size: 52 bytes
//

undefined4 pkt_alloc_fail_handle(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = asic_get_packet_type();
  if (iVar1 == 6) {
    asic_txdone_handle(param_1,param_2,param_3);
  }
  return 0;
}

