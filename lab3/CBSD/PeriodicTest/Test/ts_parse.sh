args_gen()
{
  N=0
  while read C D T;
   do
    PRIO=$((99-N))
    WCET=$((C*1000))
    PERIOD=$((T*1000))
    echo -n " -C $WCET"
    echo -n " -p $PERIOD"
    echo -n " -P $PRIO"
    N=$((N+1))
   done
#  echo -n " -R 1061779"
  echo " -n $N"
}

ARGS=$(args_gen < $1)

echo "./periodic_thread $ARGS"
sudo taskset 1 ./periodic_thread $ARGS
