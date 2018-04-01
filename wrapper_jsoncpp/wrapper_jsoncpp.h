//
// Created by zhengbo.cai on 2017/10/20.
/*
* wrapper jsoncpp API, support "redirect" semantic read and write, like below:
* 	{
* 	    "test1": "test 1",
* 	    "another":{
*           "redirect" : "mytest2.json"
*       }
*   }
*   ======mytest2.json=====
*   {
*      "test2": "test 2",
*      "test3": 23456
*   }
*/
//
#ifndef HOBOT_ADAS_SOC_JSONUTILS_H
#define HOBOT_ADAS_SOC_JSONUTILS_H

#include <string>
#include <vector>
#include <map>
#include <mutex>
#include <memory>
#include <json/json.h>
 
namespace JsonUtils {
class JsonWrappers;
typedef std::shared_ptr<JsonWrappers> spJsonWrapper;
class JsonWrappers {
public:
  JsonWrappers();
  ~JsonWrappers();
  bool Open(std::string jsonfile);
  bool OpenFromJsonString(std::string json);
  bool Close();
  bool Save2File(std::string another_file="");

  /*===========================================
  ** GetValue function declare
  =============================================*/
  int GetIntValue(const std::string &key, int default_value = 0);

  float GetFloatValue(const std::string &key, float default_value = 0.0f);

  bool GetBoolValue(const std::string &key, bool default_value = false);

  int64_t GetLongValue(const std::string &key, int64_t default_value = 0);

  double GetDoubleValue(const std::string &key, double default_value = 0.0);

  const std::string GetSTDStringValue(const std::string &key,
      const std::string &default_value = "");

  // will insert a new empty sub config if sub_configs_[name] do not exist
  spJsonWrapper GetSubConfig(const std::string &name);
  spJsonWrapper GetArray(const std::string &arrayname);
  int GetArraySize();

  /*===========================================
  ** SetValue function declare
  =============================================*/
  bool SetIntValue(const std::string& key, int value);

  bool SetFloatValue(const std::string& key, float value);

  bool SetBoolValue(const std::string& key, bool value);

  bool SetLongValue(const std::string& key, int64_t value);

  bool SetDoubleValue(const std::string& key, double value);

  bool SetSTDStringValue(const std::string& key, std::string& value);

  bool DelItem(const std::string& key);

  spJsonWrapper operator[](int index);


private:
  typedef std::map<std::string, spJsonWrapper> MapSpConfig;
  /*===========================================
  ** private function declare
  =============================================*/
  bool OpenFromJsonValue(Json::Value* sub_value, std::string sub_fname);
  /*===========================================
  ** private vars declare
  =============================================*/
  std::string cur_jsonfname_;
  Json::Reader reader_;
  Json::Value *root_;
  bool release_manual_;
  bool save_flag_;
  MapSpConfig sub_configs_;
  std::mutex config_mutex_;
};
}  // namespace JsonUtils
#endif