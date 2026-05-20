// module: mt7915.ko
// function: Set_DfsChannelShow_Proc @ 0x230808
// size: 84 bytes
//

undefined4 Set_DfsChannelShow_Proc(int param_1,undefined4 param_2)

{
  os_str_tol(param_2,0,10);
  if (0 < DebugLevel) {
    printk("Current 5G channel, Band0Ch: %d, Band1Ch: %d\n",*(undefined1 *)(param_1 + 0x795130),
           *(undefined1 *)(param_1 + 0x795131));
  }
  return 1;
}

