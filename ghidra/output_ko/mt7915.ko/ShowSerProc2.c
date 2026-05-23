// module: mt7915.ko
// function: ShowSerProc2 @ 0xedb88
// size: 40 bytes
//

undefined4 ShowSerProc2(undefined4 param_1)

{
  ShowSerProc();
  CmdExtSER(param_1,0,0,0);
  return 1;
}

