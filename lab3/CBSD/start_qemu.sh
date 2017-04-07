qemu-system-x86_64 -initrd periodic_test.gz  -machine pc,accel=kvm -smp cpus=1 -kernel bzImage -append "sleeptime=1" &
PID=$!
echo PID: $PID
echo vCPU: $((PID+2))

