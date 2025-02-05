#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define BUFFER_SIZE 20

void read_sensor_data(uint16_t *data) {
    for (int i = 0; i < BUFFER_SIZE; i++) { 
        data[i] = rand() % 1024; // Simulating sensor data in the range [0, 1023]
    }
}

float calculate_average(uint16_t *data, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += data[i];
    }
    printf("\n");
    return sum / size;
}

void print_data(uint16_t *data, int size) {
    for (int i = 0; i < size; i++) {
        printf("Sensor Data[%d]: %d\n", i, data[i]);
    }
}

void process_data(uint16_t *data) {
    float avg = calculate_average(data, BUFFER_SIZE);
    
    if (avg > 512) {
        printf("Warning: Sensor value exceeds threshold!\n");
    } else {
        printf("Sensor value is within the safe range.\n");
    }
}

int main() { 
    uint16_t *sensor_data = (uint16_t *)malloc(BUFFER_SIZE * sizeof(uint16_t));
    if (sensor_data == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    
    read_sensor_data(sensor_data);
    process_data(sensor_data);
    print_data(sensor_data, BUFFER_SIZE);   

    free(sensor_data); // Properly release allocated memory
  
    return 0; // Indicate successful execution
}
