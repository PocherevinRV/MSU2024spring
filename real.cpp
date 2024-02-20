#include <iostream>
#include <cmath>

void print_float(float *);
void print_double(double *);
//void print_long_double(long double *);
void binary_print(int, int, int);

void binary_print(int num, int delim1, int delim2)
{
	unsigned int mask = 1<<31;
	for (int i = 0; i <= 31; i++, mask >>= 1)
	{
		if (i == delim1 || i == delim2) std::cout << " | ";
		if (num & mask) std::cout << "1"; else std::cout << "0";
		//std::cout << mask << std::endl;
	} 
}

void print_float(float *num)
{
	int *int_num = (int *) num;
	std::cout << std::endl << "sign|exponent|mantisse (significand)" << std::endl;
	binary_print(int_num[0], 1, 9);
	std::cout << std::endl;
}

void print_double(double *num)
{
	int *int_num = (int *) num;
	std::cout << std::endl << "sign| exponent  | mantisse (significand)" << std::endl;
	binary_print(int_num[1], 1, 12);
	binary_print(int_num[0], 100, 100);
	std::cout << std::endl;
}

/*
void print_long_double(long double * num)
{
	int *int_num = (int *) num;
	std::cout << std::endl << "sign| exponent  | mantisse (significand)" << std::endl;
	binary_print(int_num[2], 1, 100);
	std::cout << "~";
	binary_print(int_num[1], 1, 100);
	std::cout << "~";
	binary_print(int_num[0], 100, 100);
	std::cout << "~";
	binary_print(int_num[3], 100, 100);
	std::cout << std::endl;

} */

int main(void)
{
	float *num1 = new float[1];
	double *num2 = new double[1];
	long double *num3 = new long double[1];
        std::cout << "Enter real number for float:" << std::endl;
	std::cin >> num1[0];
	print_float(num1);

	std::cout << "Machine epsilon for float:" << std::endl;
	num1[0] = std::pow(2, -24);
	print_float(num1);

	std::cout << std::endl;
	std::cout << "Enter real number for double:" << std::endl;
	std::cin >> num2[0];
	print_double(num2);

	std::cout << "Machine epsilon for double:" << std::endl;
	num2[0] = std::pow(2, -53);
	print_double(num2);

	/*
	std::cout << std::endl;
	std::cout << "Enter real number for double:" << std::endl;
	std::cin >> num3[0];
	print_long_double(num3);

	std::cout << "Machine epsilon for double:" << std::endl;
	num3[0] = std::pow(2, -53);
	print_long_double(num3);    */
	return 0;
} 