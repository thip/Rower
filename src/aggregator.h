#ifndef AGGREGATOR_H
#define AGGREGATOR_H

template<class T, int N>
class Aggregator {
    public:
        void add (int timeStamp, T elem){
            add(elem);
            timeStamps[head] = timeStamp;
        };
        void add (T elem){
            head = move(head, 1);
            elems[head] = elem;
            sampleCount++;
        };
        T delta(){
            return elems[head]-elems[move(head, -1)];
        };
        T average(int period){
            int cutoff = timeStamps[head] - period;
            T sum = 0;
            int iterations = 0;
            for (int index = head; iterations < N && iterations < sampleCount; index = move(index, -1), iterations++){
                if (period > 0 && timeStamps[index] < cutoff){
                    break;
                }
            
                sum += elems[index];    
            }

            return sum/iterations;
        };

        T average(){
            return average(0);
        };

        T current(){
            return elems[head];
        };

        int count(){
            return sampleCount;
        }

    protected:
        int head = 0;
        int sampleCount = 0;
        T elems[N] = {};
        int timeStamps[N] = {};

    private:
        int move(int value, int amount){
            return (value + amount + N) % N;
        }
};

#endif