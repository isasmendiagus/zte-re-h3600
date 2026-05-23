// module: mt7915.ko
// function: Set_Map_Channel_En_Proc @ 0xd8e24
// size: 44 bytes
//

undefined4 Set_Map_Channel_En_Proc(int param_1,undefined4 param_2)

{
  undefined1 uVar1;
  
  uVar1 = os_str_tol(param_2,0,10);
  *(undefined1 *)(param_1 + 0xa7cbfc) = uVar1;
  return 1;
}

