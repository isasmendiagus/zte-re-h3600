// module: mt7915.ko
// function: MATDBEntryAlloc @ 0x79b68
// size: 40 bytes
//

undefined4 MATDBEntryAlloc(undefined4 param_1,undefined4 param_2)

{
  undefined4 local_c [2];
  
  local_c[0] = 0;
  os_alloc_mem(0,local_c,param_2);
  return local_c[0];
}

