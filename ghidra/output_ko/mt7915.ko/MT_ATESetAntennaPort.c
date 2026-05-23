// module: mt7915.ko
// function: MT_ATESetAntennaPort @ 0x27d4bc
// size: 108 bytes
//

void MT_ATESetAntennaPort
               (undefined4 param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4)

{
  if (2 < DebugLevel) {
    printk("%s: RfModeMask:%d RfPortMask:%d AntPortMask:%d\n","MT_ATESetAntennaPort",param_2,param_3
           ,param_4);
  }
  MtCmdSetAntennaPort(param_1,param_2,param_3,param_4);
  return;
}

