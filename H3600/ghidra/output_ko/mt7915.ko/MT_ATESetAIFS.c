// module: mt7915.ko
// function: MT_ATESetAIFS @ 0x27e4c4
// size: 96 bytes
//

undefined4 MT_ATESetAIFS(undefined4 param_1,uint param_2)

{
  if (2 < DebugLevel) {
    printk("%s: Value:%x\n","MT_ATESetAIFS",param_2 & 0xf);
  }
  AsicSetWmmParam(param_1,0,0,1,param_2 & 0xf);
  return 0;
}

