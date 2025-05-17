#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

//remove if you want compiler optimizations
/*
#pragma GCC push_options
#pragma GCC optimize ("O0")
//*/
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void double_swap(double *a, double *b) {
    double temp = *a;
    *a = *b;
    *b = temp;
}

int countBits(int number){       
    return (int)log2(number)+1; 
} 

int gcd(int a, int b){
    int result = ((a < b) ? a : b);
    while (result > 0) {
        if (a % result == 0 && b % result == 0) {
            break;
        }
        result--;
    }
    return result;
}

// Function to find GCD and the modular inverse using Extended Euclidean Algorithm - chatGPT
int gcdExtended(int a, int m, int *x, int *y) {
    // Base case
    if (a == 0) {
        *x = 0;
        *y = 1;
        return m;
    }

    int x1, y1; // To store results of recursive call
    int gcd_ext = gcdExtended(m % a, a, &x1, &y1);

    // Update x and y using results of recursive call
    *x = y1 - (m / a) * x1;
    *y = x1;

    return gcd_ext;
}

// Function to calculate the modular multiplicative inverse - chatGPT
int modInverse(int a, int m) {
    int x, y;
    int gcd_ext = gcdExtended(a, m, &x, &y);

    // If GCD is not 1, then inverse does not exist
    if (gcd_ext != 1) {
        printf("Inverse doesn't exist\n");
        return -1;
    } else {
        // m might be negative, so ensure result is positive
        int result = (x % m + m) % m;
        return result;
    }
}

double relu(double x){
    return max(0.0,x);
}

//config - i hope it doesnt matter that i have used global variables. i can refactor it to use function parameters instead, this is just more convenient
//-------------------------------------------------------------------------
int num_neurons = 1000;
int cut_off = 1;
int *s1;
int *s2;
int num_runs = 100;
int repeat_time = 200;
double *inputs;
double **W;
int hidden_layer_neuron = 1000;
//-------------------------------------------------------------------------

void print_outputs(double *outputs){
    for (int i = 0; i < hidden_layer_neuron; i++){
        printf("%d, %f\n", i, outputs[i]);
    }
    printf("\n");
}

void compare_arrays(double *array1, double *array2){
    int i;
    for (i = 0; i < num_neurons; i++){
        if (array1[i] != array2[i]){
            printf("Error detected!\n");
            break;
        }
    }
    if (i != num_neurons){
        printf("Error, wrong number of results compared!\n");
    }
}

int *array_init(){
    //array init
    int *array = (int*)malloc(num_neurons * sizeof(int));

    for (int i = 0; i < num_neurons; i++){
        array[i] = i;
    }
    return array;
}

void init(){
    //s1 and s2 init
    s1 = (int*)malloc(num_neurons * sizeof(int));
    s2 = (int*)malloc(num_neurons * sizeof(int));

    int i = 3, r;
    int s1_counter = 0, s2_counter = 0;
    while (i <= num_neurons) {
        r = rand() % (i + 1);

        if (gcd(r, i) == 1){
            s1[s1_counter++] = r;
            s2[s2_counter++] = modInverse(r, i);
            i = i + 1;
        }
    }

    //init inputs
    inputs = (double*)malloc(num_neurons * sizeof(double));
    for(int i = 0; i < num_neurons; i++){
        inputs[i] = (rand() % (20 + 1)) - 10;
    }


    //init W array
    W = (double**)malloc(num_neurons * sizeof(double*));
    for (int i = 0; i < num_neurons; i++){
        W[i] = (double*)malloc(num_neurons * sizeof(double));
        for (int j = 0; j < num_neurons; j++){
            W[i][j] = (rand() % (20 + 1)) - 10;
        }
    }
}

int blakely(int a, int b, int n){
    int R = 0;
    int bit_length = countBits(a);
    for(int i = bit_length - 1; i >= 0; i--){
        int ai = (a >> i) & 1;
        R = 2 * R + ai * b;

        if (R >= n) {
            R = R - n;
        }

        if (R >= n){
            R = R - n;
        }
    }

    return R;
}

int modulo_masked(int i){
    int r1 = rand();
    int r2 = rand();
    int tmp = (r1 * s1[i-2] + r2 * (i+1)) % (i+1);
    
    int j = blakely(tmp, s2[i-2], i+1);
    //testing if it is the same as un-masked value
    /*
    int j2 = r1 % (i+1);
    if (j2 != j){
        printf("not equal %d\n", j);
    }
    //*/

    return j;
}

void Fisher_Yates_masked(int *array){
    int j;
    
    for(int i = num_neurons - 1; i > cut_off; i--){
        j = modulo_masked(i);
        swap(&array[i], &array[j]);
    }

    for(int i = cut_off; i > 0; i--){
        j = rand() % (i + 1);
        swap(&array[i], &array[j]);
    }
}

void Fisher_Yates(int *array){
    int j;
    
    for(int i = num_neurons - 1; i > 0; i--){
        j = rand() % (i + 1);
        swap(&array[i], &array[j]);
    }
}

void test_Blakely(){
    for(int i = 0; i < num_neurons; i++){
        for(int j = 0; j < num_neurons; j++){
            int pro = blakely(i, j, num_neurons);
            int pro2 = (i*j) % num_neurons;
            if (pro != pro2){
                printf("Blakely error: %d, %d", pro, pro2);
            }    
        }
    }
}

double computeOverhead(){
    
    int *array = array_init();
    clock_t start_time = clock();
    for(int i = 0; i < repeat_time; i++){
        Fisher_Yates(array);
    }
    clock_t end_time = clock();
    free(array);

    array = array_init();
    clock_t start_time_masked = clock();
    for(int i = 0; i < repeat_time; i++){
        Fisher_Yates_masked(array);
    }
    clock_t end_time_masked = clock();
    free(array);

    double t = (double)(end_time - start_time) / repeat_time;
    double t_masked = (double)(end_time_masked - start_time_masked) / repeat_time;
    double overhead = ((t_masked - t)/t)*100;

    return overhead;
}

void average_overhead(){
    double overhead = 0;
    for(int i = 1; i < num_runs; i++){
        overhead += computeOverhead();
    }
    overhead /= num_runs;
    printf("Average overhead: %f", overhead);
    return;
}

//Overhead compared to one layer computation
//---------------------------------------------------------------------------------------

double* one_layer(){
    double *outputs = (double*) calloc(num_neurons, sizeof(double));

    for (int i = 0; i < hidden_layer_neuron; i++){
        for (int j = 0; j < num_neurons; j++){
            outputs[i] += (W[i][j] * inputs[j]);
        }
        outputs[i] = relu(outputs[i]);
    }
    return outputs;
}

double* shuffled_one_layer(){
    double *outputs = (double*) calloc(num_neurons, sizeof(double));
    int *indices = (int*) malloc(num_neurons * sizeof(int));
    for (int i = 0; i < num_neurons; i++){
        indices[i] = i;
    }
     
    //this changes array in-place;
    Fisher_Yates_masked(indices);

    for (int i = 0; i < hidden_layer_neuron; i++){
        
        for (int j = 0; j < num_neurons; j++){
            outputs[i] += (W[i][indices[j]] * inputs[indices[j]]);
        }
        outputs[i] = relu(outputs[i]);
    }
    return outputs;
}

double compute_overhead_over_layer(){
    double **outputs1 = (double**)malloc(repeat_time * sizeof(double*));
    clock_t start_time = clock();
    for(int i = 0; i < repeat_time; i++){
        outputs1[i] = one_layer();
    }
    clock_t end_time = clock();

    double **outputs2 = (double**)malloc(repeat_time * sizeof(double*));
    clock_t start_time_masked = clock();
    for(int i = 0; i < repeat_time; i++){
        outputs2[i] = shuffled_one_layer();
    }
    clock_t end_time_masked = clock();

    //check if the arrays are matching
    for (int i = 0; i < repeat_time; i++){
        compare_arrays(outputs1[i], outputs2[i]);
    }

    double t = (double)(end_time - start_time) / repeat_time;
    double t_masked = (double)(end_time_masked - start_time_masked) / repeat_time;
    double overhead = ((t_masked - t)/t)*100;

    for(int i = 0; i < repeat_time; i++){
        free(outputs1[i]);
        free(outputs2[i]);
    }
    free(outputs1);
    free(outputs2);

    return overhead;
}

double average_overhead_layer(){
    double overhead = 0;
    for(int i = 1; i < num_runs; i++){
        overhead += compute_overhead_over_layer();
    }
    overhead /= num_runs;
    printf("Average overhead over layer: %f", overhead);
    return overhead;
}

//Overhead over original shuffling with one layer computation
//------------------------------------------------------------------------------------------------------------------

double* Fisher_shuffled_one_layer(){
    double *outputs = (double*) calloc(num_neurons, sizeof(double));
    int *indices = (int*) malloc(num_neurons * sizeof(int));
    for (int i = 0; i < num_neurons; i++){
        indices[i] = i;
    }

    //this changes the array in-place
    Fisher_Yates(indices);

    for (int i = 0; i < hidden_layer_neuron; i++){
        
        for (int j = 0; j < num_neurons; j++){
            outputs[i] += (W[i][indices[j]] * inputs[indices[j]]);
        }
        outputs[i] = relu(outputs[i]);
    }
    return outputs;
}

double compute_overhead_over_original_layer_with_one_layer_computation(){
    double **outputs1 = (double**)malloc(repeat_time * sizeof(double*));
    clock_t start_time = clock();
    for(int i = 0; i < repeat_time; i++){
        outputs1[i] = Fisher_shuffled_one_layer();
    }
    clock_t end_time = clock();

    double **outputs2 = (double**)malloc(repeat_time * sizeof(double*));
    clock_t start_time_masked = clock();
    for(int i = 0; i < repeat_time; i++){
        outputs2[i] = shuffled_one_layer();
    }
    clock_t end_time_masked = clock();

    //check if the arrays are matching
    for (int i = 0; i < repeat_time; i++){
        compare_arrays(outputs1[i], outputs2[i]);
    }

    double t = (double)(end_time - start_time) / repeat_time;
    double t_masked = (double)(end_time_masked - start_time_masked) / repeat_time;
    double overhead = ((t_masked - t)/t)*100;

    for(int i = 0; i < repeat_time; i++){
        free(outputs1[i]);
        free(outputs2[i]);
    }
    free(outputs1);
    free(outputs2);

    return overhead;
}

double average_overhead_over_original_layer_with_one_layer_computation(){
    double overhead = 0;
    for(int i = 1; i < num_runs; i++){
        overhead += compute_overhead_over_original_layer_with_one_layer_computation();
    }
    overhead /= num_runs;
    printf("Average overhead over layer: %f\n", overhead);
    return overhead;
}


void print_config(){
    printf("num_neurons: %d\n", num_neurons);
    printf("cut_off: %d\n", cut_off);
    printf("num_runs: %d\n", num_runs);
    printf("repeat_time: %d\n", repeat_time);
    printf("hidden_layer_neuron: %d\n", hidden_layer_neuron);
}

//if you want to plot higher number of neurons, make sure you have enought s1 and s2 calculations done (array lenght). it is calculated during init function using the original num_neurons value
void get_plot_data(){
    FILE *fptr;
    fptr = fopen("results.txt", "w");
    fprintf(fptr, "x y\n");

    for (int i = 50; i <= 1000; i+=50){
        num_neurons = i;
        hidden_layer_neuron = i;
        fprintf(fptr, "%d %lf\n", i, average_overhead_over_original_layer_with_one_layer_computation());
    }
    fclose(fptr);
}

int main(){
    srand(time(NULL));
    init();
    print_config();
    //test_Blakely();
    
    //average_overhead();
    
    //average_overhead_layer();
    
    //average_overhead_over_original_layer_with_one_layer_computation();
    
    get_plot_data();


    for(int i = 0; i < num_neurons; i++){
        free(W[i]);
    }
    free(W);
    free(inputs);
    free(s1);
    free(s2);
    return 0;
}

//remove if you want compiler optimizations
//#pragma GCC pop_options