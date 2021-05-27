#include <iostream>
#include "readfile.h"

using namespace std;

int main(int  argc, char * argv[])
{
    if(argc<2)
    {
        cout<<"Usage: "<<argv[0]<<" <filename>\n";
        return 0;
    }

    Graph * Gph = parse_file(argv[1]);

    if(Gph==NULL) return 0;
    int time_taken = Gph->shortest();

    if(time_taken==-1)
    {
        cout<<"There is no way for the car at "<<Gph->src<<" to reach the emergency at "<<Gph->dest<<endl;
    }
    else cout<<"Fastest time for car at "<<Gph->src<<" to reach the emergency at "<<Gph->dest<<" is "<<time_taken<<" minutes\n";
    
    
    return 0;
}