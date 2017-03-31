nclude <iostream>
#include <string>
using namespace std;

float GetUserInput()
{
    cout << "Please enter an integer: ";
    float nValue;
    cin >> nValue;
    return nValue;
}

inline unsigned int AsInt(float f) {
    return *(unsigned int *)&f;
}

inline float AsFloat(unsigned int i) {
    return *(float*)&i;
}

//Negate float
float NegateFloat(float f) {
    return AsFloat(AsInt(f)^0x80000000);
}


const unsigned int OneAsInt = 0x3F800000;//1.0f as int
const float scaleUp = float(0x00800000);//2^23
const float scaleDown = 1.0f/scaleUp;
//Log 2 (float) Approximation 
float Log2(float x) {
    return float (AsInt(x)-OneAsInt)*scaleDown;
}

//2 ^ (float) Approximation 
float Exp2(float x) {
    return AsFloat(int(x*scaleUp)+OneAsInt);
}

//Lose Approximation for power function
//Combinationm of Log2 and Exp2

//x^p = 2^[p log2 x]
float Pow(float x, float p) {
    return AsFloat(int(p*(AsInt(x)-OneAsInt))+OneAsInt);
}

//Domain does not include negative values
float Sqrt(float x) {
    return AsFloat((AsInt(x)>>1)+(OneAsInt>>1));
}

//Inverse Square Root (1/sqrt(x))
float Inverse_sqrt(float x){
    float xhalf = 0.5F;
    int i = *(int*)&x;
    i = 0x5f375a86-(i>>1);
    x = *(float*)&i;
    x = x*(1.5f-xhalf*x*x);
    return x;
}



void PrintResult(int nResult)
{
    cout << "Your result is: " << nResult << "\n" << endl;
}

void PrintFloatResult(float nResult)
{
    cout << "Your result is: " << nResult << "\n" << endl;
}

int main()
{
    float x = GetUserInput();

    cout << "Negate " << x << endl;
    //-(x)
    float negatedF = NegateFloat(x);
    PrintFloatResult(negatedF);

    cout << "Log Base two of " << x << endl;
    // log2 (x)
    int numFacOfTwo = Log2(x);
    PrintResult(numFacOfTwo);

    cout << "2 Raised to the  " << x << "power" << endl;
    //2 ^ (x)  
    float exp = Exp2(x);
    PrintFloatResult(exp);

    cout << x << " rasised to the 2.0" << endl;
    //x^p = 2^[p log2 x]
    float pow = Pow(x, 2.0);
    PrintFloatResult(pow);

    cout << "Suare Root of " << x << endl;
    //sqrt (x)
    float root =  Sqrt(x);
    PrintFloatResult(root);

    cout << "Inverse Square Root of two of " << x << endl;
    // 1/sqrt(x)
    int result = Inverse_sqrt(x);
    PrintResult(result);


    float y = GetUserInput();
}
