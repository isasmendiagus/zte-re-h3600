// module: mt7915.ko
// function: Set_Key1_Proc @ 0x59ee0
// size: 44 bytes
//

void Set_Key1_Proc(undefined4 param_1,char *param_2)

{
  size_t sVar1;
  
  sVar1 = strlen(param_2);
  Set_Wep_Key_Proc(param_1,param_2,sVar1,0);
  return;
}

