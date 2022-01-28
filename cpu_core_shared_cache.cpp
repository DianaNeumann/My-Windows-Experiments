#include <windows.h>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

typedef BOOL(WINAPI* LPFN_GLPI)(LOGICAL_PROCESSOR_RELATIONSHIP,
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX, PDWORD);

int main(){

    ofstream out("out.txt");

    LPFN_GLPI glpi = (LPFN_GLPI)GetProcAddress(
        GetModuleHandle(TEXT("kernel32")), "GetLogicalProcessorInformationEx");

    if (!glpi) {
        cout << " [-] GetLogicalProcessorInformation is not supported." << endl;
        return 1;
    }

    DWORD bytes = 0;
    glpi(RelationAll, 0, &bytes);

    
    vector<char> buffer(bytes);
    
    SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX* info;

    if (!glpi(RelationAll, (SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX*)&buffer[0], &bytes))
        return 1;

    
    

    for (size_t i = 0; i < bytes; i += info->Size)
    {
        
        info = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX*)&buffer[i];

        if (info->Relationship == RelationCache &&
            (info->Cache.Type == CacheData || info->Cache.Type == CacheUnified)){

            cout << "info->Cache.Level: " << (int)info->Cache.Level << endl;
            out << "info->Cache.Level: " << (int)info->Cache.Level << endl;

            cout << "info->Cache.CacheSize: " << (int)info->Cache.CacheSize << endl;
            out << "info->Cache.CacheSize: " << (int)info->Cache.CacheSize << endl;


            cout << "info->Cache.GroupMask.Group: " << info->Cache.GroupMask.Group << endl;
            out << "info->Cache.GroupMask.Group: " << info->Cache.GroupMask.Group << endl;

            cout << "info->Cache.GroupMask.Mask: " << info->Cache.GroupMask.Mask << endl << endl;
            out << "info->Cache.GroupMask.Mask: " << info->Cache.GroupMask.Mask << endl << endl;
        }
    }

    out.close();
    return 0;
}
