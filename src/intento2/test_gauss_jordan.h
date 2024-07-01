#ifndef TEST_GAUSS_JORDAN_H_INCLUDED
#define TEST_GAUSS_JORDAN_H_INCLUDED
/*class test_gauss_jordan {
public:
    //void exec();
    //test_gauss_jordan();

private:
    //void gauss_jordan_Solucion(std::vector<std::vector<double>>& matrix);
    //void solveSystem(const std::string& input);
};*/
void gauss_jordan_Solucion(std::vector<std::vector<double>>& matrix);
void solveSystem(const std::vector<double>& coefficients);
#include "test_gauss_jordan.cpp"


#endif // TEST_GAUSS_JORDAN_H_INCLUDED
