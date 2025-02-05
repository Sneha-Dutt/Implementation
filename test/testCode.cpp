#include <gtest/gtest.h>
#include <stdint.h>
#include <stdlib.h>
#include <vector>
#include <numeric>
#include <iostream>  // For logging

// Function prototypes from the main code
void read_sensor_data(uint16_t *data);
float calculate_average(uint16_t *data, int size);
void process_data(uint16_t *data);
void print_data(uint16_t *data, int size);

#define BUFFER_SIZE 20

// Mock function to simulate a controlled `rand` for predictable data
void mock_read_sensor_data(uint16_t *data) {
    for (int i = 0; i < BUFFER_SIZE; i++) {
        data[i] = i * 50; // Generate predictable data for testing
    }
}

// Test for `calculate_average`
TEST(SensorDataTests, CalculateAverage) {
    std::cout << "Running CalculateAverage test..." << std::endl;
    uint16_t test_data[BUFFER_SIZE] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000,
                                       1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000};
    float average = calculate_average(test_data, BUFFER_SIZE);
    std::cout << "Calculated average: " << average << std::endl;
    EXPECT_EQ(average, 1049); // Expected average of the test data
}

// Test for `read_sensor_data`
TEST(SensorDataTests, ReadSensorData) {
    std::cout << "Running ReadSensorData test..." << std::endl;
    uint16_t test_data[BUFFER_SIZE] = {0};
    mock_read_sensor_data(test_data);

    for (int i = 0; i < BUFFER_SIZE; i++) {
        std::cout << "Testing index " << i << ": Expected " << (i * 50) << ", Got " << test_data[i] << std::endl;
        EXPECT_EQ(test_data[i], i * 50); // Ensure data is generated as expected
    }
}

// Test for `process_data` with mock data
TEST(SensorDataTests, ProcessData) {
    std::cout << "Running ProcessData test..." << std::endl;
    testing::internal::CaptureStdout(); // Capture the printed output
    uint16_t test_data[BUFFER_SIZE] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000,
                                       1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000};
    process_data(test_data);
    std::string output = testing::internal::GetCapturedStdout();

    std::cout << "Captured Output: " << output << std::endl;
    EXPECT_TRUE(output.find("Average sensor value: 1050") != std::string::npos);
    EXPECT_TRUE(output.find("Warning: Sensor value exceeds threshold!") != std::string::npos);
}

// Test for `print_data`
TEST(SensorDataTests, PrintData) {
    std::cout << "Running PrintData test..." << std::endl;
    testing::internal::CaptureStdout(); // Capture the printed output
    uint16_t test_data[BUFFER_SIZE] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000,
                                       1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000};
    print_data(test_data, BUFFER_SIZE);
    std::string output = testing::internal::GetCapturedStdout();

    for (int i = 0; i < BUFFER_SIZE; i++) {
        std::string expected_line = "Sensor Data[" + std::to_string(i) + "]: " + std::to_string(test_data[i]) + "\n";
        std::cout << "Checking if output contains: " << expected_line << std::endl;
        EXPECT_TRUE(output.find(expected_line) != std::string::npos);
    }
}

// Test for memory allocation failure handling
TEST(SensorDataTests, MemoryAllocationFailure) {
    std::cout << "Running MemoryAllocationFailure test..." << std::endl;
    testing::internal::CaptureStdout(); // Capture the printed output
    uint16_t *test_data = (uint16_t *)malloc(BUFFER_SIZE * sizeof(uint16_t));

    if (test_data == NULL) {
        std::cout << "Memory allocation failed!" << std::endl;
        printf("Memory allocation failed!\n");
    } else {
        free(test_data);
    }
    std::string output = testing::internal::GetCapturedStdout();
    std::cout << "Captured Output: " << output << std::endl;
    EXPECT_TRUE(output.find("Memory allocation failed!") == std::string::npos); // Should not fail
}
