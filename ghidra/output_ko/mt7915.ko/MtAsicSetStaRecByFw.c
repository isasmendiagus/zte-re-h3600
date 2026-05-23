// module: mt7915.ko
// function: MtAsicSetStaRecByFw @ 0x197fa8
// size: 68 bytes
//

void MtAsicSetStaRecByFw(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4
                        )

{
  undefined1 auStack_e8 [204];
  
  memcpy(auStack_e8,&stack0x00000000,200);
  CmdExtStaRecUpdate(param_1,param_2,param_3,param_4);
  return;
}

