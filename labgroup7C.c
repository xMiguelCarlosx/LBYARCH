#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void compute_acceleration(float *inputs, int *outputs, int count);

float random_float(float min, float max)
{
    return min + ((float)rand() / RAND_MAX) * (max - min);
}

void generate_random_input(float *input, int count)
{
    for (int i = 0; i < count; ++i)
    {
        float Vi = random_float(0, 200);  // km/h
        float Vf = random_float(Vi, 300); // ensure Vf >= Vi
        float T = random_float(1, 20);    // seconds, avoid division by 0
        input[i * 3 + 0] = Vi;
        input[i * 3 + 1] = Vf;
        input[i * 3 + 2] = T;

        if (i < 5 || count <= 5)
        {
            printf("Car %d: Vi = %.2f km/h, Vf = %.2f km/h, T = %.2f s\n",
                   i + 1, Vi, Vf, T);
        }
        else if (i == 5)
        {
            printf("...showing only first 5 cars...\n");
        }
    }
}

void get_manual_input(float *input, int count)
{
    printf("\nEnter Vi (km/h), Vf (km/h), and T (s) for each car:\n");
    for (int i = 0; i < count; ++i)
    {
        printf("Car %d: ", i + 1);
        scanf("%f %f %f", &input[i * 3], &input[i * 3 + 1], &input[i * 3 + 2]);
    }
}
int main()
{
    int count, mode;
    const int runs = 30;
    srand((unsigned int)time(NULL));

    printf("Choose input mode:\n");
    printf("1 - Manual Input\n");
    printf("2 - Auto Generate Input\n");
    printf("3 - Time Performance for Sizes 10,100,1000,10000\n");
    printf("Enter choice: ");
    scanf("%d", &mode);

    if (mode == 1 || mode == 2)
    {
        printf("Enter number of cars: ");
        scanf("%d", &count);

        if (count <= 0)
        {
            printf("Invalid number of cars.\n");
            return 1;
        }

        float *input = (float *)malloc(sizeof(float) * count * 3);
        int *output = (int *)malloc(sizeof(int) * count);

        if (!input || !output)
        {
            printf("Memory allocation failed.\n");
            return 1;
        }

        if (mode == 1)
        {
            get_manual_input(input, count);
        }
        else
        {
            printf("\nAuto-generated input values (Vi, Vf, T):\n");
            generate_random_input(input, count);
        }

        clock_t start = clock();
        for (int i = 0; i < runs; ++i)
        {
            compute_acceleration(input, output, count);
        }
        clock_t end = clock();

        double avg_time = (double)(end - start) / CLOCKS_PER_SEC / runs;

        printf("\nAverage execution time over %d runs: %.9f seconds\n", runs, avg_time);

        // Output
        int limit;
        if (count < 5)
        {
            limit = count;
        }
        else
        {
            limit = 5;
        }
        printf("\nOutput (first %d cars):\n", limit);
        for (int i = 0; i < limit; ++i)
        {
            printf("Car %d: %d m/s^2\n", i + 1, output[i]);
        }

        free(input);
        free(output);
    }

    else if (mode == 3)
    {
        int sizes[] = {10, 100, 1000, 10000};

        for (int s = 0; s < 4; ++s)
        {
            count = sizes[s];
            printf("\n--- Testing with %d cars ---\n", count);

            float *input = (float *)malloc(sizeof(float) * count * 3);
            int *output = (int *)malloc(sizeof(int) * count);

            generate_random_input(input, count);

            clock_t start = clock();
            for (int i = 0; i < runs; ++i)
            {
                compute_acceleration(input, output, count);
            }
            clock_t end = clock();

            double avg_time = (double)(end - start) / CLOCKS_PER_SEC / runs;
            printf("Average execution time over %d runs: %.9f seconds\n", runs, avg_time);

            int limit;
            if (count < 5)
            {
                limit = count;
            }
            else
            {
                limit = 5;
            }

            printf("\nOutput (first %d cars):\n", limit);
            for (int i = 0; i < limit; ++i)
            {
                printf("Car %d: %d m/s^2\n", i + 1, output[i]);
            }

            free(input);
            free(output);
        }
    }

    else
    {
        printf("Invalid mode selected.\n");
        return 1;
    }

    return 0;
}
