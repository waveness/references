#include <wrapper_jsoncpp.h>
#include <fstream>
#include <iostream>

void test_jsoncpp() {
  JsonWrappers jhanle;
  std::string json_file = "D:\\temp\\Adas\\mytest.json";
  std::string json_file_ot = "D:/temp/Adas/writetest.json";
  if (!jhanle.Open(json_file))
    return;
  int val_int = 0;
  float val_float = 0.0f;
  int64_t val_int64 = 0;
  double val_double = 0.0;
  bool val_bool = false;
  std::string val_str = "";
  std::cout.precision(18);

  val_int = jhanle.GetIntValue("vint", 0);
  val_float = jhanle.GetFloatValue("vfloat", val_float);
  val_double = jhanle.GetDoubleValue("vdouble", val_double);
  val_int64 = jhanle.GetLongValue("vint64", val_int64);
  val_bool = jhanle.GetBoolValue("vbool", val_bool);
  val_str = jhanle.GetSTDStringValue("vstring", val_str);

  std::cout << "val_int = " << val_int << std::endl;
  std::cout << "val_float = " << val_float << std::endl;
  std::cout << "val_double = " << val_double << std::endl;
  std::cout << "val_int64 = " << val_int64 << std::endl;
  std::cout << "val_bool = " << val_bool << std::endl;
  std::cout << "val_string = " << val_str << std::endl;
  

  jhanle.SetIntValue("vint", val_int + 1);
  jhanle.SetFloatValue("vfloat", val_float + 1);
  jhanle.SetDoubleValue("vdouble", val_double + 1);
  jhanle.SetLongValue("vint64", val_int64 + 1);
  jhanle.SetBoolValue("vbool", ~val_bool);
  val_str = "this is new string";
  jhanle.SetSTDStringValue("vstring", val_str);
  jhanle.SetIntValue("new_vint", 879);

  //jhanle.DelItem("insert", "mem2");

  float another_float = jhanle.GetSubConfig("another")->GetFloatValue("vfloat", 0.0);
  val_int = jhanle.GetSubConfig("another")->GetSubConfig("people")->GetIntValue("age", 100);
  val_str = jhanle.GetSubConfig("another")->GetSubConfig("people")->GetSTDStringValue("name", "testname");
  std::cout << "another float value = " << another_float << std::endl;
  std::cout << "another int value = " << val_int << std::endl;
  std::cout << "another str value = " << val_str << std::endl;
  jhanle.GetSubConfig("another")->GetSubConfig("people")->SetBoolValue("sex", true);
  jhanle.GetSubConfig("another")->GetSubConfig("people")->SetDoubleValue("vdouble", 0.03554892644024208);
  jhanle.GetSubConfig("another")->GetSubConfig("people")->SetFloatValue("vfloat", 1457.4897);
  jhanle.GetSubConfig("another")->GetSubConfig("people")->SetIntValue("vint", 5566);
  jhanle.GetSubConfig("another")->GetSubConfig("people")->SetLongValue("vlong", 12345677890123);
  std::string tempstr = "test sub config write string";
  jhanle.GetSubConfig("another")->GetSubConfig("people")->SetSTDStringValue("stdstr", tempstr);
  jhanle.GetSubConfig("another")->SetIntValue("testInt", 256);
  
  std::cout << "another animal name = " << jhanle.GetSubConfig("another")->GetSubConfig("animal")->GetSTDStringValue("name") << std::endl;
  std::cout << "another animal feature = " << jhanle.GetSubConfig("another")->GetSubConfig("animal")->GetSTDStringValue("feature") << std::endl;
  jhanle.GetSubConfig("another")->GetSubConfig("animal")->SetIntValue("vint", 888);
  //jhanle.GetSubConfig("another")->Save2File();

  val_float = jhanle.GetSubConfig("another_notwork")->GetFloatValue("vfloat", 0.0);
  std::cout << "another_not work float value = " << val_float << std::endl;

  /*val_float = jhanle.GetSubConfig("another")->GetSubConfig("test_redirect2")->GetFloatValue("vfloat", 0.1);
  val_int = jhanle.GetSubConfig("another")->GetSubConfig("test_redirect2")->GetSubConfig("people2")->GetIntValue("age", 101);
  val_str = jhanle.GetSubConfig("another")->GetSubConfig("test_redirect2")->GetSubConfig("people2")->GetSTDStringValue("name", "testname2");*/
  val_float = jhanle.GetSubConfig("another")->GetSubConfig("people2")->GetFloatValue("vfloat", 0.1);
  val_int = jhanle.GetSubConfig("another")->GetSubConfig("people2")->GetSubConfig("people2")->GetIntValue("age", 101);
  val_str = jhanle.GetSubConfig("another")->GetSubConfig("people2")->GetSubConfig("people2")->GetSTDStringValue("name", "testname2");
  jhanle.GetSubConfig("another")->GetSubConfig("people2")->GetSubConfig("people3")->SetSTDStringValue("name", tempstr);
  jhanle.GetSubConfig("another")->GetSubConfig("people2")->GetSubConfig("people3")->SetIntValue("age", 100);
  std::cout << "another2 float value = " << val_float << std::endl;
  std::cout << "another2 int value = " << val_int << std::endl;
  std::cout << "another2 str value = " << val_str << std::endl;

  spJsonWrapper subwrapper = jhanle.GetArray("test_array");
  JsonWrappers *subconfig = subwrapper.get();
  val_int = (*subconfig)[0]->GetIntValue("vint", 4);
  (*(jhanle.GetArray("test_array2").get()))[4]->SetSTDStringValue("vstring", tempstr);
  (*(jhanle.GetArray("test_array2").get()))[4]->SetIntValue("vint", 109);

  (*subconfig)[1]->SetIntValue("vint", val_int);
  (*subconfig)[1]->SetSTDStringValue("vstring", val_str);

  jhanle.Save2File(json_file_ot);
  jhanle.Close();
}

int main() {
  test_jsoncpp();

  getchar();
  return 0;
}