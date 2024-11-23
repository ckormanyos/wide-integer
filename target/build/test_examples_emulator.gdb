
# Connect to the target (e.g., OpenOCD or another GDB server).
target remote localhost:9999
monitor halt

# Ensure that the program is loaded.
load

# Set a breakpoint at the specified subroutine.
break app_benchmark_get_standalone_result

# Start or continue program execution.
continue

# Format and print the value of a variable.
printf "value 0x%X\n\n", app_benchmark_standalone_result

# Delete (all) breakpoint(s).
delete

# Perform a non-elegant quit of the GDB session.
quit
