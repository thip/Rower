#include <gtest/gtest.h>
#include "../src/rower.h"

class MockPresenter : public RowerPresenter {
  public:
    void Distance(float distance){
      this->distance = distance;
    }

    void Velocity(float velocity){
      this->velocity = velocity;
    }

    void Acceleration(float acceleration){
      this->acceleration = acceleration;
    }

    float distance;
    float velocity;
    float acceleration;
};

void addPulses(Rower* rower, std::initializer_list<int> pulses){
  for( auto pulse : pulses )
    {
        rower->AddPulse(pulse);
    }
}

TEST(Rower, 1_ticks_is_1m) {
  MockPresenter* presenter = new MockPresenter();

  RowerConfig config = {
    .pulseRatio = 1.0f,
    .presenter = presenter
  };

  Rower* rower = new Rower(config);

  rower->AddPulse(1);
  
  EXPECT_FLOAT_EQ(presenter->distance, 1.0f);
}

TEST(Rower, 0_ticks_is_0m) {
  MockPresenter* presenter = new MockPresenter();

  RowerConfig config = {
    .pulseRatio = 4.805f,
    .presenter = presenter
  };

  Rower* rower = new Rower(config);
  
  EXPECT_FLOAT_EQ(presenter->distance, 0.0f);
}

TEST(Rower, 100_ticks_is_20_81m) {
  MockPresenter* presenter = new MockPresenter();

  RowerConfig config = {
    .pulseRatio = 4.805f,
    .presenter = presenter
  };

  Rower* rower = new Rower(config);

  for (int i = 0; i < 100; i++){
    rower->AddPulse(1);
  }
  
  EXPECT_NEAR(presenter->distance, 20.81f, 0.005);
}

TEST(Rower, 150_ticks_is_31_22m) {
  MockPresenter* presenter = new MockPresenter();

  RowerConfig config = {
    .pulseRatio = 4.805f,
    .presenter = presenter
  };

  Rower* rower = new Rower(config);

  for (int i = 0; i < 150; i++){
    rower->AddPulse(1);
  }
  
  EXPECT_NEAR(presenter->distance, 31.22f, 0.005);
}


TEST(Rower, velocity_1ms) {
  MockPresenter* presenter = new MockPresenter();

  RowerConfig config = {
    .pulseRatio = 1.0f,
    .presenter = presenter
  };

  Rower* rower = new Rower(config);

  addPulses(rower, {1000,2000,3000,4000,5000});

  EXPECT_NEAR(presenter->velocity, 1.0f, 0.005);
}

TEST(Rower, velocity_2ms) {
  MockPresenter* presenter = new MockPresenter();

  RowerConfig config = {
    .pulseRatio = 1.0f,
    .presenter = presenter
  };

  Rower* rower = new Rower(config);

  addPulses(rower, {500,1000,1500,2000,2500});

  EXPECT_NEAR(presenter->velocity, 2.0f, 0.005);
}

TEST(Rower, accel_0mss) {
  MockPresenter* presenter = new MockPresenter();

  RowerConfig config = {
    .pulseRatio = 1.0f,
    .presenter = presenter
  };

  Rower* rower = new Rower(config);

  addPulses(rower, {1000,2000,3000,4000,5000,6000,7000,8000,9000,10000});

  EXPECT_NEAR(presenter->acceleration, 0.0f, 0.05);
}

TEST(Rower, accel_1mss) {
  MockPresenter* presenter = new MockPresenter();

  RowerConfig config = {
    .pulseRatio = 1.0f,
    .presenter = presenter
  };

  Rower* rower = new Rower(config);

  addPulses(rower, {1414, 2000, 2449, 2828, 3162, 3464, 3742, 4000, 4243, 4472,
                    4690, 4899, 5099, 5292, 5477, 5657, 5831, 6000, 6164, 6325,
                    6481,6633, 6782, 6928, 7071, 7211});


  EXPECT_NEAR(presenter->acceleration, 1.0f, 0.05);
}

TEST(Rower, accel_0_1mss) {
  MockPresenter* presenter = new MockPresenter();

  RowerConfig config = {
    .pulseRatio = 1.0f,
    .presenter = presenter
  };

  Rower* rower = new Rower(config);

addPulses(rower, {4472, 6325, 7746, 8944, 10000, 10954, 11832, 12649, 13416, 14142});

  EXPECT_NEAR(presenter->acceleration, 0.1f, 0.005);
}
