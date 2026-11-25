#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>   // setw, left : 출력 줄 맞춤용

using namespace std;


// ============================================================
// 1. 벡터 출력 함수
// ============================================================
void printVector(const vector<double>& values)
{
    cout << "[ ";

    for (double value : values)
    {
        cout << value << " ";
    }

    cout << "]" << endl;
}


// ============================================================
// 2. 두 벡터의 내적(dot product)을 계산하는 함수
// ============================================================
//
// a = [a1, a2, a3]
// b = [b1, b2, b3]
//
// dotProduct(a, b)
// = a1*b1 + a2*b2 + a3*b3
//
// ============================================================
double dotProduct(const vector<double>& a, const vector<double>& b){
    double result = 0.0;

    // TODO1
    //두 벡터의 크기가 다르면 내적을 구할 수 없으므로 에러 메시지 출력
    if (a.size() != b.size()) //크기가 다를때
    {
        cerr << "[Error] dotProduct : vector size mismatch (a.size() = "
             << a.size() << ", b.size() = " << b.size() << ")" << endl;
        return result;
    }

    // 같은 위치의 원소끼리 곱해서 누적
    for (size_t i = 0; i < a.size(); i++)
    {
        result += a[i] * b[i];
    }

    return result;
}


// ============================================================
// 3. Layer 추상 클래스
// ============================================================
//
// Dense, ReLU, Sigmoid 등
// 모든 Layer가 공통적으로 가져야 하는 기능을 정의
//
// ============================================================
class Layer
{
public:
    // 입력 벡터를 받아 출력 벡터를 반환
    virtual vector<double> forward(const vector<double>& input) = 0;

    // Layer 이름 반환
    virtual string getName() const = 0;

    // 부모 포인터를 이용해서 자식 객체를 삭제하기 위해 가상 소멸자 선언
    virtual ~Layer(){ }
};



// 4. Dense Layer
// output = W * input + bias
// 하나의 뉴런:  y = w1*x1 + w2*x2 + ... + bias
// 즉: y = dotProduct(weight, input) + bias
class Dense : public Layer{
private:    
    vector<vector<double>> weights; // 여러 뉴런의 가중치
    vector<double> bias;            // 각 뉴런의 bias
public:
    // 생성자
    Dense(const vector<vector<double>>& weights, const vector<double>& bias){
        this->weights = weights;
        this->bias = bias;
    }

    // Forward Propagation
    vector<double> forward(const vector<double>& input) override {
        vector<double> output;

        // TODO2
        // 출력 뉴런 개수만큼 반복
        for (size_t i = 0; i < weights.size(); i++)
        {
            //i번째의 뉴런을 출력
            double value = dotProduct(weights[i], input) + bias[i];
            output.push_back(value);
        }

        return output;
    }

    // Layer 이름 반환
    string getName() const override{
        return "Dense";
    }
};


// 5. ReLU Layer
// x > 0  → x,  x <= 0 → 0
class ReLU : public Layer{
public:
    vector<double> forward(const vector<double>& input) override{
        vector<double> output;

        // TODO3
        for (double value : input){
            if (value > 0){
                output.push_back(value);   // 양수 - 그대로 통과
            }
            else{
                output.push_back(0.0);     // 0 이하 - 0
            }
        }

        return output;
    }

    string getName() const override{
        return "ReLU";
    }
};


// 6. Sigmoid Layer
//              1
// y = -----------------
//          1 + e^(-x)
// 출력 범위: 0 ~ 1
class Sigmoid : public Layer{
public:
    vector<double> forward(const vector<double>& input) override{
        vector<double> output;
        for (double value : input){
            double result = 1.0 / (1.0 + exp(-value));
            output.push_back(result);
        }
        return output;
    }
    string getName() const override{
        return "Sigmoid";
    }
};


//Step Layer
class Step : public Layer{
public:
    vector<double> forward(const vector<double>& input) override{
        vector<double> output;
        for (double value : input){
            if (value >= 0){
                output.push_back(1.0);   // 0 이상 - 1
            }
            else{
                output.push_back(0.0);   // 음수 - 0
            }
        }
        return output;
    }

    string getName() const override{
        return "Step";
    }
};


// ============================================================
// 8. Forward Propagation 함수
// ============================================================
//
// network에 쌓인 Layer를 순서대로 통과시키면서
// 각 Layer에 들어간 값(input)과 나온 값(output)을 보여주고,
// 마지막 Layer의 출력을 반환
//
// ============================================================
vector<double> forwardPropagation(const vector<Layer*>& network, const vector<double>& input)
{
    vector<double> output = input;

    // Layer* 하나를 이용하여 서로 다른 객체(Dense/ReLU/Step/Sigmoid)의 forward()를 호출한다.
    // <다형성>
    for (Layer* layer : network)
    {
        // input  : 이 Layer에 들어가는 값 (= 바로 앞 Layer의 출력)
        cout << "  " << left << setw(8) << layer->getName() << " input  : ";
        printVector(output);

        output = layer->forward(output);

        // output : 이 Layer에서 나온 값 (이름 자리 8칸은 공백으로 채워 줄 맞춤)
        cout << "  " << setw(8) << "" << " output : ";
        printVector(output);
    }

    return output;
}


// ============================================================
// 9. 이진 분류 함수
// ============================================================
// Sigmoid 결과값 0.5 이상 → Class 1,  0.5 미만 → Class 0
int predictClass(double probability)
{
    if (probability >= 0.5)
    {
        return 1;
    }

    return 0;
}


// ============================================================
// 10. 네트워크 메모리 해제 함수
// ============================================================
// new로 만든 Layer 객체를 모두 delete
void deleteNetwork(vector<Layer*>& network)
{
    for (Layer* layer : network)
    {
        delete layer;
    }

    network.clear();
}


// ============================================================
// 11. Layer 단독 테스트 함수
// ============================================================
// Layer 하나에 값을 넣고 input / output을 나란히 출력
// Layer& (부모 참조)로 받으므로 ReLU / Sigmoid / Step 모두 넣을 수 있다 <다형성>
void testLayer(Layer& layer, const vector<double>& input)
{
    cout << "[" << layer.getName() << "]" << endl;

    cout << "  input  : ";
    printVector(input);

    cout << "  output : ";
    printVector(layer.forward(input));
}


int main()
{
    cout << "================================" << endl;
    cout << "       Simple C++ DNN" << endl;
    cout << "================================" << endl;

    // 1. 각 Layer의 weight / bias 초기화 (기존과 동일)

    // 첫 번째 Dense Layer
    // Input Node  : 2개, Output Node : 3개,  따라서 Weight Matrix는 3 x 2
    vector<vector<double>> weights1 =
    {
        { 0.5, -0.2 },
        {-0.3,  0.8 },
        { 0.7,  0.1 }
    };
    vector<double> bias1 ={0.1,-0.1,0.05};

    // 두 번째 Dense Layer
    // Input Node  : 3개, Output Node : 1개, 따라서 Weight Matrix는 1 x 3
    vector<vector<double>> weights2 =
    {
        { 0.6, -0.4, 0.9 }
    };
    vector<double> bias2 ={-0.2};

    // 2. Neural Network 생성
    // weight/bias는 똑같고, 가운데 활성화 함수만 다른 네트워크 2개
    // reluNet : Input(2) → Dense(2 → 3) → ReLU → Dense(3 → 1) → Sigmoid
    // stepNet : Input(2) → Dense(2 → 3) → Step → Dense(3 → 1) → Sigmoid
    vector<Layer*> reluNet;
    reluNet.push_back(new Dense(weights1, bias1));
    reluNet.push_back(new ReLU());
    reluNet.push_back(new Dense(weights2, bias2));
    reluNet.push_back(new Sigmoid());

    vector<Layer*> stepNet;
    stepNet.push_back(new Dense(weights1, bias1));
    stepNet.push_back(new Step());
    stepNet.push_back(new Dense(weights2, bias2));
    stepNet.push_back(new Sigmoid());

    // 3. 실험할 입력 데이터
    // Case 1 : 기존 입력 {1.0, 0.5} (x1이 큼) → ReLU 기준 Class 1
    // Case 2 : 바꾼 입력 {0.0, 1.0} (x2가 큼) → ReLU 기준 Class 0
    // 다른 입력도 시험하려면 아래 목록에 {x1, x2}를 추가하면 된다.
    vector<vector<double>> inputs =
    {
        {1.0, 0.5},
        {0.0, 1.0}
    };

    vector<double> reluResults;   // ReLU 네트워크의 최종 출력(Sigmoid 값)
    vector<double> stepResults;   // Step 네트워크의 최종 출력(Sigmoid 값)

    // 4. 케이스별 Forward Propagation
    for (size_t i = 0; i < inputs.size(); i++)
    {
        cout << endl;
        cout << "================================" << endl;
        cout << " Case " << i + 1 << " - Input : ";
        printVector(inputs[i]);
        cout << "================================" << endl;

        // (1) ReLU 네트워크
        cout << "[ReLU network]" << endl;
        vector<double> reluOutput = forwardPropagation(reluNet, inputs[i]);
        cout << "  => Prediction : Class " << predictClass(reluOutput[0]) << endl;

        // (2) Step 네트워크
        cout << endl;
        cout << "[Step network]" << endl;
        vector<double> stepOutput = forwardPropagation(stepNet, inputs[i]);
        cout << "  => Prediction : Class " << predictClass(stepOutput[0]) << endl;

        reluResults.push_back(reluOutput[0]);
        stepResults.push_back(stepOutput[0]);
    }

    // 5. 결과 비교 요약
    // Changed : ReLU → Step으로 바꿨을 때 예측 Class가 달라졌는지
    cout << endl;
    cout << "================================" << endl;
    cout << "      Comparison Summary" << endl;
    cout << "================================" << endl;

    cout << left << setw(6) << "Case"
         << setw(12) << "ReLU" << setw(8) << "Class"
         << setw(12) << "Step" << setw(8) << "Class"
         << "Changed" << endl;

    for (size_t i = 0; i < inputs.size(); i++)
    {
        int reluClass = predictClass(reluResults[i]);
        int stepClass = predictClass(stepResults[i]);

        cout << left << setw(6) << i + 1
             << setw(12) << reluResults[i] << setw(8) << reluClass
             << setw(12) << stepResults[i] << setw(8) << stepClass
             << (reluClass != stepClass ? "Yes" : "No") << endl;
    }

    // 6. 활성화 함수 Layer 단독 테스트 : input → output 확인
    cout << endl;
    cout << "================================" << endl;
    cout << "     Activation Layer Test" << endl;
    cout << "================================" << endl;

    ReLU    reluLayer;
    Sigmoid sigmoidLayer;
    Step    stepLayer;

    // ReLU    : 슬라이드 23쪽 예시 [0.7, -0.4, 0.1] → [0.7, 0.0, 0.1]
    testLayer(reluLayer, {0.7, -0.4, 0.1});

    // Sigmoid : 슬라이드 23쪽 예시 [1.27] → [0.7807]
    testLayer(sigmoidLayer, {1.27});

    // Step    : 경계값 0 포함, 음수 → 0 / 0 이상 → 1
    testLayer(stepLayer, {-1.0, -0.5, 0.0, 0.5, 1.0});

    // 7. 동적 객체 메모리 해제
    deleteNetwork(reluNet);
    deleteNetwork(stepNet);

    return 0;
}