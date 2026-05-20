// module: mt7915.ko
// function: log_time_begin @ 0x147730
// size: 48 bytes
//

void log_time_begin(int param_1,int param_2)

{
  *(char *)(param_2 + 0x11) = (char)param_1;
  if (param_1 == 0) {
    *(undefined4 *)(param_2 + 8) = jiffies;
    return;
  }
  if (param_1 != 1) {
    return;
  }
  do_gettimeofday(param_2);
  return;
}

