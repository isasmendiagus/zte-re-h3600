// module: mt7915.ko
// function: Set_BndStrg_Init @ 0x9d8a8
// size: 68 bytes
//

undefined4 Set_BndStrg_Init(int param_1)

{
  if (0 < DebugLevel) {
    printk("%s,name=%s\n","Set_BndStrg_Init",*(undefined4 *)(param_1 + 4));
  }
  BndStrg_Init(param_1);
  return 1;
}

