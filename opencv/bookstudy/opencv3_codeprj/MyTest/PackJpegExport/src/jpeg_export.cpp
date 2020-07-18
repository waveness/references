#include <fstream>
#include <iostream>
#include <string>
#include <vector>
int main(int argc, char **argv)
{
  int ret = 0;
  if (argc < 3) {
    std::cout << "usage: exe path/test.pack outpath" << std::endl;
    return -1;
  }
  uint32_t frame_cnt = 0;
  std::fstream fin;
  std::fstream fout;
  std::string inname;
  std::string outname;
  std::string outpath;
  inname.assign(argv[1]);
  outpath.assign(argv[2]);
  std::string input_path = inname.substr(0, inname.find_last_of("\\"));
  std::string temp_path = outpath;
  if (outpath.substr(outpath.length() - 1) == "\\")
    temp_path = outpath.substr(0, outpath.length() - 1);

  if (temp_path == input_path) {
    std::cout << "error: the input file directory is same with outpath" << std::endl;
    return -1;
  }

  fin.open(inname, std::ios::in | std::ios::binary);
  if (!fin.is_open()) {
    std::cout << "error: open file " << inname << "failed!!continue" << std::endl;
    return -1;
  }

  std::cout << "input file name " << inname << std::endl;
  //get file size
  fin.seekg(0, std::ios::end);
  int tsize = fin.tellg();
  fin.seekg(0, std::ios::beg);

  //read version
  int version = 0;
  fin.read((char *)&version, sizeof(int));
  tsize -= 4;

  //read protobuf & image data in loop
  int old_proto_len = 0;
  int new_proto_len = 0;
  int img_len = 0;
  std::vector<char> imgbuf;
  imgbuf.resize(1024 * 1024);
  while (tsize > 0) {
    //read protobuf data
    fin.read((char*)&old_proto_len, sizeof(int));
    //fin.read(&protobuf[0], old_proto_len);
    fin.seekg(old_proto_len, std::ios::cur);

    //std::cout << "tsize =" << tsize << ", protolen=" << old_proto_len << std::endl;
    tsize -= (sizeof(int) + old_proto_len);
    if (tsize <= 0) {
      std::cout << "file size error" << std::endl;
      ret = -1;
      goto out;
    }
    //read image data
    fin.read((char*)&img_len, sizeof(int));
    if (img_len > imgbuf.size()) {
      imgbuf.resize(img_len + 1024);
    }
    outname = outpath + "\\" + std::to_string(frame_cnt++) + ".jpg";
    fout.open(outname, std::ios::out | std::ios::binary);
    if (!fout.is_open()) {
      std::cout << "error: open file " << outname << "failed" << std::endl;
      ret = -1;
      return -1;
    }

    fin.read(&imgbuf[0], img_len);
    fout.write(&imgbuf[0], img_len);
    fout.sync();
    fout.close();
    //std::cout << "tsize =" << tsize << ", imglen=" << img_len << std::endl;
    tsize -= (sizeof(int) + img_len);
    if (tsize < 0) {
      std::cout << "file size error" << std::endl;
      ret = -1;
      goto out;
    }
  }
  fin.sync();
  fin.close();
out:
  if (ret == 0) {
    std::cout << "congratulations,you are success ^_^" << std::endl;
  }
  else {
    std::cout << "bad news,you are failed -_-!!" << std::endl;
  }
  fin.close();
  return 0;
}