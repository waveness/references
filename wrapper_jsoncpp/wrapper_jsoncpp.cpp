//
// Created by zhengbo.cai on 2017/10/20.
//
#include <fstream>
#include "wrapper_jsoncpp.h"
#include <iostream>
#include <sstream>

template<typename T>
static std::string toString(const T& t) {
  std::ostringstream oss;

  if (typeid(t) == typeid(double)) {
    std::cout << "this is double" << std::endl;
    int prec = std::numeric_limits<long double>::digits10;
    oss.precision(prec);
  }
  oss << t;
  return oss.str();
}

namespace JsonUtils {
  JsonWrappers::JsonWrappers() {
    release_manual_ = false;
    save_flag_ = true;
    root_ = NULL;
  }

  JsonWrappers::~JsonWrappers() {
    //  std::cout << "in ~JsonWrappers" << std::endl;
    if (release_manual_ && root_) {
      //  std::cout << "in ~JsonWrappers, delete root" << std::endl;
      delete root_;
      root_ = NULL;
    }
    release_manual_ = false;
    save_flag_ = true;
    root_ = NULL;
  }

  bool JsonWrappers::Open(std::string jsonfile) {
    std::ifstream input;
    input.open(jsonfile, std::ifstream::in | std::ifstream::binary);
    if (!input.good()) {
      std::cout << "[JsonWrappers] Open " << jsonfile.c_str()
        << " failed" << std::endl;
      return false;
    }
    cur_jsonfname_ = jsonfile;
    root_ = new Json::Value();
    release_manual_ = true;
    if (!reader_.parse(input, *root_, true)) {
      std::cout << "[JsonWrappers] Open parser " << jsonfile.c_str()
        << " failed" << std::endl;
      input.close();
      return false;
    }
    input.close();
    return true;
  }

  bool JsonWrappers::OpenFromJsonValue(Json::Value* sub_value,
    std::string sub_fname) {
    release_manual_ = false;
    root_ = sub_value;
    cur_jsonfname_ = sub_fname;
    save_flag_ = false;
    return true;
  }

  bool JsonWrappers::OpenFromJsonString(std::string json) {
    if (json.empty()) {
      std::cout << "[JsonWrappers] Open String empty" << std::endl;
      return false;
    }
    root_ = new Json::Value();
    release_manual_ = true;
    if (!reader_.parse(json, *root_, true)) {
      std::cout << "[JsonWrappers] OpenFromJsonString failed" << std::endl;
      return false;
    }
    cur_jsonfname_ = "";
  }

  bool JsonWrappers::Close() {
    if (release_manual_ && root_) {
      delete root_;
      root_ = NULL;
    }
    return true;
  }

  bool JsonWrappers::Save2File(std::string another_file) {
    std::string dst_file = cur_jsonfname_;
    if (!another_file.empty()) {
      dst_file = another_file;
    }
    for (auto iter = sub_configs_.begin(); iter != sub_configs_.end(); iter++) {
      reinterpret_cast<JsonWrappers*>(iter->second.get())->Save2File();
    }
    if (!save_flag_)
      return false;
    std::ofstream of;
    of.open(dst_file, std::ofstream::out | std::ofstream::binary);
    if (!of.good()) {
      std::cout << "[JsonWrappers] Save2File open file "
        << dst_file.c_str() << "failed" << std::endl;
      return false;
    }
    Json::StyledStreamWriter ofstm_write = Json::StyledStreamWriter();
    ofstm_write.write(of, *root_);
    of.close();
  }

  int JsonWrappers::GetIntValue(const std::string &key, int default_value) {
    if (key.empty()) {
      std::cout << "[JsonWrappers] key is empty" << std::endl;
      return default_value;
    }
    if (root_->isMember(key) && (*root_)[key].isInt())
      return (*root_)[key].asInt();
    else
      return default_value;
  }

  float JsonWrappers::GetFloatValue(const std::string &key,
    float default_value) {
    if (key.empty()) {
      std::cout << "[JsonWrappers] key is empty" << std::endl;
      return default_value;
    }
    if (root_->isMember(key) && (*root_)[key].isDouble())
      return (*root_)[key].asFloat();
    else
      return default_value;
  }

  bool JsonWrappers::GetBoolValue(const std::string &key, bool default_value) {
    if (key.empty()) {
      std::cout << "[JsonWrappers] key is empty" << std::endl;
      return default_value;
    }
    if (root_->isMember(key) && (*root_)[key].isBool())
      return (*root_)[key].asBool();
    else
      return default_value;
  }

  int64_t JsonWrappers::GetLongValue(const std::string &key,
    int64_t default_value) {
    if (key.empty()) {
      std::cout << "[JsonWrappers] key is empty" << std::endl;
      return default_value;
    }
    if (root_->isMember(key) && (*root_)[key].isInt64())
      return (*root_)[key].asInt64();
    else
      return default_value;
  }

  double JsonWrappers::GetDoubleValue(const std::string &key,
    double default_value) {
    if (key.empty()) {
      std::cout << "[JsonWrappers] key is empty" << std::endl;
      return default_value;
    }
    if (root_->isMember(key) && (*root_)[key].isDouble())
      return (*root_)[key].asDouble();
    else
      return default_value;
  }

  const std::string JsonWrappers::GetSTDStringValue(const std::string &key,
    const std::string &default_value) {
    if (key.empty()) {
      std::cout << "[JsonWrappers] key is empty" << std::endl;
      return default_value;
    }
    if (root_->isMember(key) && (*root_)[key].isString())
      return (*root_)[key].asString();
    else
      return default_value;
  }

spJsonWrapper JsonWrappers::GetSubConfig(const std::string &name) {
  spJsonWrapper empty_config(std::make_shared<JsonWrappers>());
  empty_config->OpenFromJsonString("{}");
  //  std::cout << "[JsonWrappers] this file name "
  //  << cur_jsonfname_ << std::endl;
  if (name.empty()) {
      std::cout << "[JsonWrappers] key is empty" << std::endl;
      return empty_config;
    }
    // search if already open
    if (sub_configs_.find(name) != sub_configs_.end()) {
      //  std::cout << "[JsonWrappers] key=" << newjson_path
      //  << ", find one" << std::endl;
      return sub_configs_[name];
    }
    //  if (root_->isMember(name)) {
    //  here true mean if not exsit, will create it
    if (1) {
      Json::Value *sub_root = &(*root_)[name];
	  spJsonWrapper spconfig(std::make_shared<JsonWrappers>());
      if (sub_root->isMember("redirect") &&
        !(*sub_root)["redirect"].asString().empty()) {
        std::string newjson_path;
        if (std::string::npos != cur_jsonfname_.find_last_of("\\")) {
          newjson_path =
            cur_jsonfname_.substr(0, cur_jsonfname_.find_last_of("\\")) + "\\" +
            (*sub_root)["redirect"].asString();
        } else {
          newjson_path =
            cur_jsonfname_.substr(0, cur_jsonfname_.find_last_of("/")) + "/" +
            (*sub_root)["redirect"].asString();
        }

        if (sub_configs_.find(newjson_path) != sub_configs_.end()) {
          //  std::cout << "[JsonWrappers] key=" << newjson_path
          //  << ", find one" << std::endl;
          return sub_configs_[newjson_path];
        } else {
        if (spconfig->Open(newjson_path)) {
          sub_configs_.insert(std::map<std::string, spJsonWrapper>::
		  value_type(newjson_path, spconfig));
          return spconfig;
        }else {
            std::cout << "[JsonWrappers] open redirect json "
              << newjson_path << " failed!!" << std::endl;
            return empty_config;
          }
        }
      } else {
        reinterpret_cast<JsonWrappers*>(
          spconfig.get())->OpenFromJsonValue(sub_root, cur_jsonfname_);
        sub_configs_.insert(std::map<std::string, spJsonWrapper>::
          value_type(name, spconfig));
        return spconfig;
      }
    }

    return empty_config;
  }

spJsonWrapper JsonWrappers::GetArray(const std::string &arrayname) {
  spJsonWrapper empty_config(std::make_shared<JsonWrappers>());
  empty_config->OpenFromJsonString("{}");
  //std::cout << "this file name " << cur_jsonfname_ << std::endl;
  if (arrayname.empty()) {
      std::cout << "[JsonWrappers] key is empty" << std::endl;
      return empty_config;
    }
    // search if already open
    if (sub_configs_.find(arrayname) != sub_configs_.end()) {
      return sub_configs_[arrayname];
    }
    //  here true mean if not exsit, will create it
    if (true || root_->isMember(arrayname)) {
      Json::Value *array = &(*root_)[arrayname];
      int size = array->size();
    spJsonWrapper spconfig(std::make_shared<JsonWrappers>());
    
    spconfig->OpenFromJsonValue(array, cur_jsonfname_);
      sub_configs_.insert(std::map<std::string, JsonWrappers>::
        value_type(arrayname, spconfig));
      return spconfig;
    }

    return empty_config;
  }

  int JsonWrappers::GetArraySize() {
    if (!root_->isArray()) {
      std::cout << "is not array" << std::endl;
      return 0;
    }
    return root_->size();
  }
spJsonWrapper JsonWrappers::operator[](int index) {
  spJsonWrapper empty_config(std::make_shared<JsonWrappers>());
  empty_config->OpenFromJsonString("{}");
    /*if (true || !root_->isArray()) {
      std::cout << "is not array" << std::endl;
      return empty_config;
    }*/
    std::string str_idx = toString(index);
    // search if already open
    if (sub_configs_.find(str_idx) != sub_configs_.end()) {
      return sub_configs_[str_idx];
    }
  Json::Value *sub_root = &(*root_)[index];
  spJsonWrapper spconfig(std::make_shared<JsonWrappers>());
  spconfig->OpenFromJsonValue(sub_root, cur_jsonfname_);
    sub_configs_.insert(std::map<std::string, JsonWrappers>::
      value_type(str_idx, spconfig));
    return spconfig;
  }


  bool JsonWrappers::SetIntValue(const std::string& key, int value) {
    if (key.empty()) {
      std::cout << "[JsonWrappers] key is empty" << std::endl;
      return false;
    }
    (*root_)[key] = value;
    return true;
  }

  bool JsonWrappers::SetFloatValue(const std::string& key, float value) {
    if (key.empty()) {
      std::cout << "[JsonWrappers] key is empty" << std::endl;
      return false;
    }
    (*root_)[key] = value;
    return true;
  }

  bool JsonWrappers::SetBoolValue(const std::string& key, bool value) {
    if (key.empty()) {
      std::cout << "[JsonWrappers] key is empty" << std::endl;
      return false;
    }
    (*root_)[key] = value;
    return true;
  }

  bool JsonWrappers::SetLongValue(const std::string& key, int64_t value) {
    if (key.empty()) {
      std::cout << "[JsonWrappers] key is empty" << std::endl;
      return false;
    }
    (*root_)[key] = (Json::Value::Int64)value;
    return true;
  }

  bool JsonWrappers::SetDoubleValue(const std::string& key, double value) {
    if (key.empty()) {
      std::cout << "[JsonWrappers] key is empty" << std::endl;
      return false;
    }
    (*root_)[key] = value;
    return true;
  }

  bool JsonWrappers::SetSTDStringValue(
    const std::string& key, std::string& value) {
    if (key.empty()) {
      std::cout << "[JsonWrappers] key is empty" << std::endl;
      return false;
    }
    (*root_)[key] = value;
    return true;
  }

  bool JsonWrappers::DelItem(const std::string& key) {
    if (key.empty()) {
      std::cout << "[JsonWrappers] key is empty" << std::endl;
      return false;
    }
    root_->removeMember(key);
    return true;
  }
}  //  namespace hobot
