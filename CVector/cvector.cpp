#include <iostream>
#include <cassert>

#define type template <typename T>

using namespace std;
const int MAX_SIZE = 32;

type
class CVector
{
    private:
        int size_;
        T data_[MAX_SIZE];
    public:
        CVector(int _size);
        ~CVector();
        int Vsize()
        {
            return size_;
        }
        CVector<T> operator + (CVector<T>& val)
        {
            assert(size_ == val.Vsize());
            CVector<T> exp(size_);
            int i;
            for(i = 0; i < size_; i++)
                exp[i] = data_[i] + val[i];
            return exp;
        }
        T& operator [] (int index)
        {
            assert(0 <= index && index < size_);
            return data_[index];
        }
        T operator ^ (CVector<T>& val) // scalar product
        {
            assert(size_ == val.Vsize());
            T exp = 0;
            int i;
            for(i = 0; i < size_; i++)
                exp += data_[i] * val[i];
            return exp;
        }
        void VDump();
        class iter
        {
        private:
            T* data_;
        public:
            iter(T* dt)
            {
                data_ = dt;
            }
            void operator ++ ()
            {
                data_ += 1;
                return;
            }
            T operator * ()
            {
                return *data_;
            }
            bool operator != (iter now)
            {
                if(data_ != now.data_)
                    return true; 
                else
                    return false;
            }

        };
        iter begin()
        {
            return iter(&data_[0]);
        }
        iter end()
        {
            return iter(&data_[size_ - 1]);
        }
};

type
CVector<T>::CVector(int _size)
{
    size_ = _size;
    int i;
    for(i = 0; i < size_; i++)
        data_[i] = 0;
}

type
CVector<T>::~CVector()
{
    int i;
    for(i = 0; i < size_; i++)
        data_[i] = 0xBAD;
    size_ = -1;
}

type
void CVector<T>::VDump()
 {
    int i;
    cout<<"(";
    for(i = 0; i < size_ - 1; i++)
        cout << data_[i] << ", ";
    cout <<data_[i]<<")"<< endl;
 }

template <>
CVector<bool> CVector<bool>::operator + (CVector<bool>& val) 
{
	assert(size_ == val.Vsize());
	CVector<bool> exp(size_);
	int i;
	for(i = 0; i < size_; i++)
		exp[i] = (data_[i] + val[i]) % 2;
	return exp;
}


int main()
{
    CVector<double> V(5), V1(5), V2(5);
    int i;
    for(i = 0; i < V.Vsize(); i++)
    {
        V1[i] = i + 0.5;
        V2[i] = i + 1;
    }
    V1.VDump();
    V2.VDump();
    V.VDump();
    V = V1 + V2;
    V.VDump();
    double sk = V1 ^ V2;
    cout << "scalar product = "<< sk << endl;

	CVector<bool> V3(5), V4(5), V5(5);
	for(i = 0; i < V.Vsize(); i++)
		{
		    V3[i] = (7 * i + 1) % 2;
		    V4[i] = (5 * i + 6) % 2;
    	}
	V3.VDump();
    V4.VDump();
    V5 = V3 + V4;
    V5.VDump();

    for(/*CVector<double>:: iter*/auto it = V.begin(); it != V.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << *V.end()<< endl;
    return 0;
}
