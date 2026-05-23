// module: mt7915.ko
// function: rrm_set_handle_nr_req_flag @ 0x221848
// size: 76 bytes
//

undefined4 rrm_set_handle_nr_req_flag(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = DebugLevel;
  (&DAT_0036daa0)[param_1] = param_2 != 0;
  if (2 < iVar1) {
    printk("%s, HandleNRReqbyUplayer(%d)!\n","rrm_set_handle_nr_req_flag",param_2 != 0,iVar1,param_4
          );
  }
  return 0;
}

