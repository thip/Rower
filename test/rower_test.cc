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

  rower->AddPulse(0);
  rower->AddPulse(1000);
  rower->AddPulse(2000);
  rower->AddPulse(3000);
  rower->AddPulse(4000);
  rower->AddPulse(5000);

  EXPECT_NEAR(presenter->velocity, 1.0f, 0.005);
}

TEST(Rower, velocity_2ms) {
  MockPresenter* presenter = new MockPresenter();

  RowerConfig config = {
    .pulseRatio = 1.0f,
    .presenter = presenter
  };

  Rower* rower = new Rower(config);

  rower->AddPulse(0);
  rower->AddPulse(500);
  rower->AddPulse(1000);
  rower->AddPulse(1500);
  rower->AddPulse(2000);
  rower->AddPulse(2500);

  EXPECT_NEAR(presenter->velocity, 2.0f, 0.005);
}

TEST(Rower, accel_0mss) {
  MockPresenter* presenter = new MockPresenter();

  RowerConfig config = {
    .pulseRatio = 1.0f,
    .presenter = presenter
  };

  Rower* rower = new Rower(config);

  rower->AddPulse(0);
  rower->AddPulse(1000);
  rower->AddPulse(2000);
  rower->AddPulse(3000);
  rower->AddPulse(4000);
  rower->AddPulse(5000);

  EXPECT_NEAR(presenter->acceleration, 0.0f, 0.1);
}

TEST(Rower, accel_1mss) {
  MockPresenter* presenter = new MockPresenter();

  RowerConfig config = {
    .pulseRatio = 1.0f,
    .presenter = presenter
  };

  Rower* rower = new Rower(config);

  rower->AddPulse(0);
  rower->AddPulse(1414);
  rower->AddPulse(2000);
  rower->AddPulse(2449);
  rower->AddPulse(2828);
  rower->AddPulse(3162);


  EXPECT_NEAR(presenter->acceleration, 1.0f, 0.1);
}

TEST(Rower, accel_0_1mss) {
  MockPresenter* presenter = new MockPresenter();

  RowerConfig config = {
    .pulseRatio = 1.0f,
    .presenter = presenter
  };

  Rower* rower = new Rower(config);

  rower->AddPulse(0);
  rower->AddPulse(4472);
  rower->AddPulse(6325);
  rower->AddPulse(7746);
  rower->AddPulse(8944);
  rower->AddPulse(10000);

  EXPECT_NEAR(presenter->acceleration, 0.1f, 0.01);
}
