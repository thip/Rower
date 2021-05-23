class Rower {
    public:
        Rower();
        void AddPulse(int time);
        float GetDistance();
        int GetSplit(int index);
    
    private:
        int pulseCount;
        float pulseRatio;
};