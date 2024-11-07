# Verify if the executable is available
if [ ! -f "./executable_pthreads" ]; then
    echo "The executable is not available. Please, run the command: make compile_pthreads"
    exit 1
fi

if [ ! -f "./executable_openmp" ]; then
    echo "The executable is not available. Please, run the command: make compile_openmp"
    exit 1
fi

executable=(
    "./executable_pthreads"
    "./executable_openmp"
)

parameters=(
    "16"
    "17"
    "18"
)

for arg in "${parameters[@]}"
do
    for exe in "${executable[@]}"
    do
        echo -e "Running $exe with parameter $arg..."
        time $exe $arg
        echo -e "Done\n"
    done
done