#include <gtest/gtest.h>
#include "rower.h"

class MockPresenter : public RowerPresenter {
  public:
    void Distance(float distance){
      this->distance = distance;
    }

    float distance;
};



TEST(Rower, 1_ticks_is_1m) {
  MockPresenter* presenter = new MockPresenter;

  RowerConfig config = {
    .pulseRatio = 1.0f,
    .presenter = presenter
  };

  Rower* rower = new Rower(config);

  rower->AddPulse(1);
  
  EXPECT_FLOAT_EQ(presenter->distance, 1.0f);
}

TEST(Rower, 0_ticks_is_0m) {
  MockPresenter* presenter = new MockPresenter;

  RowerConfig config = {
    .pulseRatio = 4.805f,
    .presenter = presenter
  };

  Rower* rower = new Rower(config);
  
  EXPECT_FLOAT_EQ(presenter->distance, 0.0f);
}

TEST(Rower, 100_ticks_is_20_81m) {
  MockPresenter* presenter = new MockPresenter;

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
  MockPresenter* presenter = new MockPresenter;

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
