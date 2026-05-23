// module: mt7915.ko
// function: Set_StaRecBfRead @ 0xe6484
// size: 48 bytes
//

bool Set_StaRecBfRead(undefined4 param_1,undefined4 param_2)

{
  undefined2 uVar1;
  int iVar2;
  
  uVar1 = os_str_tol(param_2,0,10);
  iVar2 = CmdETxBfStaRecRead(param_1,uVar1);
  return iVar2 == 0;
}

