// module: mt7915.ko
// function: CmdMemDumpRsp @ 0x1ac048
// size: 20 bytes
//

void CmdMemDumpRsp(int param_1,int param_2)

{
  os_move_mem((void *)**(undefined4 **)(param_1 + 0xc),(void *)(param_2 + 4),0x40);
  return;
}

