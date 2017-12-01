#include <iostream>

int main(int argc, const char *argv[]) {
    std::string numbers;
    getline(std::cin, numbers);

    long sum = 0;
    for (int i = 0; i < numbers.length(); i++) {
        if (numbers[i] == numbers[(i + 1) % numbers.length()]) {
            sum += numbers[i] - '0';
        }
    }

    std::cout << sum << std::endl;

    long sum2 = 0;
    for (int i = 0; i < numbers.length(); i++) {
        if (numbers[i] == numbers[(i + numbers.length() / 2) % numbers.length()]) {
            sum2 += numbers[i] - '0';
        }
    }
    std::cout << sum2 << std::endl;
}