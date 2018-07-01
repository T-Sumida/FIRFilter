#ifndef _FIR_FILTER_HH_
#define _FIR_FILTER_HH_

#include <cmath>
#include <string.h>

#include "WindowFunc.hpp"


template<class T> class FIRFilter{
private:
    /**
     * フィルタ係数タップ数
     */
    int _n;
    /**
     * 窓関数を示すフラグ
     */
    int _windowFuncFlag;
    /**
     * フィルタ係数バッファ
     */
    T* _coef;
    
    /**
     * シンク関数
     * @param x 入力データ
     * @return  シンク関数計算結果
     */
    T _sinc(T x){
        if(x==0.0) return 1.0;
        else return sin(x)/x;
    }

    /**
     * フィルタのタップ数を計算する
     * @param   delta   遷移帯域幅
     */
    int _calcTaps(float delta){
        int n = round(3.1/delta)-1;
        if((n+1)%2 == 0) n++;
        return n;
    }

    /**
     * 入力されたデータに対して窓関数をかける
     * @param data  入力バッファ
     * @param size  入力バッファサイズ
     */
    void _windowfuncMethod(T* data,int size){
        switch(this->_windowFuncFlag){
            case SINGBELL:
            _singbell(data,size);
            break;

            case HANNING:
            _hanning(data,size);
            break;

            case HAMMING:
            _hamming(data,size);
            break;

            case BLACKMAN:
            _blackman(data,size);
            break;

            default:
            break;
        }
    }


public:
    /**
     * コンストラクタ
     * @param flag 窓関数を示すフラグ 
     */
    FIRFilter(int windowFuncFlag){
        _windowFuncFlag = windowFuncFlag;
        this->_coef = nullptr;
    }

    /**
     * デストラクタ
     * 係数配列のメモリを解放
     */
    ~FIRFilter(){
        if(this->_coef) delete [] this->_coef;
    }

    /**
     * LPFの係数を作成する
     * @param fe    エッジ周波数 = カットオフ周波数/サンプリング周波数[Hz]
     * @param delta 遷移帯域幅 = 帯域幅[Hz]/サンプリング周波数[Hz]
     */
    void _createLPF(float fe,float delta){
        this->_n = this->_calcTaps(delta);

        if(this->_coef) delete [] this->_coef;
        this->_n++;
        this->_coef = new T[this->_n];
        for(int i = 0;i < this->_n;i++)
            this->_coef[i] = 2.0 * fe * this->_sinc(2.0 * M_PI * fe * (i-(this->_n-1)/2));
        this->_windowfuncMethod(this->_coef,this->_n);
    }

    /**
     * BPFの係数を作成する
     * @param fe1   エッジ周波数1 = カットオフ周波数/サンプリング周波数[Hz]
     * @param fe2   エッジ周波数2 = カットオフ周波数/サンプリング周波数[Hz]
     * @param delta 遷移帯域幅 = 帯域幅[Hz]/サンプリング周波数[Hz]
     */
    void _createBPF(float fe1,float fe2,float delta){
        this->_n = this->_calcTaps(delta);

        if(this->_coef) delete [] this->_coef;
        this->_n++;
        this->_coef = new T[this->_n];
        for(int i = 0;i < this->_n;i++)
            this->_coef[i] = 2 * fe2 * this->_sinc(2 * M_PI * fe2 * (i-((this->_n-1)/2))) - 2 * fe1 * this->_sinc(2 * M_PI * fe1 * (i-((this->_n-1)/2)));
        this->_windowfuncMethod(this->_coef,this->_n);
    }

    /**
     * HPFの係数を作成する
     * @param fe    エッジ周波数 = カットオフ周波数/サンプリング周波数[Hz]
     * @param delta 遷移帯域幅 = 帯域幅[Hz]/サンプリング周波数[Hz]
     */
    void _createHPF(float fe,float delta){
        this->_n = this->_calcTaps(delta);

        if(this->_coef) delete [] this->_coef;
        this->_n++;
        this->_coef = new T[this->_n];
        for(int i = 0;i < this->_n;i++)
            this->_coef[i] = this->_sinc(M_PI*(i-((this->_n-1)/2))) - 2 * fe * this->_sinc(2 * M_PI * fe * (i-((this->_n-1)/2)));
        this->_windowfuncMethod(this->_coef,this->_n);
    }

    /**
     * FIRフィルタリングを行う
     * @param data      入力データバッファ
     * @param result    出力データバッファ
     * @param size      データバッファのサイズ
     * @return          FIR成功時：１，失敗時：０
     */
    inline int _fir(T* data,T* result,int size){
        if(!this->_coef) return 0;
        memset(result,0,sizeof(T)*size);
        for(int i = 0;i < size;i++){
            for(int j = 0;j < this->_n;j++){
                if(i-j >= 0) result[i] += data[i]*this->_coef[j];
            }
        }
        return 1;
    }
};

#endif