#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../src/jsonPresenter.h"

using ::testing::HasSubstr;

TEST(JsonPresenter, no_data_zeroes) {
  JsonPresenter* jsonPresenter = new JsonPresenter();

  jsonPresenter->Present([](char* json){
      EXPECT_STREQ(json, "{\"distance\":0,\"velocity\":0.00,\"acceleration\":0.00}");
  });
}

TEST(JsonPresenter, distance_1) {
  JsonPresenter* jsonPresenter = new JsonPresenter();

  jsonPresenter->Distance(1.0f);
  
  jsonPresenter->Present([](char* json){
      EXPECT_THAT(json, HasSubstr("\"distance\":1"));
  });
}

TEST(JsonPresenter, distance_2) {
  JsonPresenter* jsonPresenter = new JsonPresenter();

  jsonPresenter->Distance(2.0f);
  
  jsonPresenter->Present([](char* json){
      EXPECT_THAT(json, HasSubstr("\"distance\":2"));
  });
}

TEST(JsonPresenter, distance_10000) {
  JsonPresenter* jsonPresenter = new JsonPresenter();

  jsonPresenter->Distance(10000.0f);
  
  jsonPresenter->Present([](char* json){
    EXPECT_THAT(json, HasSubstr("\"distance\":10000"));
  });
}

TEST(JsonPresenter, velocity_1) {
  JsonPresenter* jsonPresenter = new JsonPresenter();

  jsonPresenter->Velocity(1.0f);
  
  jsonPresenter->Present([](char* json){
    EXPECT_THAT(json, HasSubstr("\"velocity\":1.00"));
  });
}

TEST(JsonPresenter, velocity_2_5) {
  JsonPresenter* jsonPresenter = new JsonPresenter();

  jsonPresenter->Velocity(2.5f);
  
  jsonPresenter->Present([](char* json){
    EXPECT_THAT(json, HasSubstr("\"velocity\":2.50"));
  });
}

TEST(JsonPresenter, velocity_10_53) {
  JsonPresenter* jsonPresenter = new JsonPresenter();

  jsonPresenter->Velocity(10.53f);
  
  jsonPresenter->Present([](char* json){
    EXPECT_THAT(json, HasSubstr("\"velocity\":10.53"));
  });
}

TEST(JsonPresenter, acceleration_1) {
  JsonPresenter* jsonPresenter = new JsonPresenter();

  jsonPresenter->Acceleration(1.0f);
  
  jsonPresenter->Present([](char* json){
    EXPECT_THAT(json, HasSubstr("\"acceleration\":1.00"));
  });
}

TEST(JsonPresenter, acceleration_2_45) {
  JsonPresenter* jsonPresenter = new JsonPresenter();

  jsonPresenter->Acceleration(2.45f);
  
  jsonPresenter->Present([](char* json){
    EXPECT_THAT(json, HasSubstr("\"acceleration\":2.45"));
  });
}

TEST(JsonPresenter, acceleration_nan) {
  JsonPresenter* jsonPresenter = new JsonPresenter();

  jsonPresenter->Acceleration(nan(""));
  
  jsonPresenter->Present([](char* json){
    EXPECT_THAT(json, HasSubstr("\"acceleration\":0.00"));
  });
}

TEST(JsonPresenter, velocity_nan) {
  JsonPresenter* jsonPresenter = new JsonPresenter();

  jsonPresenter->Velocity(nan(""));
  
  jsonPresenter->Present([](char* json){
    EXPECT_THAT(json, HasSubstr("\"velocity\":0.00"));
  });
}