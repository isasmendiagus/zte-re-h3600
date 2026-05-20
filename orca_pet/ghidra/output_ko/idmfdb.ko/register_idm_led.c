// module: idmfdb.ko
// function: register_idm_led @ 0x12880
// size: 140 bytes
//

undefined4 register_idm_led(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  iVar1 = param_1 * 0x40;
  *(int *)(&led_handle + param_1 * 0x40) = param_1;
  *(undefined4 *)(&DAT_00018020 + iVar1) = param_2;
  (&DAT_0001801c)[iVar1] = 1;
  *(undefined4 *)(&DAT_00018024 + iVar1) = param_3;
  *(undefined4 *)(&DAT_00018054 + iVar1) = param_4;
  (&DAT_0001804c)[param_1 * 0x10] = 0;
  init_timer_key(&DAT_00018030 + iVar1,0,0,0);
  iVar2 = jiffies;
  *(code **)(&DAT_00018040 + iVar1) = idm_led_timer_handle;
  *(undefined1 **)(&DAT_00018044 + iVar1) = &led_handle + iVar1;
  mod_timer(&DAT_00018030 + iVar1,iVar2 + 500);
  create_led_proc_file(&led_handle + iVar1);
  return 0;
}

