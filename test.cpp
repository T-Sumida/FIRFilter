#include "FIRFilter.hpp"

#include <cmath>
#include <iostream>

using namespace std;

// サンプリング周波数
#define SAMP_RATE 44100

/**
 * サイン波を合成する
 * @param   data    データバッファ
 * @param   f       基本周波数
 * @param   length  データバッファサイズ
 */
void generateSin(float* data,float f,int length){
    for(int i = 0;i < length;i++)
        data[i] = sin(2*M_PI*f*i/SAMP_RATE);
}


/**
 * メイン関数
 */
int main(int argc, char const *argv[]){
    // 元データとフィルタリング後データのバッファを確保
    float* data = new float[SAMP_RATE];
    float* result = new float[SAMP_RATE];

    // サイン波をdataに格納する
    generateSin(data,1.,SAMP_RATE);

    //FIRFilterインスタンスを宣言
    FIRFilter<float>* _firFilter = new FIRFilter<float>(HANNING);

    // LPFフィルタを設計する
    _firFilter->_createLPF(3000./SAMP_RATE,1000./SAMP_RATE);
    // フィルタリングを行う
    _firFilter->_fir(data,result,SAMP_RATE);

    // メモリを解放する
    delete [] data;
    delete [] result;
    return 0;
}
