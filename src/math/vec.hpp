#ifndef ENGINE_MATH_VEC
#define ENGINE_MATH_VEC

const int VEC_ERR_BUF_SIZE = 1024;

char VEC_ERR_BUF[VEC_ERR_BUF_SIZE];

template<int N, class T>
struct vec {

    T elements[N];

    T &at(int i) {
        if (i >= N || i < 0) {
            snprintf(VEC_ERR_BUF, VEC_ERR_BUF_SIZE,
                "invalid index (%d) for vec of size %d", i, N);
            throw runtime_error(VEC_ERR_BUF);
        }
        return elements[i];
    }

    vec<N, T> operator +(const vec<N, T> &other) const {
        vec<N, T> res;
        for (int i = 0; i < N; i++)
            res.elements[i] = at(i) + other.at(i);
        return res;
    }

    vec<N, T> operator -(const vec<N, T> &other) const {
        vec<N, T> res;
        for (int i = 0; i < N; i++)
            res.elements[i] = at(i) - other.at(i);
        return res;
    }

    vec<N, T> operator *(const vec<N, T> &other) const {
        vec<N, T> res;
        for (int i = 0; i < N; i++)
            res.elements[i] = at(i) * other.at(i);
        return res;
    }

    vec<N, T> operator /(const vec<N, T> &other) const {
        vec<N, T> res;
        for (int i = 0; i < N; i++)
            res.elements[i] = at(i) / other.at(i);
        return res;
    }

    bool operator ==(const vec<N, T> &other) const {
        for (int i = 0; i < N; i++)
            if (at(i) != other.at(i))
                return false;
        return true;
    }

    bool operator !=(const vec<N, T> &other) const {
        return !(*this == other);
    }

    operator vec<N, int> () {
        vec<N, int> res;
        for (int i = 0; i < N; i++)
            res.elements[i] = (int)at(i);
        return res;
    }

};

typedef vec<1, float> vec1;
typedef vec<2, float> vec2;
typedef vec<3, float> vec3;
typedef vec<4, float> vec4;

typedef vec<1, double> vec1d;
typedef vec<2, double> vec2d;
typedef vec<3, double> vec3d;
typedef vec<4, double> vec4d;

typedef vec<1, int> vec1i;
typedef vec<2, int> vec2i;
typedef vec<3, int> vec3i;
typedef vec<4, int> vec4i;

typedef vec<1, unsigned int> vec1u;
typedef vec<2, unsigned int> vec2u;
typedef vec<3, unsigned int> vec3u;
typedef vec<4, unsigned int> vec4u;

#endif