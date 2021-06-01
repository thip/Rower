#ifndef AGGREGATOR_H
#define AGGREGATOR_H

template<class T, int N>
class Aggregator {
    public:
        void add (T elem){
            head = (head+1)%N;
            elems[head] = elem;
        };
        T delta(){
            return elems[head]-elems[(head+N-1)%N];
        };
        T average(){
            T sum = 0;
            for (auto elem : elems){
                sum += elem;
            }
            return sum/N;
        };
        T current(){
            return elems[head];
        }

    protected:
        int head = 0;
        T elems[N] = {}; 
};

#endif