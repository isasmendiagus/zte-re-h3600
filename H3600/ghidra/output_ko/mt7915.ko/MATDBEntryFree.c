// module: mt7915.ko
// function: MATDBEntryFree @ 0x79b54
// size: 20 bytes
//

undefined4 MATDBEntryFree(undefined4 param_1,undefined4 param_2)

{
  os_free_mem(param_2);
  return 1;
}

