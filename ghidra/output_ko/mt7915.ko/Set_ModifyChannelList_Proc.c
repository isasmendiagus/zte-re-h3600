// module: mt7915.ko
// function: Set_ModifyChannelList_Proc @ 0x2372cc
// size: 216 bytes
//

undefined4 Set_ModifyChannelList_Proc(undefined4 param_1,undefined4 param_2)

{
  undefined4 local_5a;
  undefined4 local_56;
  undefined4 local_52;
  undefined4 local_4e;
  undefined4 local_4a;
  undefined4 local_46;
  undefined4 local_42;
  undefined4 local_3e;
  undefined4 local_3a;
  undefined4 local_36;
  undefined4 local_32;
  undefined4 local_2e;
  undefined2 local_2a;
  
  local_3e = 0x680064;
  local_52 = 0x680064;
  local_46 = 0x80007c;
  local_4e = 0x70006c;
  local_2e = 0x880084;
  local_4a = 0x780074;
  local_42 = 0x880084;
  local_56 = 0x80007c;
  local_3a = 0x70006c;
  local_36 = 0x780074;
  local_32 = 0x80007c;
  local_2a = 0x8c;
  local_5a = 0x780074;
  simple_strtol(param_2,0,10);
  ZeroWait_DFS_Initialize_Candidate_List(param_1,4,&local_5a,10,&local_52,0xb,&local_3e);
  return 1;
}

