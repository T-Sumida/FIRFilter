#ifndef _WINDOW_FUNC_HH_
#define _WINDOW_FUNC_HH_

#include <math.h>

#define SINGBELL 0
#define HANNING 1
#define HAMMING 2
#define BLACKMAN 3

/**
 * 入力バッファにSINGBELL関数をかける
 * @param   data    入力バッファ
 * @param   size    入力バッファサイズ
 */
template <class X> void _singbell(X* data,int size){
    X f = 2.0*M_PI/(X)(size-1);
    for(int i = 0;i < size;i++){
        data[i] *= sin(f*i);
    }
}

/**
 * 入力バッファにHANNING関数をかける
 * @param   data    入力バッファ
 * @param   size    入力バッファサイズ
 */
template <class X> void _hanning(X* data,int size){
    X f = 2.0*M_PI/(X)(size-1);
    for(int i = 0;i < size;i++){
        data[i] *= 0.5*(1.0 - cos(f*i));
    }
}

/**
 * 入力バッファにHAMMING関数をかける
 * @param   data    入力バッファ
 * @param   size    入力バッファサイズ
 */
template <class X> void _hamming(X* data,int size){
    X f = 2.0*M_PI/(X)(size-1);
    for(int i = 0;i < size;i++){
        data[i] *= 0.54 - 0.46 * cos(f*i);
    }
}

/**
 * 入力バッファにBLACKMAN関数をかける
 * @param   data    入力バッファ
 * @param   size    入力バッファサイズ
 */
template <class X> void _blackman(X* data,int size){
    X f = 2.0*M_PI/(X)(size-1);
    for(int i = 0;i < size;i++){
        data[i] *= 0.42 - 0.5*cos(f*i) + 0.08 * cos(2*f*i);
    }
}

#endif