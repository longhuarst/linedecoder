#include <iostream>




#include "clhlib_ringbuffer.h"


#include "tty.h"

clhlib_ringbuffer(int)








clh::serial::tty mytty;//串口对象











int main(int argc, char *argv[]) {
    std::cout << "Hello, World!" << std::endl;

    std::string devpath_ = "/dev/ttyUSB0";


    if (argc > 2){
        for (int i=1;i<argc;++i){
            if (std::string(argv[i]) == "-D" || std::string(argv[i]) == "-d"){
                std::cout<<"设备路径 = "<<std::string(argv[i+1])<<std::endl;
                devpath_ = std::string(argv[i+1]);
            }
        }
    }


    //打开串口
    mytty.init(devpath_,115200);







    if (mytty.getfd() < 0){
        //串口没有被正常打开
    }else{
        mytty.closefd();
    }








    return 0;
}





