#include <AppleCarving/AppleCarving.hpp>
//C:\Users\pozoy\Desktop\lib_apple\build_my_project\project\test\Debug
int main(int argc, char* argv[]) {

   
    Cities cit;
    std::string path = "C:/Users/pozoy/Desktop/lib_apple/AppleCarving/project/test/data/data2.txt";
    cit.InitializationPoints(path, argc,  argv);
    Carving carv;

    int begin_trap = 0;
    int end_trap = 18;
    carv.Generate_path(cit, begin_trap, end_trap);
    cit.DrawBeforeCarving();
    carv.MergeFaces(cit);
    cit.DrawAfterCarving();
   
    return 0;
}