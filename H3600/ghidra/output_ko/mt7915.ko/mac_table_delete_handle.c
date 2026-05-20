// module: mt7915.ko
// function: mac_table_delete_handle @ 0xc4340
// size: 24 bytes
//

undefined4
mac_table_delete_handle(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  MacTableDeleteEntry(param_1,**(undefined2 **)(param_2 + 4),*(undefined2 **)(param_2 + 4) + 1,
                      param_4,param_4);
  return 0;
}

