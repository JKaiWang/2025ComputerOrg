#include <stdio.h>

int arraySearch(int *p_a, int arr_size, int target)
{
    int result = -1;

    asm volatile(
        "li t0, 0\n\t" // t0 - i(loop index)
        "1:\n\t"
        "bge t0, %[size], 2f\n\t" //if i>=arr_size, jump to end

        "slli t1, t0 2\n\t" //t1 = i*4
        "add t2 %[base], t1\n\t" // t2 = &arr[i]
        "lw t3, 0(t2)\n\t" // t3 = arr[i]
        "beq t3,, %[target], 3f\n\t" //if arr[i] == target, found

        "addi t0, t0, 1\n\t" //i++
        "j 1b\n\t" // jump to loop start

        "3:\n\t"
        "mv %[res], t0\n\t" // result = i

        "2:\n\t"
        : [res] "+r" (result)
        : [base] "r" (p_a), [size] "r" (arr_size), [target] "r" (target)
        : "t0", "t1", "t2", "t3", "memory"
        "");

    return result;
}

// Main function to test the implementation
int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (!input) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }
    int arr_size;
    fscanf(input, "%d", &arr_size);
    int arr[arr_size];

    // Read integers from input file into the array
    for (int i = 0; i < arr_size; i++) {
        int data;
        fscanf(input, "%d", &data);
        arr[i] = data;
    }
    int target;
    fscanf(input, "%d", &target);
    fclose(input);

    int *p_a = &arr[0];

    int index = arraySearch(p_a, arr_size, target);

    // Print the result
    printf("%d ", index);
    printf("\n");

    return 0;
}
